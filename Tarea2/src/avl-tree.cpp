/*
 * ============================================================================
 * avl-tree.cpp
 * ============================================================================
 * Implementación del Árbol AVL. Este archivo contiene la implementación de
 * todas las operaciones principales: inserción, búsqueda, rebalanceo y manejo
 * de memoria. Incluye también funciones de prueba para medir rendimiento.
 * ============================================================================
 */

#include <algorithm>
#include <fstream>
#include <string>
#include <cstdint>
#include <random>
#include "../include/avl-tree.hpp"

// ============================================================================
// MÉTODOS PRIVADOS DE UTILITY
// ============================================================================

/**
 * @brief Retorna la altura de un nodo
 * Complejidad: O(1)
 * 
 * @param nodo Nodo del cual obtener la altura
 * @return int Altura del nodo (0 si es nullptr)
 */
int AVLTree::getAltura(NODO* nodo){
    return (nodo==nullptr) ? 0 : nodo->altura;
}

/**
 * @brief Calcula el factor de balance de un nodo
 * El factor de balance es la diferencia entre las alturas del subárbol
 * izquierdo y el subárbol derecho. En un AVL tree bien balanceado, este
 * valor debe estar siempre entre -1 y 1.
 * 
 * Complejidad: O(1)
 * 
 * @param nodo Nodo del cual calcular el balance
 * @return int Balance del nodo (altura_izq - altura_der)
 */
int AVLTree::getBalance(NODO* nodo) {
    if (nodo==nullptr) return 0;
    return getAltura(nodo->izq) - getAltura(nodo->der);
}

// ============================================================================
// MÉTODOS PÚBLICOS BÁSICOS
// ============================================================================

/**
 * @brief Busca un valor en el árbol (interfaz pública)
 * Complejidad: O(log n)
 * 
 * @param x Valor a buscar
 * @return NODO* Puntero al nodo encontrado o nullptr
 */
NODO* AVLTree::search(int x) {
    return search(raiz, x);
}

/**
 * @brief Busca un valor en el árbol (implementación recursiva)
 * Realiza una búsqueda binaria estándar en el árbol.
 * Complejidad: O(log n) en promedio para un AVL balanceado
 * 
 * @param nodo Raíz del subárbol siendo buscado
 * @param x Valor a buscar
 * @return NODO* Puntero al nodo encontrado o nullptr
 */
NODO* AVLTree::search(NODO* nodo, int x) {
    if (nodo==nullptr || nodo->valor==x) return nodo;
    if (x<nodo->valor) return search(nodo->izq, x);
    return search(nodo->der, x);
}

/**
 * @brief Inserta un valor en el árbol (interfaz pública)
 * Complejidad: O(log n)
 * 
 * @param x Valor a insertar
 */
void AVLTree::insert(int x) {
    raiz = insert(raiz, x);
}

/**
 * @brief Inserta un valor en el árbol (implementación recursiva)
 * 
 * Proceso:
 * 1. Inserta el nodo como en un BST estándar
 * 2. Actualiza la altura del nodo
 * 3. Calcula el factor de balance
 * 4. Si el balance es > 1 o < -1, realiza la rotación apropiada
 * 
 * Complejidad: O(log n)
 * 
 * @param nodo Raíz del subárbol siendo insertado
 * @param x Valor a insertar
 * @return NODO* Nuevo nodo raíz del subárbol después del rebalanceo
 */
NODO* AVLTree::insert(NODO* nodo, int x) {
    // Caso base: crear nuevo nodo si está vacío
    if (nodo==nullptr) {
        return new NODO(x);
    }
    
    // Insertar en el subárbol izquierdo o derecho según el valor
    if (x < nodo->valor) {
        nodo->izq = insert(nodo->izq, x);
    } else if (x > nodo->valor) {
        nodo->der = insert(nodo->der, x);
    } else {
        // Duplicado: no se inserta
        return nodo;
    }

    // Actualizar altura del nodo actual
    nodo->altura = 1 + std::max(getAltura(nodo->izq), getAltura(nodo->der));
    
    // Obtener el factor de balance
    int balance = getBalance(nodo);
    
    // Caso izquierdo-izquierdo (LL) o izquierdo-derecho (LR)
    if (balance > 1) {
        // Si el hijo izquierdo tiene balance >= 0, es LL, usar zig
        // Si tiene balance < 0, es LR, usar zigZag
        if (getBalance(nodo->izq) >= 0) 
            return zig(nodo);
        else 
            return zigZag(nodo);
    }

    // Caso derecho-derecho (RR) o derecho-izquierdo (RL)
    if (balance < -1) {
        // Si el hijo derecho tiene balance <= 0, es RR, usar zag
        // Si tiene balance > 0, es RL, usar zagZig
        if (getBalance(nodo->der) <= 0) 
            return zag(nodo);
        else 
            return zagZig(nodo);
    }
    
    // Árbol balanceado, retornar nodo sin cambios
    return nodo;
}

// ============================================================================
// MÉTODOS DE CONSTRUCCIÓN DEL ÁRBOL
// ============================================================================

/**
 * @brief Construye el árbol insertando valores en orden original
 * Complejidad: O(n log n)
 * 
 * @param valores Vector de valores a insertar
 */
void AVLTree::build(const std::vector<uint32_t>& valores) {
    for (uint32_t x: valores) {
        insert(x);
    }
}

/**
 * @brief Construye el árbol insertando valores en orden aleatorio
 * Realiza un shuffle de los valores antes de insertarlos.
 * Esto produce un árbol más balanceado en promedio que insertar ordenados.
 * Complejidad: O(n log n)
 * 
 * @param valores Vector de valores a insertar
 */
void AVLTree::build_random(const std::vector<uint32_t>& valores) {
    std::vector<uint32_t> val_random = valores;

    // Crear generador de números aleatorios
    std::mt19937 gen(std::random_device{}());
    
    // Mezclar aleatoriamente
    std::shuffle(val_random.begin(), val_random.end(), gen);

    // Insertar valores mezclados
    for (uint32_t x: val_random) {
        insert(x);
    }
}

/**
 * @brief Construye el árbol insertando valores en orden ascendente
 * Complejidad: O(n log n)
 * 
 * @param valores Vector de valores a insertar
 */
void AVLTree::build_ordered(const std::vector<uint32_t>& valores) {
    std::vector<uint32_t> val_ordenados = valores;

    // Crear generador de números aleatorios (no utilizado pero presente en original)
    std::mt19937 gen(std::random_device{}());
    
    // Ordenar los valores
    std::sort(val_ordenados.begin(), val_ordenados.end());

    // Insertar valores ordenados
    for (uint32_t x: val_ordenados) {
        insert(x);
    }
}

// ============================================================================
// MÉTODOS DE PRUEBA: BÚSQUEDAS UNIFORMES Y SESGADAS
// ============================================================================

/**
 * @brief Realiza M búsquedas uniformes (aleatorias) en el árbol
 * Cada búsqueda selecciona un índice aleatorio del rango [0, N-1]
 * Complejidad: O(M log n)
 * 
 * @param valores Vector de valores del cual seleccionar búsquedas
 * @param N Cantidad de valores disponibles
 * @param M Cantidad de búsquedas a realizar
 */
void AVLTree::uniform_search(const std::vector<uint32_t>& valores, int N, int M) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, N - 1);

    // Realizar M búsquedas uniformes
    for (int i = 0; i < M; i++) {
        search(valores[dist(gen)]);
    }
}

// ============================================================================
// FUNCIONES PRIVADAS PARA BÚSQUEDAS SESGADAS
// ============================================================================

/**
 * @brief Función de distribución exponencial para búsquedas sesgadas
 * Genera una distribución exponencial con parámetro lambda = 0.025
 * Los elementos más pequeños (menores índices) tienen mayor probabilidad
 * Fórmula: e^(-lambda*i) * (1 - e^(-lambda)) / (1 - e^(-lambda*N))
 * 
 * @param N Cantidad total de elementos
 * @param i Índice del elemento (0 a N-1)
 * @return double Probabilidad de acceder a este elemento
 */
static double funcion_p(int N, int i) {
    // Parámetro lambda de la distribución exponencial
    double lambda = 0.025; 

    // Fórmula de distribución exponencial normalizada
    return std::exp(-lambda * i) * (1.0 - std::exp(-lambda)) / (1.0 - std::exp(-lambda * N));
}

/**
 * @brief Pre-calcula distribución acumulativa para generación eficiente de índices
 * Crea un vector donde cada posición i contiene la suma acumulativa de
 * probabilidades hasta ese índice. Esto permite usar binary search para
 * generar índices con la distribución deseada.
 * 
 * @param N Cantidad de elementos
 * @return std::vector<double> Vector de probabilidades acumulativas
 */
static std::vector<double> vector_funcion_p(int N) {
    std::vector<double> c_dist(N);

    double acum = 0.0;

    // Calcular probabilidades acumulativas
    for (int i = 0; i < N; i++) {
        acum += funcion_p(N, i);
        c_dist[i] = acum;
    }

    // Normalizar el último valor a 1.0 (por precisión numérica)
    c_dist[N - 1] = 1.0;
    return c_dist;
}

/**
 * @brief Genera un índice aleatorio según distribución exponencial
 * Usa el método de transformación inversa: genera un número aleatorio
 * uniforme y encuentra su posición en la distribución acumulativa
 * 
 * @param c_dist Vector de probabilidades acumulativas
 * @return int Índice generado según distribución exponencial
 */
static int gen_indice_exp(const std::vector<double>& c_dist) {
    // Generar número aleatorio uniforme en [0, 1]
    double a = (double) rand() / RAND_MAX;

    // Encontrar la posición de este número en la distribución acumulativa
    auto it = std::lower_bound(
        c_dist.begin(),
        c_dist.end(),
        a
    );

    return it - c_dist.begin();
}

/**
 * @brief Realiza M búsquedas con distribución sesgada (exponencial)
 * Los elementos de menor índice tienen mayor probabilidad de ser buscados.
 * Simula el Teorema del Working Set.
 * Complejidad: O(M log n)
 * 
 * @param valores Vector de valores del cual seleccionar búsquedas
 * @param N Cantidad de valores disponibles
 * @param M Cantidad de búsquedas a realizar
 */
void AVLTree::biased_search(const std::vector<uint32_t>& valores, int N, int M) {
    // Pre-calcular distribución acumulativa
    auto c_dist = vector_funcion_p(N);

    // Realizar M búsquedas con distribución sesgada
    for (int i = 0; i < M; i++) {
        int k = gen_indice_exp(c_dist);
        search(valores[k]);
    }
}

// ============================================================================
// MÉTODOS DE PRUEBA: ACCESO SECUENCIAL Y WORKING SET
// ============================================================================

/**
 * @brief Realiza M accesos secuenciales a elementos ordenados
 * Accede a los elementos en orden ascendente, saltando 2 posiciones cada vez.
 * Cuando llega al final, comienza desde la penúltima posición.
 * Prueba el Teorema de Acceso Secuencial.
 * Complejidad: O(M log n)
 * 
 * @param valores Vector de valores a acceder
 * @param M Cantidad de accesos a realizar
 */
void AVLTree::seq_access(const std::vector<uint32_t>& valores, uint64_t M) {
    size_t N = valores.size();
    std::vector<uint32_t> val_ordenados = valores;
    
    // Ordenar los valores
    std::sort(val_ordenados.begin(), val_ordenados.end());
    
    size_t indice = 0;
    
    // Realizar M accesos secuenciales con saltos de 2
    for (uint64_t k = 0; k < M; k++) {
        search(val_ordenados[indice]);
        indice += 2;
        // Si sobrepasa el final, ir a la penúltima posición
        if (indice >= N) indice = N - 1;
    }
}

/**
 * @brief Realiza M búsquedas dentro de un conjunto de trabajo específico
 * Prueba el comportamiento del árbol cuando accede repetidamente a un
 * subconjunto pequeño (working set) de los elementos.
 * Prueba el Teorema del Working Set.
 * Complejidad: O(M log W) donde W es el tamaño del working set
 * 
 * @param valores Vector completo de valores
 * @param working_set_i Vector de índices que forman el conjunto de trabajo
 * @param M Cantidad de búsquedas a realizar dentro del working set
 */
void AVLTree::work_set(const std::vector<uint32_t>& valores, const std::vector<int>& working_set_i, int M) {
    int W = working_set_i.size();
    
    // Extraer los valores del working set
    std::vector<uint32_t> working_set(W);
    for (int i = 0; i < W; i++) {
        working_set[i] = valores[working_set_i[i]];
    }
    
    // Realizar búsquedas uniformes dentro del working set
    uniform_search(working_set, W, M);
}

// ============================================================================
// MÉTODOS DE LIMPIEZA DE MEMORIA
// ============================================================================

/**
 * @brief Limpia el árbol, liberando toda la memoria asignada
 * Complejidad: O(n)
 */
void AVLTree::clear() {
    clearRec(raiz);
    raiz = nullptr;
}

/**
 * @brief Libera recursivamente la memoria de todos los nodos del árbol
 * Realiza un recorrido post-orden (izq, der, nodo) para asegurar que
 * los nodos hijos sean eliminados antes que el padre.
 * Complejidad: O(n)
 * 
 * @param nodo Nodo siendo liberado
 */
void AVLTree::clearRec(NODO* nodo) {
    if (nodo == nullptr) return;
    
    // Liberar subárbol izquierdo
    clearRec(nodo->izq);
    
    // Liberar subárbol derecho
    clearRec(nodo->der);
    
    // Liberar nodo actual
    delete nodo;
}