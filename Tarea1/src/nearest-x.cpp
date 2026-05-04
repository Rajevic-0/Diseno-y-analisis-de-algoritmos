#include "../include/globals.hpp"
#include "../include/rtree.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

void nearest_x_rec(std::vector<std::pair<Key, int>> *pares, const int n) {
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
  nearest_x_rec(&nuevo_pares, nuevo_pares.size());
}

std::vector<RTreeNode> nearest_x(const std::string &path, const int n) {
  std::vector<std::pair<float, float>> puntos = TreeUtils::load(path);
  std::vector<std::pair<Key, int>> pares;

  for (int i = 0; i < n; i++) {
    float x = puntos[i].first, y = puntos[i].second;
    Key k = {x, x, y, y};
    pares.push_back({k, -1});
  }

  nearest_x_rec(&pares, pares.size());
  return nodos;
}
