// create_tree.cpp
#include "../include/bulk_loading.hpp"
#include "../include/rtree.hpp"
#include <iostream>
#include <vector>
#include <chrono>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Uso: ./test_load <archivo1.bin> <archivo2.bin>" << std::endl;
    return 1;
  }

  std::string path1 = argv[1], path2 = argv[2];

  std::vector<RTreeNode> rtree_nodes;
  auto inicio = std::chrono::high_resolution_clock::now();
  auto fin = std::chrono::high_resolution_clock::now();
  auto tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin-inicio);

  for (int i = 15; i < 25; i++) {
    int N = 1 << i;
    std::cout << "-------------------- 2^" << i << " --------------------" << std::endl;
    std::cout << "---- Random ---" << std::endl;
    std::cout << "Nearest-X -";

    inicio = std::chrono::high_resolution_clock::now();
    rtree_nodes = nearest_x(path1, N);
    fin = std::chrono::high_resolution_clock::now();
    tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin-inicio);
    std::cout << "Tiempo: " << tiempo.count() << " milisegundos" << std::endl;

    if (i == 24) {
        const std::string filename = "random-nearest-x.bin";
        TreeUtils::write_tree_to_file(filename, rtree_nodes);
        std::cout << "R-tree serializado en '" << filename << "'." << std::endl;
    }
    //std::cout << "STR -";
    //inicio = std::chrono::high_resolution_clock::now();
    //rtree_nodes = s_t_r(path1, N);
    //fin = std::chrono::high_resolution_clock::now();
    //tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin-inicio);
    //std::cout << "Tiempo: " << tiempo.count() << " milisegundos" << std::endl;
    //if (i == 24) {
    //    const std::string filename = "random-str.bin";
    //    TreeUtils::write_tree_to_file(filename, rtree_nodes);
    //    std::cout << "R-tree serializado en '" << filename << "'." << std::endl;
    //}


    std::cout << "---- Europa ---" << std::endl;
    std::cout << "Nearest-X -";

    inicio = std::chrono::high_resolution_clock::now();
    rtree_nodes = nearest_x(path2, N);
    fin = std::chrono::high_resolution_clock::now();
    tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin-inicio);
    std::cout << "Tiempo: " << tiempo.count() << " milisegundos" << std::endl;

    if (i == 24) {
        const std::string filename = "europa-nearest-x.bin";
        TreeUtils::write_tree_to_file(filename, rtree_nodes);
        std::cout << "R-tree serializado en '" << filename << "'." << std::endl;
    }

    //std::cout << "STR -";
    //inicio = std::chrono::high_resolution_clock::now();
    //rtree_nodes = s_t_r(path2, N);
    //fin = std::chrono::high_resolution_clock::now();
    //tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin-inicio);
    //std::cout << "Tiempo: " << tiempo.count() << " milisegundos" << std::endl;
    //if (i == 24) {
    //    const std::string filename = "europa-str.bin";
    //    TreeUtils::write_tree_to_file(filename, rtree_nodes);
    //    std::cout << "R-tree serializado en '" << filename << "'." << std::endl;
    //}
  }
  return 0;
}
