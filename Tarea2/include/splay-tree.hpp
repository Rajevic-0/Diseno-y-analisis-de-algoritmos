/*
 * ============================================================================
 * splay-tree.hpp
 * ============================================================================
 * Archivo de encabezado para la implementación de un Árbol Splay (Splay Tree).
 * Un árbol binario de búsqueda auto-balanceado que utiliza la operación de
 * "splay" para llevar el elemento accedido a la raíz del árbol. Esto proporciona
 * excelente rendimiento para patrones de acceso sesgados.
 * ============================================================================
 */

#ifndef SPLAY_TREE_HPP
#define SPLAY_TREE_HPP

#include "tree-rotations.hpp"
#include <vector>
#include <cstdint>

/**
 * @class SplayTree
 * @brief Clase que implementa un árbol Splay (Self-Adjusting BST)
 * 
 * Un árbol binario de búsqueda auto-balanceado donde el elemento accedido
 * es llevado a la raíz mediante la operación de splaying (combinación inteligente
 * de rotaciones). Proporciona excelente rendimiento amortizado O(log n) y es
 * particularmente eficiente para accesos sesgados al árbol.
 * 
 * Características:
 * - No requiere información de balance en cada nodo
 * - Muy eficiente para patrones de acceso sesgados
 * - Excelente localidad de referencia
 * 
 * Hereda de TreeRotations para usar las operaciones de rotación.
 */
class SplayTree : public TreeRotations {
private:
    NODO* raiz;                              ///< Puntero a la raíz del árbol
    
    /**
     * @brief Operación de splay interna (recursiva)
     * Reorganiza el árbol llevando el nodo con valor x a la raíz
     * mediante una serie de rotaciones (zig, zag, zig-zig, etc.)
     * 
     * @param nodo Raíz del subárbol sobre el cual se realiza el splay
     * @param x Valor del nodo a llevar a la raíz
     * @return NODO* Nuevo nodo raíz después del splay
     */
    NODO* splay(NODO* nodo, int x);
    
public:
    /**
     * @brief Constructor del árbol Splay
     * Inicializa un árbol vacío
     */
    SplayTree() : raiz(nullptr) {}
    
    /**
     * @brief Realiza la operación de splay en un valor
     * Lleva el nodo con valor x a la raíz del árbol mediante rotaciones
     * 
     * @param x Valor del nodo a llevar a la raíz
     * @return NODO* Puntero al nodo ahora en la raíz
     */
    NODO* splay(int x);
    
    /**
     * @brief Busca un valor en el árbol
     * Realiza un splay del valor buscado (si existe) llevándolo a la raíz
     * 
     * @param x Valor a buscar
     * @return NODO* Puntero al nodo encontrado o nullptr si no existe
     */
    NODO* search(int x);
    
    /**
     * @brief Inserta un valor en el árbol
     * Inserta el valor siguiendo la estructura de BST y luego realiza
     * un splay para llevar el nuevo nodo a la raíz
     * 
     * @param x Valor a insertar
     */
    void insert(int x);

    /**
     * @brief Construye el árbol insertando todos los valores del vector
     * @param valores Vector de valores a insertar
     */
    void build(const std::vector<uint32_t>& valores);
    
    /**
     * @brief Construye el árbol con los valores en orden aleatorio
     * Primero los mezcla y luego los inserta
     * @param valores Vector de valores a insertar
     */
    void build_random(const std::vector<uint32_t>& valores);
    
    /**
     * @brief Construye el árbol con los valores en orden ordenado (ascendente)
     * @param valores Vector de valores a insertar
     */
    void build_ordered(const std::vector<uint32_t>& valores);
    
    /**
     * @brief Realiza búsquedas uniformes (aleatorias) en el árbol
     * Selecciona aleatoriamente M elementos del vector para buscar
     * 
     * @param valores Vector de valores del cual seleccionar búsquedas
     * @param N Cantidad de valores en el vector
     * @param M Cantidad de búsquedas a realizar
     */
    void uniform_search(const std::vector<uint32_t>& valores, int N, int M);
    
    /**
     * @brief Realiza búsquedas sesgadas (con distribución exponencial)
     * Los elementos más pequeños tienen mayor probabilidad de ser buscados
     * Simula el teorema de Working Set
     * 
     * @param valores Vector de valores del cual seleccionar búsquedas
     * @param N Cantidad de valores en el vector
     * @param M Cantidad de búsquedas a realizar
     */
    void biased_search(const std::vector<uint32_t>& valores, int N, int M);
    
    /**
     * @brief Realiza accesos secuenciales a los elementos ordenados
     * Simula el patrón de acceso secuencial con saltos de 2 posiciones
     * Utilizado para verificar el Teorema de Acceso Secuencial
     * 
     * @param valores Vector de valores a acceder
     * @param m Cantidad de accesos a realizar
     */
    void seq_access(const std::vector<uint32_t>& valores, uint64_t m); 
    
    /**
     * @brief Realiza búsquedas dentro de un conjunto de trabajo (working set)
     * Prueba el comportamiento del árbol cuando accede a un subconjunto específico
     * 
     * @param valores Vector completo de valores
     * @param working_set_i Vector de índices que forman el conjunto de trabajo
     * @param M Cantidad de búsquedas a realizar
     */
    void work_set(const std::vector<uint32_t>& valores, const std::vector<int>& working_set_i, int M); 

    /**
     * @brief Limpia el árbol, liberando toda la memoria
     */
    void clear(); 
    
    /**
     * @brief Libera recursivamente la memoria de todos los nodos del árbol
     * @param nodo Nodo actual siendo liberado
     */
    void clearRec(NODO* nodo); 
    
    /**
     * @brief Obtiene la raíz del árbol
     * @return NODO* Puntero a la raíz
     */
    NODO* getRoot() const { return raiz; }
};

#endif
