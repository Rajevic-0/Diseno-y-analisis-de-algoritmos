#include <algorithm>
#include <fstream>
#include <string>
#include <cstdint>
#include <random>
#include "../include/avl-tree.hpp"

int AVLTree::getAltura(NODO* nodo){
    return (nodo==nullptr) ? 0 : nodo->altura;
}

int AVLTree::getBalance(NODO* nodo) {
    if (nodo==nullptr) return 0;
    return getAltura(nodo->izq) - getAltura(nodo->der);
}

NODO* AVLTree::search(int x) {
    return search(raiz,x);
}

NODO* AVLTree::search(NODO* nodo, int x) {
    if (nodo==nullptr || nodo->valor==x) return nodo;
    if (x<nodo->valor) return search(nodo->izq,x);
    return search(nodo->der,x);
}

void AVLTree::insert(int x) {
    raiz = insert(raiz,x);
}

NODO* AVLTree:: insert(NODO* nodo, int x) {
    if (nodo==nullptr) {
        return new NODO(x);
    }
    if (x<nodo->valor) {
        nodo->izq = insert(nodo->izq,x);
    } else if (x>nodo->valor) {
        nodo->der = insert(nodo->der,x);
    } else {
        return nodo;
    }

    nodo->altura = 1 + std::max(getAltura(nodo->izq),getAltura(nodo->der));
    int balance = getBalance(nodo);
    
    if (balance > 1) {
        if (getBalance(nodo->izq)>=0) return zig(nodo);
        else return zigZag(nodo);
    }

    if (balance < -1) {
        if (getBalance(nodo->der)<=0) return zag(nodo);
        else return zagZig(nodo);
    }
    return nodo;
}

void AVLTree::build(const std::vector<uint32_t>& valores) {
    for (uint32_t x: valores) {
        insert(x);
    }
}

void AVLTree::build_random(const std::vector<uint32_t>& valores) {
    std::vector<uint32_t> val_random = valores;

    std::mt19937 gen(std::random_device{}());
    std::shuffle(val_random.begin(), val_random.end(), gen);

    for (uint32_t x: val_random) {
        insert(x);
    }
}

void AVLTree::build_ordered(const std::vector<uint32_t>& valores) {
    std::vector<uint32_t> val_ordenados = valores;

    std::mt19937 gen(std::random_device{}());
    std::sort(val_ordenados.begin(), val_ordenados.end());

    for (uint32_t x: val_ordenados) {
        insert(x);
    }
}

void AVLTree::uniform_search(const std::vector<uint32_t>& valores, int N, int M) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, N - 1);

    for (int i = 0; i < M; i++) {
        search(valores[dist(gen)]);
    }
}


static double funcion_p(int N, int i) {
    double lambda = 0.025; 

    return std::exp(-lambda * i) * (1.0 - std::exp(-lambda)) / (1.0 - std::exp(-lambda * N));
}

static std::vector<double> vector_funcion_p(int N) {
    std::vector<double> c_dist(N);

    double acum = 0.0;

    for (int i = 0; i < N; i++) {
        acum += funcion_p(N, i);
        c_dist[i] = acum;
    }

    c_dist[N - 1] = 1.0;
    return c_dist;
}

static int gen_indice_exp(const std::vector<double>& c_dist) {
    double a = (double) rand() / RAND_MAX;

    auto it = std::lower_bound(
        c_dist.begin(),
        c_dist.end(),
        a
    );

    return it - c_dist.begin();
}


void AVLTree::biased_search(const std::vector<uint32_t>& valores, int N, int M) {
    auto c_dist = vector_funcion_p(N);

    for (int i = 0; i < M; i++) {
        int k = gen_indice_exp(c_dist);
        search(valores[k]);
    }
}

void AVLTree::seq_access(int m) {
    uint32_t val = 0;

    for (int i = 0; i < m; i++) {
        search(val);
        val += 1000;
    }
}

void AVLTree::work_set(const std::vector<uint32_t>& valores, const std::vector<int>& working_set_i, int M) {
    int W = working_set_i.size();
    std::vector<uint32_t> working_set(W);
    for (int i = 0; i < W; i++) {
        working_set[i] = valores[working_set_i[i]];
    }
    uniform_search(working_set, W, M);
}

void AVLTree::clear() {
    clearRec(raiz);
    raiz = nullptr;
}

void AVLTree::clearRec(NODO* nodo) {
    if (nodo == nullptr) return;
    clearRec(nodo->izq);
    clearRec(nodo->der);
    delete nodo;
}