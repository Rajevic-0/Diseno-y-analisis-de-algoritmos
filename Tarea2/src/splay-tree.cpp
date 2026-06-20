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

NODO* SplayTree::splay(NODO* raizArbol, int x) {
    if (raizArbol == nullptr) return nullptr;

    NODO cabecera(0);          
    NODO* L = &cabecera;       
    NODO* R = &cabecera;       
    NODO* nodo = raizArbol;

    while (true) {
        if (x < nodo->valor) {
            if (nodo->izq == nullptr) break;

            if (x < nodo->izq->valor) {
                NODO* hijo = nodo->izq;
                nodo->izq = hijo->der;
                hijo->der = nodo;
                nodo = hijo;
                if (nodo->izq == nullptr) break;
            }

            R->izq = nodo;
            R = nodo;
            nodo = nodo->izq;

        } else if (x > nodo->valor) {
            if (nodo->der == nullptr) break;

            if (x > nodo->der->valor) {
                NODO* hijo = nodo->der;
                nodo->der = hijo->izq;
                hijo->izq = nodo;
                nodo = hijo;
                if (nodo->der == nullptr) break;
            }

            L->der = nodo;
            L = nodo;
            nodo = nodo->der;

        } else {
            break; 
        }
    }

    L->der = nodo->izq;
    R->izq = nodo->der;
    nodo->izq = cabecera.der;
    nodo->der = cabecera.izq;

    return nodo;
}
NODO* SplayTree::search(int x) {
    raiz = splay(raiz, x);
    if (raiz != nullptr && raiz->valor == x)
        return raiz;
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

void SplayTree::seq_access(const std::vector<uint32_t>& valores, uint64_t M) {
    size_t N = valores.size();
    std::vector<uint32_t> val_ordenados = valores;
    std::sort(val_ordenados.begin(), val_ordenados.end());
    size_t indice = 0;
    for (uint64_t k = 0; k < M; k++) {
        search(val_ordenados[indice]);
        indice += 2;
        if (indice >= N) indice = N - 1;
    }
}

void SplayTree::work_set(const std::vector<uint32_t>& valores, const std::vector<int>& working_set_i, int M) {
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