// search_value.cpp
#include "../include/rtree.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 5) {
    std::cerr << "Uso: ./search_value <x1> <x2> <y1> <y2>" << std::endl;
    return 1;
  }

  Key query;
  query.x1 = std::atof(argv[1]);
  query.x2 = std::atof(argv[2]);
  query.y1 = std::atof(argv[3]);
  query.y2 = std::atof(argv[4]);
  const std::string filename = "rtree.bin";

  // Crear un objeto RTree para buscar en el archivo
  RTree rtree(filename);

  std::cout << "Buscando puntos en rango: " << std::endl;
  std::cout << "X: [" << query.x1 << " " << query.x2 << "]" << std::endl;
  std::cout << "Y: [" << query.y1 << " " << query.y2 << "]" << std::endl;

  std::vector<std::pair<float, float>> results;
  rtree.search(query, 0, results);

  std::cout << "Total de puntos encontrados: " << results.size() << std::endl;
  for (const auto &punto : results) {
    std::cout << "(x: " << punto.first << ", y: " << punto.second << ")"
              << std::endl;
  }
  return 0;
}
