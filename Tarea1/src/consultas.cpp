// create_tree.cpp
#include "../include/bulk_loading.hpp"
#include "../include/rtree.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

void r_query() {
  RTree random_nx("random-nearest-x.bin");
  RTree random_str("random-str.bin");
  RTree europa_nx("europa-nearest-x.bin");
  RTree europa_str("europa-str.bin");

  std::vector<float> s = {0.0025, 0.005, 0.01, 0.025, 0.05};

  std::random_device rd;
  std::mt19937 gen(rd());

  Key cuadrado;
  std::vector<int> puntos(5, 0);
  std::vector<int> lecturas(5, 0);

  for (int i = 0; i < 5; i++) {
    std::uniform_real_distribution<float> dist(0.0, 1.0 - s[i]);

    for (int j = 0; j < 100; j++) {
      float x = dist(gen);
      float y = dist(gen);
      cuadrado = {x, x + s[i], y, y + s[i]};

      puntos[i] += random_nx.search(cuadrado, lecturas[i]);
      puntos[i] += random_str.search(cuadrado, lecturas[i]);
      puntos[i] += europa_nx.search(cuadrado, lecturas[i]);
      puntos[i] += europa_str.search(cuadrado, lecturas[i]);
    }

    std::cout << "------ s = " << s[i] << " ------" << std::endl;
    std::cout << "Promedio de lecturas a disco: " << lecturas[i] / 100
              << std::endl;
    std::cout << "Promedio de puntos encontrados: " << puntos[i] / 100
              << std::endl;
  }
  return;
}
