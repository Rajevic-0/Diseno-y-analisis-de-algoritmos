/*
 * ============================================================================
 * splay-tree.cpp
 * ============================================================================
 * Implementación del Árbol Splay. Este archivo contiene la implementación
 * de la operación fundamental de splaying, así como inserción, búsqueda
 * y funciones de prueba. Un árbol Splay es auto-balanceado mediante la
 * operación de splay que lleva elementos recientemente accedidos a la raíz.
 * ============================================================================
 */

#include <algorithm>
#include <fstream>
#include <string>
#include <random>
#include <cstdint>

#include "../include/splay-tree.hpp"

// ============================================================================
// OPERACIÓN PRINCIPAL: SPLAY
// ============================================================================

/**
 * @brief Realiza la operación de splay (interfaz pública)
 * Lleva el nodo con valor x a la raíz del árbol.
 * Complejidad amortizada: O(log n)
 * 
 * @param x Valor del nodo a llevar a la raíz
 * @return NODO* Puntero al nodo ahora en la raíz
 */
NODO* SplayTree::splay(int x) {
    raiz = splay(raiz, x);
    return raiz;
}

/**
 * @brief Operación de splay (implementación interna)
 * 
 * El splay es el algoritmo central del árbol Splay. Utiliza una técnica
 * de "buffer" para evitar crear nuevas estructuras de datos mientras
 * reorganiza el árbol. La idea es llevar el nodo buscado (o su posición)
 * a la raíz mediante rotaciones.
 * 
 * Algoritmo:
 * 1. Mantiene dos "buffers" L y R para los subárboles izquierdo y derecho
 * 2. Busca el valor x mientras realiza rotaciones:
 *    - Zig-zig: si la búsqueda va dos niveles en la misma dirección
 *    - Zig-zag: si alterna direcciones
 *    - Zig: último paso al encontrar el valor
 * 3. Reconecta L y R con el árbol reorganizado
 * 
 * Complejidad: O(n) en el peor caso, O(log n) amortizado
 * 
 * @param raizArbol Raíz del árbol siendo splayed
 * @param x Valor del nodo a llevar a la raíz
 * @return NODO* Nuevo nodo raíz después del splay
 */
NODO* SplayTree::splay(NODO* raizArbol, int x) {
    // Árbol vacío
    if (raizArbol == nullptr) return nullptr;

    // Crear nodo centinela (dummy) para simplificar la lógica de conexión
    NODO cabecera(0);
    
    // L apunta a la raíz del subárbol derecho que se está construyendo (para valores < x)
    NODO* L = &cabecera;
    
    // R apunta a la raíz del subárbol izquierdo que se está construyendo (para valores > x)
    NODO* R = &cabecera;
    
    // Nodo actual siendo procesado
    NODO* nodo = raizArbol;

    // Proceso principal de splay
    while (true) {
        // Buscar en el subárbol izquierdo
        if (x < nodo->valor) {
            // Si no hay hijo izquierdo, el nodo actual es el más cercano a x
            if (nodo->izq == nullptr) break;

            // Caso Zig-Zig: x < hijo.valor (continuar a la izquierda)
            if (x < nodo->izq->valor) {
                // Realizar rotación Zig en el hijo izquierdo
                NODO* hijo = nodo->izq;
                nodo->izq = hijo->der;
                hijo->der = nodo;
                nodo = hijo;
                
                // Si después de la rotación no hay más hijo izquierdo, terminar
                if (nodo->izq == nullptr) break;
            }

            // Conectar el nodo actual al buffer derecho (valores > x)
            R->izq = nodo;
            R = nodo;
            nodo = nodo->izq;

        // Buscar en el subárbol derecho
        } else if (x > nodo->valor) {
            // Si no hay hijo derecho, el nodo actual es el más cercano a x
            if (nodo->der == nullptr) break;

            // Caso Zig-Zig: x > hijo.valor (continuar a la derecha)
            if (x > nodo->der->valor) {
                // Realizar rotación Zag en el hijo derecho
                NODO* hijo = nodo->der;
                nodo->der = hijo->izq;
                hijo->izq = nodo;
                nodo = hijo;
                
                // Si después de la rotación no hay más hijo derecho, terminar
                if (nodo->der == nullptr) break;
            }

            // Conectar el nodo actual al buffer izquierdo (valores < x)
            L->der = nodo;
            L = nodo;
            nodo = nodo->der;

        // Valor encontrado exactamente
        } else {
            break; 
        }
    }

    // Reconectar los buffers con el nodo ahora en la raíz
    L->der = nodo->izq;           // Conectar subárbol izquierdo
    R->izq = nodo->der;           // Conectar subárbol derecho
    nodo->izq = cabecera.der;     // Nodo recibe buffer izquierdo (valores < x)
    nodo->der = cabecera.izq;     // Nodo recibe buffer derecho (valores > x)

    return nodo;
}

// ============================================================================
// MÉTODOS BÁSICOS: BÚSQUEDA E INSERCIÓN
// ============================================================================

/**
 * @brief Busca un valor en el árbol
 * Realiza un splay del valor buscado, trayéndolo (o su posición) a la raíz.
 * Si el valor existe, estará en la raíz después del splay.
 * Complejidad amortizada: O(log n)
 * 
 * @param x Valor a buscar
 * @return NODO* Puntero al nodo encontrado o nullptr si no existe
 */
NODO* SplayTree::search(int x) {
    // Realizar splay del valor x
    raiz = splay(raiz, x);
    
    // Verificar si el valor está realmente en la raíz
    if (raiz != nullptr && raiz->valor == x)
        return raiz;
    return nullptr;
}

/**
 * @brief Inserta un valor en el árbol
 * 
 * Proceso:
 * 1. Si el árbol está vacío, crear nuevo nodo como raíz
 * 2. Buscar la posición correcta para insertar (como en BST normal)
 * 3. Insertar el nuevo nodo
 * 4. Realizar splay del nuevo nodo para llevarlo a la raíz
 * 
 * Complejidad amortizada: O(log n)
 * 
 * @param x Valor a insertar
 */
void SplayTree::insert(int x) {
    // Caso especial: árbol vacío
    if (raiz == nullptr) {
        raiz = new NODO(x);
        return;
    }

    // Buscar la posición correcta para insertar
    NODO* nodo = raiz;

    while (true) {
        if (x < nodo->valor) {
            if (nodo->izq == nullptr) {
                // Insertar como hijo izquierdo
                nodo->izq = new NODO(x);
                break;
            }
            nodo = nodo->izq;
        } else if (x > nodo->valor) {
            if (nodo->der == nullptr) {
                // Insertar como hijo derecho
                nodo->der = new NODO(x);
                break;
            }
            nodo = nodo->der;
        } else {
            // Duplicado: no insertar
            return;
        }
    }

    // Llevar el nuevo nodo a la raíz mediante splay
    splay(x);
}

// ============================================================================
// MÉTODOS DE CONSTRUCCIÓN DEL ÁRBOL
// ============================================================================

/**
 * @brief Construye el árbol insertando valores en orden original
 * Complejidad: O(n log n) amortizado
 * 
 * @param valores Vector de valores a insertar
 */
void SplayTree::build(const std::vector<uint32_t>& valores) {
    for (uint32_t x: valores) {
        insert(x);
    }
}

/**
 * @brief Construye el árbol insertando valores en orden aleatorio
 * Realiza un shuffle de los valores antes de insertarlos.
 * Complejidad: O(n log n) amortizado
 * 
 * @param valores Vector de valores a insertar
 */
void SplayTree::build_random(const std::vector<uint32_t>& valores) {
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
 * Complejidad: O(n log n) amortizado
 * 
 * @param valores Vector de valores a insertar
 */
void SplayTree::build_ordered(const std::vector<uint32_t>& valores) {
    std::vector<uint32_t> val_ordenados = valores;

    // Crear generador de números aleatorios
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
 * Complejidad: O(M log n) amortizado
 * 
 * @param valores Vector de valores del cual seleccionar búsquedas
 * @param N Cantidad de valores disponibles
 * @param M Cantidad de búsquedas a realizar
 */
void SplayTree::uniform_search(const std::vector<uint32_t>& valores, int N, int M) {
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
double funcion_p(int N, int i) {
    // Parámetro lambda de la distribución exponencial
    double lambda = 0.025; 

    // Fórmula de distribución exponencial normalizada
    return std::exp(-lambda * i) * (1.0 - std::exp(-lambda)) / (1.0 - std::exp(-lambda * N));
}

/**
 * @brief Pre-calcula distribución acumulativa para generación eficiente de índices
 * Crea un vector donde cada posición i contiene la suma acumulativa de
 * probabilidades hasta ese índice.
 * 
 * @param N Cantidad de elementos
 * @return std::vector<double> Vector de probabilidades acumulativas
 */
std::vector<double> vector_funcion_p(int N) {
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
int gen_indice_exp(const std::vector<double>& c_dist) {
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
 * Complejidad: O(M log n) amortizado
 * 
 * @param valores Vector de valores del cual seleccionar búsquedas
 * @param N Cantidad de valores disponibles
 * @param M Cantidad de búsquedas a realizar
 */
void SplayTree::biased_search(const std::vector<uint32_t>& valores, int N, int M) {
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
 * Complejidad: O(M log n) amortizado
 * 
 * @param valores Vector de valores a acceder
 * @param M Cantidad de accesos a realizar
 */
void SplayTree::seq_access(const std::vector<uint32_t>& valores, uint64_t M) {
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
 * Complejidad: O(M log W) amortizado, donde W es el tamaño del working set
 * 
 * @param valores Vector completo de valores
 * @param working_set_i Vector de índices que forman el conjunto de trabajo
 * @param M Cantidad de búsquedas a realizar dentro del working set
 */
void SplayTree::work_set(const std::vector<uint32_t>& valores, const std::vector<int>& working_set_i, int M) {
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
void SplayTree::clear() {
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
void SplayTree::clearRec(NODO* nodo) {
    if (nodo == nullptr) return;
    
    // Liberar subárbol izquierdo
    clearRec(nodo->izq);
    
    // Liberar subárbol derecho
    clearRec(nodo->der);
    
    // Liberar nodo actual
    delete nodo;
}