/**
 * nearest-x.cpp
 * @breaf Implementación para bulk loading Nearest-X.
 * Algoritmo que construye el R-Tree ordenando sus elementos por el centro de la
 * coordenada X y agrupándolos en bloques de tamaño b.
 */
#include "../include/globals.hpp"
#include "../include/rtree.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

/**
 * @brief Función auxiliar recursiva para construir los niveles del árbol.
 * @param pares Puntero a un vector de pares
 * @param nodos Referencia a vector global donde se almacenan los nodos.
 * 1. Se ordenan todos los elementos según el centro de su coordenada X.
 * 2. Se agrupan los elementos ordenados en bloques de tamaño b.
 * 3. Guardar los n/b nodos en el vector de nodos dejando el primer espacio vacío.
 * 4. Se calcula el MBR y se generan n/b pares para cada nodo creado.
 * 5. Si los n/b pares entran en un nodo, se crea la raíz, si no se aplica NX
 * recursivamente a todos los pares.
 */
void nearest_x_rec(std::vector<std::pair<Key, int>> *pares, const int n, std::vector<RTreeNode> &nodos) {
  std::sort(pares->begin(), pares->end(),
            [](std::pair<Key, int> &a, std::pair<Key, int> &b) {
              return (a.first.x1 + a.first.x2) < (b.first.x1 + b.first.x2);
            });

  std::vector<std::pair<Key, int>> nuevo_pares;

  for (int i = 0; i < n; i += b) {
    RTreeNode nodo;
    int fin = std::min(i + b, n);

    std::copy(pares->begin() + i, pares->begin() + fin, nodo.child);

    nodo.k = fin - i;

    if (n < b) {
      nodos[0] = nodo;
      return;
    }

    nodos.push_back(nodo);

    nuevo_pares.push_back({TreeUtils::mbr(nodo), nodos.size() - 1});
  }

  nearest_x_rec(&nuevo_pares, nuevo_pares.size(), nodos);
}

/**
 * Función para la construcción de NX.
 * Se cargan los puntos desde el archivo binario, se transforman en hojas y,
 * finalmente, se llama a la función auxiliar.
 */
std::vector<RTreeNode> nearest_x(const std::string &path, const int n) {
  std::vector<std::pair<float, float>> puntos = TreeUtils::load(path);
  std::vector<std::pair<Key, int>> pares;
  std::vector<RTreeNode> nodos(1);

  for (int i = 0; i < n; i++) {
    float x = puntos[i].first, y = puntos[i].second;
    Key k = {x, x, y, y};
    pares.push_back({k, -1});
  }

  nearest_x_rec(&pares, pares.size(), nodos);

  return nodos;
}
