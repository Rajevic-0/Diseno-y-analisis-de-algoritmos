/*
 * ============================================================================
 * avl-tree.hpp
 * ============================================================================
 * Archivo de encabezado para la implementación de un Árbol AVL (Adelson-Velskii
 * and Landis tree). Un árbol binario de búsqueda auto-balanceado que mantiene
 * la propiedad de que para cada nodo, la diferencia de altura entre sus
 * subárboles izquierdo y derecho es como máximo 1.
 * ============================================================================
 */

#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "tree-rotations.hpp"
#include <vector>
#include <cstdint>

/**
 * @class AVLTree
 * @brief Implementación de un Árbol AVL (Adelson-Velskii and Landis)
 * 
 * Un árbol binario de búsqueda balanceado que mantiene automáticamente el
 * balance mediante rotaciones después de cada inserción. La propiedad de
 * balance garantiza que las operaciones de búsqueda, inserción y eliminación
 * tengan complejidad O(log n).
 * 
 * Hereda de TreeRotations para usar las operaciones de rotación.
 */
class AVLTree : public TreeRotations {
private: 
    NODO *raiz;                              ///< Puntero a la raíz del árbol
    
    /**
     * @brief Obtiene la altura de un nodo
     * @param nodo Nodo del cual se obtiene la altura
     * @return int Altura del nodo (0 si es nullptr)
     */
    int getAltura(NODO* nodo);
    
    /**
     * @brief Calcula el factor de balance de un nodo
     * Factor de balance = altura(izquierda) - altura(derecha)
     * El árbol está balanceado si el factor está entre -1 y 1
     * 
     * @param nodo Nodo del cual se calcula el balance
     * @return int Factor de balance del nodo
     */
    int getBalance(NODO* nodo);
    
    /**
     * @brief Inserción recursiva en el árbol
     * @param nodo Nodo actual en la recursión
     * @param x Valor a insertar
     * @return NODO* Nuevo nodo raíz del subárbol después de la inserción y rebalanceo
     */
    NODO* insert(NODO* nodo, int x);
    
    /**
     * @brief Búsqueda recursiva en el árbol
     * @param nodo Nodo actual en la recursión
     * @param x Valor a buscar
     * @return NODO* Puntero al nodo encontrado o nullptr si no existe
     */
    NODO* search(NODO* nodo, int x);
    
    /**
     * @brief Libera recursivamente la memoria de todos los nodos del árbol
     * @param nodo Nodo actual siendo liberado
     */
    void clearRec(NODO* nodo); 

public:
    /**
     * @brief Constructor del árbol AVL
     * Inicializa un árbol vacío
     */
    AVLTree() : raiz(nullptr) {}
    
    /**
     * @brief Inserta un valor en el árbol
     * Mantiene automáticamente el balance del árbol
     * 
     * @param x Valor a insertar
     */
    void insert(int x);
    
    /**
     * @brief Busca un valor en el árbol
     * @param x Valor a buscar
     * @return NODO* Puntero al nodo encontrado o nullptr
     */
    NODO* search(int x);
    
    /**
     * @brief Obtiene la raíz del árbol
     * @return NODO* Puntero a la raíz
     */
    NODO* getRoot() const { return raiz; }

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
};

#endif