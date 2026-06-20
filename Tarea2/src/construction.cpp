/*
 * ============================================================================
 * construction.cpp
 * ============================================================================
 * Archivo principal que ejecuta las pruebas de rendimiento y comparación
 * entre AVL Trees y Splay Trees. Incluye:
 * - Pruebas base con diferentes escenarios
 * - Pruebas de teoremas (Sequential Access, Working Set)
 * - Medición de tiempos de construcción y búsqueda
 * - Generación de datasets
 * ============================================================================
 */

#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>
#include <cstdint>

#include "../include/splay-tree.hpp"
#include "../include/avl-tree.hpp"

// Generador de números aleatorios global
std::mt19937 gen(std::random_device{}());

// ============================================================================
// FUNCIONES DE UTILIDAD
// ============================================================================

/**
 * @brief Lee un dataset desde un archivo
 * Cada línea del archivo contiene un número uint32_t
 * 
 * @param filename Nombre del archivo a leer
 * @return std::vector<uint32_t> Vector con los valores leídos
 */
std::vector<uint32_t> leerDataset(const std::string& filename) {
    std::ifstream file(filename);

    std::vector<uint32_t> valores;
    uint32_t valor;

    // Leer todos los valores del archivo
    while (file >> valor) {
        valores.push_back(valor);
    }

    return valores;
}

/**
 * @brief Genera un conjunto de trabajo (working set)
 * Crea un vector de índices aleatorios que representan un subconjunto
 * de elementos sobre los cuales se realizarán búsquedas.
 * 
 * @param W Cantidad de elementos en el working set
 * @return std::vector<int> Vector de índices aleatorios
 */
std::vector<int> gen_working_set(int W) {
    int N = 1 << 25;  // Tamaño total: 2^25
    std::uniform_int_distribution<int> dist(1, N);

    std::vector <int> v(W);
    for (int i = 0; i < W; i++){
        v.push_back(dist(gen));
    }
    return v;
}

/**
 * @brief Genera un número aleatorio en el rango [0, UINT32_MAX]
 * @return uint32_t Número aleatorio generado
 */
uint32_t distribucion() {
    std::uniform_int_distribution<uint32_t> dist(0, UINT32_MAX);
    return dist(gen);
}

// ============================================================================
// GENERACIÓN DE DATASETS
// ============================================================================

/**
 * @brief Genera datasets de diferentes tamaños
 * Crea archivos dataset_10.txt hasta dataset_14.txt
 * Cada archivo contiene 2^i números aleatorios (i de 10 a 14)
 * 
 * Esta función NO se llama en el programa principal pero puede usarse
 * para generar los datasets de prueba.
 */
void construction_dataset() {
  for (int i = 10; i < 15; i++) {
    int N = 1 << i;  // N = 2^i
    std::ofstream out("dataset_" + std::to_string(i) + ".txt");

    // Escribir N números aleatorios
    for (int j = 0; j < N; j++) {
      out << distribucion() << '\n';
    }
  }
  return;
}

// ============================================================================
// PRUEBAS BASE: ESCENARIOS PRINCIPALES
// ============================================================================

/**
 * @brief Realiza pruebas base con diferentes escenarios
 * 
 * Escenarios probados:
 * 1. Construcción aleatoria + búsquedas uniformes
 * 2. Construcción aleatoria + búsquedas sesgadas
 * 3. Construcción ordenada + búsquedas uniformes
 * 4. Construcción ordenada + búsquedas sesgadas
 * 
 * Se prueba con datasets de tamaño 2^10 a 2^14
 * Para cada tamaño N, se realizan M = 10*N búsquedas
 * 
 * Se comparan AVL Tree y Splay Tree en cada escenario
 */
void construction() {
  int c = 1;

  // Variables para medición de tiempo
  auto inicio = std::chrono::high_resolution_clock::now();
  auto fin = std::chrono::high_resolution_clock::now();
  auto tiempo =
      std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);

  // Iterar sobre tamaños de dataset: 2^10 a 2^14
  for (int i = 10; i < 15; i++) {
    int N = 1 << i;              // Tamaño del dataset (2^i)
    int M = 10 * c * N;          // Cantidad de búsquedas
    
    // Leer el dataset
    std::vector<uint32_t> valores = leerDataset("dataset_" + std::to_string(i) + ".txt");
    
    // Imprimir encabezado
    std::cout << "-------------------- 2^" << i << " --------------------"
              << std::endl;

    // ====================================================================
    // ESCENARIO 1: Construcción aleatoria + Búsquedas uniformes
    // ====================================================================
    std::cout << "---- Aleatoria, uniforme ---" << std::endl;
    
    // --- AVL Tree ---
    std::cout << "- AVL -" << std::endl;
    {
      AVLTree avl_tree;
      
      // Medir tiempo de construcción
      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.build_random(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      // Medir tiempo de búsquedas uniformes
      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.uniform_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    // --- Splay Tree ---
    std::cout << "- Splay -" << std::endl;
    {
      SplayTree splay_tree;
      
      // Medir tiempo de construcción
      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.build_random(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      // Medir tiempo de búsquedas uniformes
      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.uniform_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    // ====================================================================
    // ESCENARIO 2: Construcción aleatoria + Búsquedas sesgadas
    // ====================================================================
    std::cout << "---- Aleatoria, sesgada ---" << std::endl;
    
    // --- AVL Tree ---
    std::cout << "- AVL -" << std::endl;
    {
      AVLTree avl_tree;
      
      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.build_random(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.biased_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    // --- Splay Tree ---
    std::cout << "- Splay -" << std::endl;
    {
      SplayTree splay_tree;
      
      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.build_random(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.biased_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    // ====================================================================
    // ESCENARIO 3: Construcción ordenada + Búsquedas uniformes
    // ====================================================================
    std::cout << "---- Ordenada, uniforme ---" << std::endl;
    
    // --- AVL Tree ---
    std::cout << "- AVL -" << std::endl;
    {
      AVLTree avl_tree;
      
      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.build_ordered(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.uniform_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    // --- Splay Tree ---
    std::cout << "- Splay -" << std::endl;
    {
      SplayTree splay_tree;
      
      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.build_ordered(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.uniform_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    // ====================================================================
    // ESCENARIO 4: Construcción ordenada + Búsquedas sesgadas
    // ====================================================================
    std::cout << "---- Ordenada, sesgada ---" << std::endl;
    
    // --- AVL Tree ---
    std::cout << "- AVL -" << std::endl;
    {
      AVLTree avl_tree;
      
      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.build_ordered(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.biased_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    // --- Splay Tree ---
    std::cout << "- Splay -" << std::endl;
    {
      SplayTree splay_tree;
      
      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.build_ordered(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.biased_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }
  }
  return;
}

// ============================================================================
// PRUEBAS DE TEOREMAS
// ============================================================================

/**
 * @brief Genera un dataset grande para pruebas de teoremas
 * Crea dataset_25.txt con 2^25 números aleatorios
 * Este archivo se utiliza en las pruebas de teoremas
 * 
 * Esta función NO se llama en el programa principal pero puede usarse
 * para generar el dataset para las pruebas de teoremas.
 */
void construction_dataset_25() {
  int N = 1 << 25;  // N = 2^25
  std::ofstream out("dataset_25.txt");
  
  // Escribir 2^25 números aleatorios
  for (int i = 0; i < N; i++) {
    out << distribucion() << '\n';
  }
  return;
}

/**
 * @brief Realiza pruebas de dos teoremas fundamentales
 * 
 * Teorema 1: Sequential Access Theorem
 *   Afirma que el Splay Tree es óptimo para accesos secuenciales
 *   Prueba con diferentes valores de m (1*N/100 a 10*N/100)
 * 
 * Teorema 2: Working Set Theorem
 *   Afirma que el Splay Tree es óptimo para accesos a un working set
 *   Prueba con diferentes tamaños W (10^1 a 10^6)
 * 
 * Esta función NO se llama en el programa principal pero puede usarse
 * para ejecutar las pruebas de teoremas.
 */
void construction_teo() {
  int N = 1 << 25;  // N = 2^25
  AVLTree avl_tree;
  SplayTree splay_tree;
  
  // Variables para medición de tiempo
  auto inicio = std::chrono::high_resolution_clock::now();
  auto fin = std::chrono::high_resolution_clock::now();
  auto tiempo =
      std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
  
  // ====================================================================
  // TEOREMA 1: Sequential Access Theorem
  // ====================================================================
  std::cout << "-------------------- Sequential Acess Theorem --------------------"
            << std::endl;

  // Leer el dataset y construir ambos árboles
  std::vector<uint32_t> valores = leerDataset("dataset_25.txt");
  avl_tree.build(valores);
  splay_tree.build(valores);
  
  // Pruebar con diferentes valores de m
  for (int i = 1; i < 11; i++) {
      int m = i * (N / 100);  // m = i * N / 100
  
      std::cout << "---- m = " << i << "*N/100 ---" << std::endl;
      
      // --- AVL Tree ---
      std::cout << "- AVL -" << std::endl;
      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.seq_access(m);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;

      // --- Splay Tree ---
      std::cout << "- Splay Tree -" << std::endl;
      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.seq_access(m);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
  }

  // ====================================================================
  // TEOREMA 2: Working Set Theorem
  // ====================================================================
  std::cout << "-------------------- Working Set Theorem --------------------"
            << std::endl;
  
  // Reconstruir árboles limpios
  avl_tree.build(valores);
  splay_tree.build(valores);
  
  int W = 1;            // Tamaño inicial del working set
  int c = 1;            // Constante para M
  int M = 10 * c * N;   // Cantidad de búsquedas
  std::vector<int> working_set_i;
  
  // Probar con diferentes tamaños de working set: 10^1 a 10^6
  for (int i = 1; i < 7; i++) {
      W *= 10;  // W = 10^i
      working_set_i = gen_working_set(W);
      
      std::cout << "---- W = 10^" << i << " ---" << std::endl;
      
      // --- AVL Tree ---
      std::cout << "- AVL -" << std::endl;
      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.work_set(valores, working_set_i, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;

      // --- Splay Tree ---
      std::cout << "- Splay Tree -" << std::endl;
      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.work_set(valores, working_set_i, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
  }
  return;
}



