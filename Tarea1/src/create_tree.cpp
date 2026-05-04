// create_tree.cpp
#include "../include/bulk_loading.hpp"
#include "../include/rtree.hpp"
#include <iostream>
#include <vector>

/**
 * @brief Crea un R-tree de ejemplo
 * @return std::vector<RTreeNode> Vector con los nodos serializables
 */
std::vector<RTreeNode> create_sample_rtree() {
  std::vector<RTreeNode> rtree_nodes;
  RTreeNode root;
  root.k = 2;

  root.child[0].first = {0.0, 50.0, 0.0, 50.0};
  root.child[0].second = 1;

  root.child[1].first = {51.0, 100.0, 51.0, 100.0};
  root.child[1].second = 2;

  RTreeNode leaf1, leaf2;
  leaf1.k = 1;
  leaf1.child[0].first = {25.0, 25.0, 25.0, 25.0};
  leaf1.child[0].second = -1;

  leaf2.k = 1;
  leaf2.child[0].first = {75.0, 75.0, 75.0, 75.0};
  leaf2.child[0].second = -1;

  rtree_nodes.push_back(root);
  rtree_nodes.push_back(leaf1);
  rtree_nodes.push_back(leaf2);
  return rtree_nodes;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Uso: ./test_load <archivo.bin>" << std::endl;
    return 1;
  }

  std::string path = argv[1];
  const std::string filename = "rtree.bin";

  // Creamos el árbol usando la función auxiliar
  int N = 1 << 15;
  std::vector<RTreeNode> rtree_nodes = s_t_r(path, N);

  // Serializamos el árbol a disco
  TreeUtils::write_tree_to_file(filename, rtree_nodes);

  std::cout << "R-tree serializado en '" << filename << "'." << std::endl;
  return 0;
}
