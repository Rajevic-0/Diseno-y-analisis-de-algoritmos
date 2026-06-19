#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "tree-rotations.hpp"
#include <vector>
#include <cstdint>

class AVLTree : public TreeRotations {
private: 
    NODO *raiz;
    int getAltura(NODO* nodo);
    int getBalance(NODO* nodo);
    NODO* insert(NODO* nodo, int x);
    NODO* search(NODO* nodo, int x);
    void clearRec(NODO* nodo); 

public:
    AVLTree() : raiz(nullptr) {}
    
    void insert(int x);
    
    NODO* search(int x);
    
    NODO* getRoot() const { return raiz; }

    void build(const std::vector<uint32_t>& valores);
    void build_random(const std::vector<uint32_t>& valores);
    void build_ordered(const std::vector<uint32_t>& valores);
    void uniform_search(const std::vector<uint32_t>& valores, int N, int M);
    void biased_search(const std::vector<uint32_t>& valores, int N, int M);
    void seq_access(int N, int m);
    void work_set(const std::vector<uint32_t>& valores, const std::vector<int>& working_set_i, int N, int M);

    void clear();
};

#endif