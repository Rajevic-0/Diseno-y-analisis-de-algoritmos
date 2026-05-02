#include "../include/rtree.hpp"

// Implementación de RTree
RTree::RTree(const std::string &filename) {
  this->filename = filename;
}

RTreeNode RTree::read_node_at(int offset) const {
  RTreeNode node;
  std::ifstream in(filename, std::ios::binary);
  if (!in.is_open()) {
    std::cerr << "Error al abrir archivo para lectura: " << filename
              << std::endl;
    std::exit(1);
  }

  std::streampos file_offset = offset * sizeof(RTreeNode);
  in.seekg(file_offset);
  in.read(reinterpret_cast<char *>(&node), sizeof(RTreeNode));

  if (!in) {
    std::cerr << "Error al leer nodo en posición " << offset << std::endl;
    std::exit(1);
  }
  
  in.close();
  return node;
}

void RTree::search(Key query, int offset, std::vector<std::pair<float,float>> &results) const {
  RTreeNode node = read_node_at(offset);
  for (int i=0;i<node.k;i++){
    Key childK = node.child[i].first;
    int childMBR = node.child[i].second;
    if (TreeUtils::intersects(childK, query)) {
      if (childMBR == -1) {
        results.push_back({childK.x1, childK.y1});
      } else {
        search(query, childMBR, results);
      }
    }
  }
}

// Implementación de TreeUtils
namespace TreeUtils {

std::vector<std::pair<float,float>> load(const std::string &path){
  std::vector<std::pair<float,float>> points;
  std::ifstream file(path,std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error al abrir el dataset binario: " << path << std::endl;
    return points;
  }
  float coord[2];
  while (file.read(reinterpret_cast<char*>(coord), sizeof(float) * 2)) {
    points.push_back({coord[0],coord[1]});
  }
  return points;
}

void write_tree_to_file(
    const std::string &filename,
    const std::vector<RTreeNode> &nodes
) {
  std::ofstream out(filename, std::ios::binary);
  if (!out.is_open()) {
    std::cerr << "Error al abrir archivo para escritura: " << filename
              << std::endl;
    std::exit(1);
  }

  for (const RTreeNode &node : nodes) {
    out.write(reinterpret_cast<const char *>(&node), sizeof(RTreeNode));
  }

  out.close();
}

bool intersects(Key a, Key b){
  return !(a.x1>b.x2 || a.x2 < b.x1 || a.y1 > b.y2 || a.y2 < b.y1);
}

} // namespace TreeUtils
