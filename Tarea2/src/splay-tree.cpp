#include <algorithm>
#include <fstream>
#include <string>
#include <random>
#include <cstdint>

#include "../include/splay-tree.hpp"

NODO* SplayTree::splay(int x) {
    raiz = splay(raiz, x);
    return raiz;
}

NODO* SplayTree::splay(NODO* nodo, int x) {
    if (nodo == nullptr || nodo->valor == x)
        return nodo;

    if (x < nodo->valor) {
        if (nodo->izq == nullptr)
            return nodo;

        if (x < nodo->izq->valor) {
            nodo->izq->izq = splay(nodo->izq->izq, x);
            return zigZig(nodo);
        }    

        if (x > nodo->izq->valor) {
            nodo->izq->der = splay(nodo->izq->der, x);
            return zigZag(nodo);
        }    

        return zig(nodo);
    }

    else {
        if (nodo->der == nullptr)
            return nodo;

        if (x < nodo->der->valor) {
            nodo->der->izq = splay(nodo->der->izq, x);
            return zagZig(nodo);
        }    

        if (x > nodo->der->valor) {
            nodo->der->der = splay(nodo->der->der, x);
            return zagZag(nodo);
        }    

        return zag(nodo);
    }
} 

NODO* SplayTree::search(int x) {
    NODO* nodo = raiz;
    NODO* anterior = nullptr;

    while (nodo != nullptr) {
        anterior = nodo;

        if (x < nodo->valor) {
            nodo = nodo->izq;
        } else if (x > nodo->valor) {
            nodo = nodo->der;
        } else {
            splay(x);
            return raiz;
        }
    }
    
    if (anterior != nullptr) {
        splay(anterior->valor);
    }
    
    return nullptr;
}

void SplayTree::insert(int x) {
    if (raiz == nullptr) {
        raiz = new NODO(x);
        return;
    }

    NODO* nodo = raiz;

    while (true) {
        if (x < nodo->valor) {
            if (nodo->izq == nullptr) {
                nodo->izq = new NODO(x);
                break;
            }

            nodo = nodo->izq;
        } else if (x > nodo->valor) {
            if (nodo->der == nullptr) {
                nodo->der = new NODO(x);
                break;
            }
            
            nodo = nodo->der;
        } else {
            return;
        }
    }

    splay(x);
}

void SplayTree::build(const std::vector<uint32_t>& valores) {
    for (uint32_t x: valores) {
        insert(x);
    }
}

void SplayTree::build_random(const std::vector<uint32_t>& valores) {
    std::vector<uint32_t> val_random = valores;

    std::mt19937 gen(std::random_device{}());
    std::shuffle(val_random.begin(), val_random.end(), gen);

    for (uint32_t x: val_random) {
        insert(x);
    }
}

void SplayTree::build_ordered(const std::vector<uint32_t>& valores) {
    std::vector<uint32_t> val_ordenados = valores;

    std::mt19937 gen(std::random_device{}());
    std::sort(val_ordenados.begin(), val_ordenados.end());

    for (uint32_t x: val_ordenados) {
        insert(x);
    }
}

void SplayTree::uniform_search(const std::vector<uint32_t>& valores, int N, int M) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, N - 1);

    for (int i = 0; i < M; i++) {
        search(valores[dist(gen)]);
    }
}


double funcion_p(int N, int i) {
    double lambda = 0.025; 

    return std::exp(-lambda * i) * (1.0 - std::exp(-lambda)) / (1.0 - std::exp(-lambda * N));
}

std::vector<double> vector_funcion_p(int N) {
    std::vector<double> c_dist(N);

    double acum = 0.0;

    for (int i = 0; i < N; i++) {
        acum += funcion_p(N, i);
        c_dist[i] = acum;
    }

    c_dist[N - 1] = 1.0;
    return c_dist;
}

int gen_indice_exp(const std::vector<double>& c_dist) {
    double a = (double) rand() / RAND_MAX;

    auto it = std::lower_bound(
        c_dist.begin(),
        c_dist.end(),
        a
    );

    return it - c_dist.begin();
}


void SplayTree::biased_search(const std::vector<uint32_t>& valores, int N, int M) {
    auto c_dist = vector_funcion_p(N);

    for (int i = 0; i < M; i++) {
        int k = gen_indice_exp(c_dist);
        search(valores[k]);
    }
}

void SplayTree::seq_access(int N, int m) {
    uint32_t val = 0;

    for (int i = 0; i < m; i++) {
        search(val);
        val += 1000;
    }
}

void SplayTree::work_set(const std::vector<uint32_t>& valores, const std::vector<int>& working_set_i, int N, int M) {
    int W = working_set_i.size();
    std::vector<uint32_t> working_set(W);
    for (int i = 0; i < W; i++) {
        working_set[i] = valores[working_set_i[i]];
    }
    uniform_search(working_set, W, M);
}

void SplayTree::clear() {
    clearRec(raiz);
    raiz = nullptr;
}

void SplayTree::clearRec(NODO* nodo) {
    if (nodo == nullptr) return;
    clearRec(nodo->izq);
    clearRec(nodo->der);
    delete nodo;
}