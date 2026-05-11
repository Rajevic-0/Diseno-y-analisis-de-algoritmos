/**
 * sort-tile-recursive.cpp
 * @breaf Implementación para bulk loading STR.
 * Algoritmo que construye un R-Tree mediante un ordenamiento de dos dimensiones
 * evitando así el solapamiento de nodos.
 */
#include "../include/globals.hpp"
#include "../include/rtree.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

/**
 * Función auxiliar que implementa STR de forma recursiva.
 * 1. Se ordenan los rectángulos por el centro de la coordenada X.
 * 2. Se juntan en sqrt(n/b) grupos consecutivos.
 * 3. Se ordenan los rectángulos según la coordenada Y del centro del triángulo y se
 * dividen nuevamente en sqrt(n/b) grupos para cada grupo del paso 2.
 * 4. Se guardan los n/b nodos creados en el vector de nodos dejando el primer espacio vacío.
 * 5. Se calcula su MBR y se generan n/b pares.
 * 6. Si los n/b pares entran en un nodo, se crea el nodo raíz con todos los pares y
 * se guarda en la primera posición, si no se hace la recursión STR.
 */
void sort_tile_recursive(std::vector<std::pair<Key, int>> *pares, const int n, std::vector<RTreeNode> &nodos) {
  if (n <= b) {
    RTreeNode nodo;
    nodo.k = n;
    if (n > 0)
      std::copy(pares->begin(), pares->begin() + n, nodo.child);
    nodos[0] = nodo;
    return;
  }
  std::sort(pares->begin(), pares->end(),
            [](std::pair<Key, int> &a, std::pair<Key, int> &b) {
              return (a.first.x1 + a.first.x2) < (b.first.x1 + b.first.x2);
            });
  std::vector<std::pair<Key, int>> nuevo_pares;
  int s = std::ceil(std::sqrt((n + b - 1) / b));
  int ctdad = (n + s - 1) / s;

  for (int i = 0; i < n; i += ctdad) {
    int fin = std::min(i + ctdad, n);
    std::sort(pares->begin() + i, pares->begin() + fin,
              [](std::pair<Key, int> &a, std::pair<Key, int> &b) {
                return (a.first.y1 + a.first.y2) < (b.first.y1 + b.first.y2);
              });

    for (int j = i; j < fin; j += b) {
      RTreeNode nodo;

      int fin_y = std::min(j + b, fin);

      std::copy(pares->begin() + j, pares->begin() + fin_y, nodo.child);

      nodo.k = fin_y - j;

      if (n < b) {
        nodos[0] = nodo;
        return;
      }

      nodos.push_back(nodo);

      nuevo_pares.push_back({TreeUtils::mbr(nodo), nodos.size() - 1});
    }
  }
  sort_tile_recursive(&nuevo_pares, nuevo_pares.size(), nodos);
}

/**
 * Función para la construcción de NX.
 * Se cargan los puntos desde el archivo binario, se transforman en hojas y,
 * finalmente, se llama a la función auxiliar.
 */
std::vector<RTreeNode> s_t_r(const std::string &path, const int n) {
  std::vector<std::pair<float, float>> puntos = TreeUtils::load(path);
  std::vector<std::pair<Key, int>> pares;
  std::vector<RTreeNode> nodos(1);

  for (int i = 0; i < n; i++) {
    float x = puntos[i].first, y = puntos[i].second;
    Key k = {x, x, y, y};
    pares.push_back({k, -1});
  }

  sort_tile_recursive(&pares, pares.size(), nodos);
  return nodos;
}
