// create_tree.cpp
#include "../include/bulk_loading.hpp"
#include "../include/rtree.hpp"
#include <chrono>
#include <iostream>
#include <vector>

void construction(std::string path1, std::string path2) {
  std::vector<RTreeNode> rtree_nodes;
  auto inicio = std::chrono::high_resolution_clock::now();
  auto fin = std::chrono::high_resolution_clock::now();
  auto tiempo =
      std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);

  for (int i = 15; i < 25; i++) {
    int N = 1 << i;
    std::cout << "-------------------- 2^" << i << " --------------------"
              << std::endl;
    std::cout << "---- Random ---" << std::endl;
    std::cout << "Nearest-X -";

    inicio = std::chrono::high_resolution_clock::now();
    rtree_nodes = nearest_x(path1, N);
    fin = std::chrono::high_resolution_clock::now();
    tiempo =
        std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
    std::cout << "Tiempo: " << tiempo.count() << " milisegundos" << std::endl;

    if (i == 24) {
      const std::string filename = "random-nearest-x.bin";
      TreeUtils::write_tree_to_file(filename, rtree_nodes);
      std::cout << "R-tree serializado en '" << filename << "'." << std::endl;
    }
    std::cout << "STR -";
    inicio = std::chrono::high_resolution_clock::now();
    rtree_nodes = s_t_r(path1, N);
    fin = std::chrono::high_resolution_clock::now();
    tiempo =
        std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
    std::cout << "Tiempo: " << tiempo.count() << " milisegundos" << std::endl;
    if (i == 24) {
      const std::string filename = "random-str.bin";
      TreeUtils::write_tree_to_file(filename, rtree_nodes);
      std::cout << "R-tree serializado en '" << filename << "'." << std::endl;
    }

    std::cout << "---- Europa ---" << std::endl;
    std::cout << "Nearest-X -";

    inicio = std::chrono::high_resolution_clock::now();
    rtree_nodes = nearest_x(path2, N);
    fin = std::chrono::high_resolution_clock::now();
    tiempo =
        std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
    std::cout << "Tiempo: " << tiempo.count() << " milisegundos" << std::endl;

    if (i == 24) {
      const std::string filename = "europa-nearest-x.bin";
      TreeUtils::write_tree_to_file(filename, rtree_nodes);
      std::cout << "R-tree serializado en '" << filename << "'." << std::endl;
    }

    std::cout << "STR -";
    inicio = std::chrono::high_resolution_clock::now();
    rtree_nodes = s_t_r(path2, N);
    fin = std::chrono::high_resolution_clock::now();
    tiempo =
        std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
    std::cout << "Tiempo: " << tiempo.count() << " milisegundos" << std::endl;
    if (i == 24) {
      const std::string filename = "europa-str.bin";
      TreeUtils::write_tree_to_file(filename, rtree_nodes);
      std::cout << "R-tree serializado en '" << filename << "'." << std::endl;
    }
  }
  return;
}

void bonus_construction(std::string path) {
  std::vector<RTreeNode> rtree_nodes;
  int N = 1 << 24;
  rtree_nodes = s_t_r(path, N);
  const std::string filename = "europa-bonus.bin";
  TreeUtils::write_tree_to_file(filename, rtree_nodes);
  std::cout << "R-tree serializado en '" << filename << "'." << std::endl;
  return;
}
