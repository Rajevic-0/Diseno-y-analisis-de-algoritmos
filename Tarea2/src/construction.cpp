#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>
#include <cstdint>

#include "../include/splay-tree.hpp"
#include "../include/avl-tree.hpp"

std::mt19937 gen(std::random_device{}());

std::vector<uint32_t> leerDataset(const std::string& filename) {
    std::ifstream file(filename);

    std::vector<uint32_t> valores;
    uint32_t valor;

    while (file >> valor) {
        valores.push_back(valor);
    }

    return valores;
}

std::vector<int> gen_working_set(int W) {
    int N = 1 << 25;
    std::uniform_int_distribution<int> dist(1, N);

    std::vector <int> v(W);
    for (int i = 0; i < W; i++){
        v.push_back(dist(gen));
    }
    return v;
}

uint32_t distribucion() {
    std::uniform_int_distribution<uint32_t> dist(0, UINT32_MAX);

    return dist(gen);
}


void construction_dataset() {
  for (int i = 10; i < 15; i++) {
    int N = 1 << i;
    std::ofstream out("dataset_" + std::to_string(i) + ".txt");

    for (int j = 0; j < N; j++) {
      out << distribucion() << '\n';
    }
  }
  return;
}

// Escenarios Base
void construction() {
  int c = 1;

  auto inicio = std::chrono::high_resolution_clock::now();
  auto fin = std::chrono::high_resolution_clock::now();
  auto tiempo =
      std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);

  for (int i = 10; i < 15; i++) {
    int N = 1 << i;
    int M = 10*c * N;
    std::vector<uint32_t> valores = leerDataset("dataset_" + std::to_string(i) + ".txt");
    

    std::cout << "-------------------- 2^" << i << " --------------------"
              << std::endl;
    std::cout << "---- Aleatoria, uniforme ---" << std::endl;
    std::cout << "- AVL -" << std::endl;
    
    {
      AVLTree avl_tree;
      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.build_random(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.uniform_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    std::cout << "- Splay -" << std::endl;

    {
      SplayTree splay_tree;
      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.build_random(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.uniform_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    std::cout << "---- Aleatoria, sesgada ---" << std::endl;
    std::cout << "- AVL -" << std::endl;
    
    {
      AVLTree avl_tree;
      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.build_random(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.biased_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    std::cout << "- Splay -" << std::endl;

    {
      SplayTree splay_tree;
      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.build_random(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.biased_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    std::cout << "---- Ordenada, uniforme ---" << std::endl;
    std::cout << "- AVL -" << std::endl;
    
    {
      AVLTree avl_tree;
      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.build_ordered(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.uniform_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    std::cout << "- Splay -" << std::endl;

    {
      SplayTree splay_tree;
      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.build_ordered(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.uniform_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    std::cout << "---- Ordenada, sesgada ---" << std::endl;
    std::cout << "- AVL -" << std::endl;
    
    {
      AVLTree avl_tree;
      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.build_ordered(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.biased_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }

    std::cout << "- Splay -" << std::endl;

    {
      SplayTree splay_tree;
      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.build_ordered(valores);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de inserción: " << tiempo.count() << " milisegundos" << std::endl;

      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.biased_search(valores, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
    }
  }
  return;
}

// Teoremas
void construction_dataset_25() {
  int N = 1 << 25;
  std::ofstream out("dataset_25.txt");
  for (int i = 0; i < N; i++) {
    out << distribucion() << '\n';
  }
  return;
}

void construction_teo() {
  int N = 1 << 25;
  AVLTree avl_tree;
  SplayTree splay_tree;
  
  auto inicio = std::chrono::high_resolution_clock::now();
  auto fin = std::chrono::high_resolution_clock::now();
  auto tiempo =
      std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
  
  std::cout << "-------------------- Sequential Acess Theorem --------------------"
            << std::endl;

  std::vector<uint32_t> valores = leerDataset("dataset_25.txt");
  avl_tree.build(valores);
  splay_tree.build(valores);
  
  for (int i = 1; i < 11; i++) {
      int m = i*(N/100);
  
      std::cout << "---- m = " << i << "*N/100 ---" << std::endl;
      std::cout << "- AVL -" << std::endl;
      
      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.seq_access(N, m);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;

      std::cout << "- Splay Tree -" << std::endl;
      
      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.seq_access(N, m);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
  }

  std::cout << "-------------------- Working Set Theorem --------------------"
            << std::endl;
  avl_tree.build(valores);
  splay_tree.build(valores);
  
  int W = 1;
  int c = 1;
  int M = 10*c * N;
  std::vector<int> working_set_i;
  for (int i = 1; i < 7; i++) {
      W *= 10;
      working_set_i = gen_working_set(W);
      
      std::cout << "---- W = 10^" << i << " ---" << std::endl;
      std::cout << "- AVL -" << std::endl;
      
      inicio = std::chrono::high_resolution_clock::now();
      avl_tree.work_set(valores, working_set_i, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;

      std::cout << "- Splay Tree -" << std::endl;
      
      inicio = std::chrono::high_resolution_clock::now();
      splay_tree.work_set(valores, working_set_i, N, M);
      fin = std::chrono::high_resolution_clock::now();
      tiempo =
          std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
      std::cout << "Tiempo de busqueda: " << tiempo.count() << " milisegundos" << std::endl;
  }
  return;
}



