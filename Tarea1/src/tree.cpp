/**
 * tree.cpp
 * @brief Implementación de la gestión del R-Tree en la memoria externa.
 * Contiene la lógica para interactuar con archivo binario, realizar
 * lecturas a bloques del disco y ejecutar búsquedas espaciales.
 */
#include "../include/rtree.hpp"

// Contador para información de las lecturas al disco.
int lecturas = 0;
// Implementación de RTree.
RTree::RTree(const std::string &filename) { this->filename = filename; }

/**
 * @brief Calcula la posición física de un nodo mediante la fórmula
 * file_offset = offset * sizeof(RTreeNode).
 * Como el tamaño de RTreeNode es de 4096 bytes, sabemos que cada lectura
 * está alineada con el tamaño de un bloque.
 */
RTreeNode RTree::read_node_at(int offset) const {
  RTreeNode node;
  std::ifstream in(filename, std::ios::binary);
  if (!in.is_open()) {
    std::cerr << "Error al abrir archivo para lectura: " << filename
              << std::endl;
    std::exit(1);
  }

  std::streampos file_offset = offset * sizeof(RTreeNode);
  in.seekg(file_offset);
  in.read(reinterpret_cast<char *>(&node), sizeof(RTreeNode));

  if (!in) {
    std::cerr << "Error al leer nodo en posición " << offset << std::endl;
    std::exit(1);
  }

  in.close();
  return node;
}

/**
 * Implementa la búsqueda en rango recursiva devolviendo la cantidad de puntos
 * dentro de un rango.
 * Lecturas se incrementa cada vez que se invoca a read_node_at
 * Se itera sobre las k entradas del nodo, para cada nodo se verifica si su
 * MBR intersecta con el área de búsqueda.
 * Si el índice es -1 nos encontramos en un punto y lo añadimos a nuestro contador.
 * Si el índice es positivo, llamamos recursivamente a search usando el nuevo valor.
 */
int RTree::search(Key query, int &lecturas, int offset) const {
  RTreeNode node = read_node_at(offset);
  lecturas++;
  int puntos = 0;
  for (int i = 0; i < node.k; i++) {
    Key childK = node.child[i].first;
    int childVal = node.child[i].second;
    if (TreeUtils::intersects(childK, query)) {
      if (childVal == -1) {
        puntos++;
      } else {
        puntos += search(query, lecturas, childVal);
      }
    }
  }
  return puntos;
}

/**
 * Buscador de los puntos específicos que están dentro de un rango.
 * Se incrementa lecturas cada vez que se invoca a read_node_at.
 * Se itera sobre las k entradas del nodo, para cada nodo se verifica si su
 * MBR intersecta con el área de búsqueda.
 * Si el índice es -1 nos encontramos en un punto y lo añadimos a nuestro contador.
 * Si el índice es positivo, llamamos recursivamente a search usando el nuevo valor.
 */
std::vector<Key> RTree::searchPoints(Key query, int &lecturas,
                                     int offset) const {
  RTreeNode node = read_node_at(offset);
  lecturas++;
  std::vector<Key> puntos;
  for (int i = 0; i < node.k; i++) {
    Key childK = node.child[i].first;
    int childVal = node.child[i].second;
    if (TreeUtils::intersects(childK, query)) {
      if (childVal == -1) {
        puntos.push_back(childK);
      } else {
        std::vector<Key> ans = searchPoints(query, lecturas, childVal);
        puntos.insert(puntos.end(), ans.begin(), ans.end());
      }
    }
  }
  return puntos;
}

// Implementación de TreeUtils
namespace TreeUtils {

/**
 * Carga los datos desde los datasets binarios.
 * Lee pares de floats y los almacena dentro de un vector.
 * Función encargada de preparar los datos para el bulk-loading
 */
std::vector<std::pair<float, float>> load(const std::string &path) {
  std::vector<std::pair<float, float>> points;
  std::ifstream file(path, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error al abrir el dataset binario: " << path << std::endl;
    return points;
  }
  float coord[2];
  while (file.read(reinterpret_cast<char *>(coord), sizeof(float) * 2)) {
    points.push_back({coord[0], coord[1]});
  }
  return points;
}

/**
 * Serializa la estructura hacia un archivo binario.
 * Se recorre el vector de nodos creado y escribe cada uno de forma contigua
 * en el archivo.
 */
void write_tree_to_file(const std::string &filename,
                        const std::vector<RTreeNode> &nodes) {
  std::ofstream out(filename, std::ios::binary);
  if (!out.is_open()) {
    std::cerr << "Error al abrir archivo para escritura: " << filename
              << std::endl;
    std::exit(1);
  }

  for (const RTreeNode &node : nodes) {
    out.write(reinterpret_cast<const char *>(&node), sizeof(RTreeNode));
  }

  out.close();
}

/**
 * Verifica si dos rectángulos colisionan.
 */
bool intersects(Key a, Key b) {
  return !(a.x1 > b.x2 || a.x2 < b.x1 || a.y1 > b.y2 || a.y2 < b.y1);
}

/**
 * Calcula el MBR de un nodo.
 * Recorre todas las entradas de un RTree y encuentra los valores extremos
 * que contienen todos los hijos.
 */
Key mbr(const RTreeNode nodo) {
  float min_x = nodo.child[0].first.x1;
  float max_x = nodo.child[0].first.x2;
  float min_y = nodo.child[0].first.y1;
  float max_y = nodo.child[0].first.y2;

  for (int i = 0; i < nodo.k; i++) {
    Key k = nodo.child[i].first;
    min_x = std::min(min_x, std::min(k.x1, k.x2));
    max_x = std::max(max_x, std::max(k.x1, k.x2));
    min_y = std::min(min_y, std::min(k.y1, k.y2));
    max_y = std::max(max_y, std::max(k.y1, k.y2));
  }

  return {min_x, max_x, min_y, max_y};
}
} // namespace TreeUtils
