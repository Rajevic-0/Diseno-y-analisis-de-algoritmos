#ifndef CREATION_HPP
#define CREATION_HPP

#include "rtree.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Función principal para la construcción masiva de R-Trees.
 * @param path1 Ruta al archivo binario del primer dataset (Random en esta tarea).
 * @param path2 Ruta al segundo archivo binario (Europa en este caso).
 */
void construction(std::string path1, std::string path2);

/**
 * @brief Función específica para la construcción del dataset de bonus.
 * @param Ruta al archivo binario del dataset de bonus.
 */
void bonus_construction(std::string path);

/**
 * @brief Función para la fase de implementación y consultas.
 */
void r_query();

/**
 * @brief Función para la fase de implementación y consultas de la parte del bonus.
 */
void bonus_query();

#endif
