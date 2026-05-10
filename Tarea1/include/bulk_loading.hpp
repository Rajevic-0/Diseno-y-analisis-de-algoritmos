#ifndef BULK_LOADING_HPP
#define BULK_LOADING_HPP

#include "rtree.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Implementación del algoritmo Sort-Tile-Recursive (STR)
 * 
 * Agrupa puntos en una grilla bidimensional para minimizar el solapamiento de MBRs
 * 
 * @param path Ruta al archivo binario que contiene los ptos en bruto
 * @param n Cantidad de puntos a procesar 
 */
std::vector<RTreeNode> s_t_r(const std::string &path, const int n);

/**
 * @brief Implementación del algoritmo Nearest-X (NX)
 * 
 * Ordena los puntos por la coordenada X y los agrupa de forma secuencial
 *
 * @param path Ruta al archivo binario que contiene los ptos en bruto
 * @param n Cantidad de puntos a procesar 
 */
std::vector<RTreeNode> nearest_x(const std::string &path, const int n);

#endif
