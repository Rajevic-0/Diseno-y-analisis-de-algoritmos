#include "../include/rtree.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

int b = 204;
std::vector<RTreeNode> nodos(1);

Key mbr(const RTreeNode nodo){
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

void nearest_x(const std::string &path, const int n){
    std::vector<std::pair<float,float>> puntos = TreeUtils::load(path);
    std::vector<std::pair<Key, int>> pares;

    for (int i = 0; i < n; i++) {
        int x = puntos[i].first, y = puntos[i].second;
        Key k = {x, x, y, y};
        pares.push_back({k, -1});
    }

    nearest_x_rec(pares, pares.size());
}

void nearest_x_rec(const std::vector<std::pair<Key, int>> pares, const int n) {
    std::sort(pares.begin(), pares.end(),
    [](std::pair<Key, int> a, std::pair<Key, int> b) {
        return (a.first.x1 + a.first.x2) < (b.first.x1 + b.first.x2);
    });

    std::vector<std::pair<Key, int>> nuevo_pares;

    for (int i = 0; i < n; i += b) {
        RTreeNode nodo;
        int fin = std::min(i+b, n);

        std::copy(pares.begin() + i, pares.begin() + i + fin, nodo.child);

        nodo.k = fin - i;

        if (n < b) {
            nodos[0] = nodo;
            return;
        }

        nodos.push_back(nodo);

        nuevo_pares.push_back({mbr(nodo), nodos.size()-1});
    }
    nearest_x_rec(nuevo_pares, nuevo_pares.size());
}