/*
 * ============================================================================
 * main.cpp
 * ============================================================================
 * Punto de entrada del programa. Realiza la comparación entre AVL Trees y
 * Splay Trees en varios escenarios de construcción y búsqueda.
 * ============================================================================
 */

#include "../include/avl-tree.hpp"
#include "../include/splay-tree.hpp"
#include "../include/tree-rotations.hpp"
#include <chrono>
#include <iostream>
#include <vector>

// Función que realiza la construcción y pruebas de los árboles
// Definida en construction.cpp
void construction();

/**
 * @brief Función principal del programa
 * 
 * Ejecuta la función de construcción que realiza:
 * - Pruebas de rendimiento con diferentes tamaños de datos
 * - Comparación entre AVL Trees y Splay Trees
 * - Medición de tiempos de inserción y búsqueda
 * - Pruebas de teoremas (Sequential Access, Working Set)
 * 
 * @param argc Cantidad de argumentos en línea de comandos (no utilizado)
 * @param argv Array de strings con parámetros (no utilizado)
 * @return int Código de salida (0 para éxito)
 */
int main(int argc,  char *argv[]) {
  construction();
  return 0;
}
