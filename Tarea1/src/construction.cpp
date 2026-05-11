/** construction.cpp
 * @brief Implementación de construcción de R-Trees para los datasets.
 */
#include "../include/bulk_loading.hpp"
#include "../include/rtree.hpp"
#include <chrono>
#include <iostream>
#include <vector>

/**
 * @brief Ejecuta la construción para los datasets.
 * 1. Se itera sobre las potencias de 2 para definir tamaño de N.
 * 2. Se cargan los puntos desde los archivos binarios.
 * 3. Para cada N, se ejecuta y mide el tiempo de NX Y STR.
 * 4. Al alcanzar el máximo, se guardan los cuatro árboles en disco.
 * @param path1 ruta al archivo1.
 * @param path2 ruta al archivo2. 
 */
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

/**
 * @brief Construcción del árbol especializado para la parte Bonus.
 * Sigue la misma lógica de bulk-loading pero en un archivo persistente.
 * @param path Ruta al archivo con los puntos del Bonus.
 */
void bonus_construction(std::string path) {
  std::vector<RTreeNode> rtree_nodes;
  int N = 1 << 24;
  rtree_nodes = s_t_r(path, N);
  const std::string filename = "europa-bonus.bin";
  TreeUtils::write_tree_to_file(filename, rtree_nodes);
  std::cout << "R-tree serializado en '" << filename << "'." << std::endl;
  return;
}
