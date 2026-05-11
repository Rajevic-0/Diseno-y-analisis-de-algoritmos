/**
 * search_value.cpp
 * Archivo que contiene un test para verificar la funcionalidad de la búsqueda
 * de valores.
 */
#include "../include/rtree.hpp"
#include <cstdlib>
#include <iostream>

/**
 * @brief Función de test para verificar
 * @param argc Cantidad de argumentos.
 * @param argv Array de strings con parámetros.
 * @return int Código de éxito o error.
 */
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

  std::vector<Key> results;
  int lecturas = 0;
  results = rtree.searchPoints(query, lecturas);

  std::cout << "Total de puntos encontrados: " << results.size() << std::endl;
  for (const auto &punto : results) {
    std::cout << "(x: " << punto.x1 << ", y: " << punto.x2 << ")" << std::endl;
  }
  return 0;
}
