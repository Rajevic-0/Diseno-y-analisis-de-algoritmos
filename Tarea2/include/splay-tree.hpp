#ifndef SPLAY_TREE_HPP
#define SPLAY_TREE_HPP

#include "tree-rotations.hpp"
#include <vector>
#include <cstdint>

/**
 * @brief Clase que implementa un árbol Splay
 * Un árbol binario de búsqueda auto-balanceado donde el elemento 
 * accedido es llevado a la raíz mediante splaying
 */
class SplayTree : public TreeRotations {
private:
    NODO* raiz;
    
    NODO* splay(NODO* nodo, int x);
    
public:
    SplayTree() : raiz(nullptr) {}
    
    /**
     * @brief Realiza la operación de splay en un valor
     * Lleva el nodo con valor x a la raíz del árbol
     */
    NODO* splay(int x);
    
    /**
     * @brief Busca un valor en el árbol
     */
    NODO* search(int x);
    
    /**
     * @brief Inserta un valor en el árbol
     */
    void insert(int x);

    void build(const std::vector<uint32_t>& valores);
    void build_random(const std::vector<uint32_t>& valores);
    void build_ordered(const std::vector<uint32_t>& valores);
    void uniform_search(const std::vector<uint32_t>& valores, int N, int M);
    void biased_search(const std::vector<uint32_t>& valores, int N, int M);
    void seq_access(int N, int m); 
    void work_set(const std::vector<uint32_t>& valores, const std::vector<int>& working_set_i, int N, int M); 

    void clear(); 
    void clearRec(NODO* nodo); 
    
    /**
     * @brief Obtiene la raíz del árbol
     */
    NODO* getRoot() const { return raiz; }
};

#endif
