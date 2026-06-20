// main.cpp
#include "../include/avl-tree.hpp"
#include "../include/splay-tree.hpp"
#include "../include/tree-rotations.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

// Función que realiza la construcción y pruebas de los árboles
// Definida en construction.cpp
void construction();
void sequential();
void working();
void escenarios_base();

/**
 * @brief Función main para ejecución de comandos.
 * @param argc Cantidad de argumentos.
 * @param argv Array de strings con parámetros.
 *   - argv[1]: Acción a realizar.
 *   - argv[2] y argv[3]: Rutas de archivos.
 * @return int Código de éxito o error.
 */
int main(int argc, char* argv[]) {
    // Modo por defecto: construction
    std::string mode = "construction";
    
    // Si se proporciona un argumento, usarlo como modo
    if (argc > 1) {
        mode = argv[1];
    }
    
    // Ejecutar según el modo especificado
    if (mode == "construction") {
        std::cout << "Ejecutando: Construcción de datasets" << std::endl;
        std::cout << "=============================================" << std::endl << std::endl;
        construction();
    } 
    else if (mode == "base") {
        std::cout << "Ejecutando: Pruebas Base de Construcción y Búsqueda" << std::endl;
        std::cout << "=============================================" << std::endl << std::endl;
        escenarios_base();
    } 
    
    else if (mode == "sequential") {
        std::cout << "Ejecutando: Teorema de Acceso Secuencial" << std::endl;
        std::cout << "=============================================" << std::endl << std::endl;
        sequential();
    } 
    else if (mode == "working") {
        std::cout << "Ejecutando: Teorema del Conjunto de Trabajo" << std::endl;
        std::cout << "=============================================" << std::endl << std::endl;
        working();
    } 
    return 0;
}
