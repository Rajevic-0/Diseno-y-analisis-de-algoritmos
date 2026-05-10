#ifndef RTREE_HPP
#define RTREE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Estructura que representa un MBR
 */

struct Key {
  float x1, x2, y1, y2;
};

/**
 * @brief Estructura que representa un nodo de un R-tree en disco
 *
 * Cada nodo contiene:
 * - k: Cantidad de entradas en el nodo.
 * - child: arreglo de pares (MBR, índice), donde el índice apunta a un nodo
 * hijo o es -1 si es una hoja.
 * - pad: 12 bytes libres para que el tamaño del nodo coincida con el tamaño de
 * un bloque.
 */

struct RTreeNode {
  int k;
  std::pair<Key, int> child[204];
  int pad[3];
};

/**
 * @brief Clase que representa un R-tree almacenado en disco
 *
 * Esta clase permite navegar un R-tree guardado en memoria externa.
 */
class RTree {
public:
  /**
   * @brief Construye un R-tree a partir de un archivo binario
   * @param filename Nombre del archivo que contiene el R-tree
   */
  RTree(const std::string &filename);

  /**
   * @brief Lee un nodo específico desde el  archivo binario
   *
   * Esta función calcula la posición exacta como offset*4096 bytes y carga el
   * bloque a memoria. Es responsabilidad del usuario asegurarse de que el
   * offset sea válido, es decir, que exista un nodo en esa posición.
   *
   * @param offset Índice del bloque/nodo en el archivo
   * @return RTreeNode Estructura con los datos del nodo cargado
   * @throws Termina el programa si no puede abrir el archivo o leer los bytes
   * del nodo
   */
  RTreeNode read_node_at(int offset) const;

  /**
   * @brief Realiza una búsqueda en rango en el R-tree
   *
   * Esta función implementa una búsqueda por rango en el R-tree, leyendo solo
   * los nodos que intersectan con el area de consulta. Si se omite el offset,
   * comienza desde la raíz (offset 0).
   *
   * @param query El MBR de consulta
   * @param offset Posición del nodo inicial (por defecto 0, la raíz)
   * @param results Vector donde se guardaran los pares x,y encontrados.
   * @return TreeNode con el valor buscado, o un nodo con id=-1 si no se
   * encuentra
   */
  int search(Key query, int &lecturas, int offset = 0) const;

  std::vector<Key> searchPoints(Key query, int &lecturas, int offset = 0) const;

private:
  std::string filename;
};

namespace TreeUtils {

/**
 * @brief Lee un conjunto de puntos desde un archivo binario (.bin)
 *
 * Esta función carga los datos originales donde cada punto está
 * representado por dos floats consecutivos (x,y)
 *
 * @param path Ruta al archivo binario del dataset
 * @return std::vector<std::pair<float,float>> Vector con todos los
 * puntos cargados en memoria
 */
std::vector<std::pair<float, float>> load(const std::string &path);

/**
 * @brief Serializa y escribe un R-tree en un archivo binario
 *
 * Esta función recibe un vector de nodos y los escribe secuencialmente
 * en un archivo binario. Cada nodo ocupa sizeof(RTreeNode) bytes.
 *
 * @param filename Nombre del archivo donde se escribirá el R-tree
 * @param nodes Vector de nodos construidos.
 * @throws Termina el programa si no puede abrir el archivo
 */
void write_tree_to_file(const std::string &filename,
                        const std::vector<RTreeNode> &nodes);

/**
 * @brief Determina si dos rectándulos intersectan en alguna parte
 * @param a Primer MBR, buscado
 * @param b Segundo MBR, área de búsqueda
 * @return true si hay intersección, false si no
 */
bool intersects(Key a, Key b);

/**
 * @brief Encuentra el MBR
 * @param nodo El nodo
 * @return Key
 */
Key mbr(const RTreeNode nodo);
} // namespace TreeUtils

#endif
