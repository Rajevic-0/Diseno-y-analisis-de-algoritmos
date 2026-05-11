/**
 * consultas.cpp
 * @brief Experimentación y evaluación del R-Tree.
 * Realiza consultas de rango aleatorias sobre los datasetspara comprobar
 * el rendimiento de los algoritmos de construcción masiva.
 */
#include "../include/bulk_loading.hpp"
#include "../include/rtree.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <cmath>

/**
 * @brief Ejecuta el set de pruebas definido por el enunciado.
 * 1. Se itera sobre 5 tamaños de lado 's'
 * 2. Se generan 100 coordenadas aleatorias para cada 's'
 * 3. Ejecuta la búsqueda en los 4 árboles
 * 4. Calcula y reporta el promedio de lecturas, puntos encontrados y su desviación estándar.
 */
void r_query() {
  RTree random_nx("random-nearest-x.bin");
  RTree random_str("random-str.bin");
  RTree europa_nx("europa-nearest-x.bin");
  RTree europa_str("europa-str.bin");

  std::vector<float> s = {0.0025, 0.005, 0.01, 0.025, 0.05};
  std::vector<std::string> nombres = {"random-nx", "random-str", "europa-nx", "europa-str"};
  int suma;

  std::random_device rd;
  std::mt19937 gen(rd());

  Key cuadrado;
  std::vector<std::vector<std::vector<int>>> puntos(
    4,
    std::vector<std::vector<int>>(
      5,
      std::vector<int>(100, 0)
    )
  );
  std::vector<std::vector<int>> lecturas(4, std::vector<int>(5, 0));

  for (int i = 0; i < 5; i++) {
    std::uniform_real_distribution<float> dist(0.0, 1.0 - s[i]);

    for (int j = 0; j < 100; j++) {
      float x = dist(gen);
      float y = dist(gen);
      cuadrado = {x, x + s[i], y, y + s[i]};

      puntos[0][i][j] = random_nx.search(cuadrado, lecturas[0][i]);
      puntos[1][i][j] = random_str.search(cuadrado, lecturas[1][i]);
      puntos[2][i][j] = europa_nx.search(cuadrado, lecturas[2][i]);
      puntos[3][i][j] = europa_str.search(cuadrado, lecturas[3][i]);
    }


    std::cout << "------ s = " << s[i] << " ------" << std::endl;
    for (int k = 0; k < 4; k++) {
      suma = std::accumulate(puntos[k][i].begin(), puntos[k][i].end(), 0);
      double promedio = (double)suma / 100.0;
      double suma_sq = 0;
      for (int p : puntos[k][i]) {
        suma_sq += (double)p*p;
      }
      double varianza = (suma_sq / 100.0) - (promedio* promedio);
      double desviacion = std::sqrt(std::abs(varianza));

      std::cout << "---- " << nombres[k] << " ----" << std::endl;
      std::cout << "Promedio de lecturas a disco: " << (double)lecturas[k][i] / 100
              << std::endl;
      std::cout << "Promedio de puntos encontrados: " << promedio
              << std::endl;
      std::cout << "Desviación estandar: " << desviacion << std::endl;
    }
  }
  return;
}

/**
 * @brief Ejecuta el set de pruebas definido por el enunciado para el bonus.
 * Se recuperan las coordenadas exactas de los puntos en un área de Europa.
 * 1. Se carga el R-Tree.
 * 2. Se define un MBR de consulta.
 * 3. Utilizamos 'searchPoints' para obtener los (x,y) de los resultados.
 * 4. Imprime las coordenadas encontradas.
 */
void bonus_query() {
  RTree europa_bonus("europa-bonus.bin");
  Key cuadrado;
  cuadrado = {5.662065396260891, 18.90970478446205, 36.387839863769806,
              47.01632746811377};
  int lecturas = 0;
  std::vector<Key> results = europa_bonus.searchPoints(cuadrado, lecturas);
  for (const auto &punto : results) {
    std::cout << "(x: " << punto.x1 << ", y: " << punto.y1 << ")" << std::endl;
  }
}
