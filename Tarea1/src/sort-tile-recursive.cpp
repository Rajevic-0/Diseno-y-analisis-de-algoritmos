#include "../include/rtree.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

int b = 204;
std::vector<RTreeNode> nodos(1);

void sort_tile_recursive(const std::vector<std::pair<Key, int>> pares,
                         const int n) {
  std::sort(pares.begin(), pares.end(),
            [](std::pair<Key, int> a, std::pair<Key, int> b) {
              return (a.first.x1 + a.first.x2) < (b.first.x1 + b.first.x2);
            });
  std::vector<std::pair<Key, int>> nuevo_pares;
  for (int i = 0; i * i < n; i += b) {
    RTreeNode nodo;
    int fin = std::min(i + b, n);

    std::copy(pares.begin() + i, pares.begin() + i + fin, nodo.child);

    nodo.k = fin - i;

    if (n < b) {
      nodos[0] = nodo;
      return;
    }

    nodos.push_back(nodo);

    nuevo_pares.push_back({TreeUtils::mbr(nodo), nodos.size() - 1});
  }
  std::sort(nuevo_pares.begin(), nuevo_pares.end(),
            [](std::pair<Key, int> a, std::pair<Key, int> b) {
              return (a.first.y1 + a.first.y2) < (b.first.y1 + b.first.y2);
            });
  std::vector<std::pair<Key, int>> nuevo_pares_y;
  for (int i = 0; i * i < n; i += b) {
    RTreeNode nodo;
    int fin = std::min(i + b, n);

    std::copy(nuevo_pares.begin() + i, nuevo_pares.begin() + i + fin,
              nodo.child);

    nodo.k = fin - i;

    if (n < b) {
      nodos[0] = nodo;
      return;
    }

    nodos.push_back(nodo);

    nuevo_pares_y.push_back({TreeUtils::mbr(nodo), nodos.size() - 1});
  }
  sort_tile_recursive(nuevo_pares_y, nuevo_pares_y.size());
}

void s_t_r(const std::string &path, const int n) {
  std::vector<std::pair<float, float>> puntos = TreeUtils::load(path);
  std::vector<std::pair<Key, int>> pares;

  for (int i = 0; i < n; i++) {
    float x = puntos[i].first, y = puntos[i].second;
    Key k = {x, x, y, y};
    pares.push_back({k, -1});
  }

  sort_tile_recursive(pares, pares.size());
}
