#include "../include/rtree.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int b = 204;
std::vector<RTreeNode> nodos(1);

void sort_tile_recursive(std::vector<std::pair<Key, int>> *pares, const int n) {

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
    sort_tile_recursive(&nuevo_pares, nuevo_pares.size());
  }
}

std::vector<RTreeNode> s_t_r(const std::string &path, const int n) {
  std::vector<std::pair<float, float>> puntos = TreeUtils::load(path);
  std::vector<std::pair<Key, int>> pares;

  for (int i = 0; i < n; i++) {
    float x = puntos[i].first, y = puntos[i].second;
    Key k = {x, x, y, y};
    pares.push_back({k, -1});
  }

  sort_tile_recursive(&pares, pares.size());
  return nodos;
}
