/*
 * ============================================================================
 * tree-rotations.hpp
 * ============================================================================
 * Archivo de encabezado para las operaciones de rotación compartidas entre
 * diferentes tipos de árboles binarios de búsqueda balanceados.
 * Define la estructura base de un nodo y la clase TreeRotations con las
 * rotaciones fundamentales utilizadas en AVL Trees y Splay Trees.
 * ============================================================================
 */

#ifndef TREE_ROTATIONS_HPP
#define TREE_ROTATIONS_HPP

/**
 * @struct NODO
 * @brief Estructura que representa un nodo de árbol binario de búsqueda
 * 
 * Cada nodo contiene:
 * - valor: el dato almacenado en el nodo
 * - izq: puntero al hijo izquierdo
 * - der: puntero al hijo derecho
 * - altura: la altura del nodo (utilizada en AVL para el balanceo)
 */
struct NODO {
    int valor;          ///< Valor/clave almacenado en el nodo
    NODO* izq;          ///< Puntero al hijo izquierdo
    NODO* der;          ///< Puntero al hijo derecho
    int altura;         ///< Altura del nodo (usado en AVL Tree)
    
    /**
     * @brief Constructor que inicializa un nodo con un valor
     * @param val Valor a almacenar en el nodo
     */
    NODO(int val) : valor(val), izq(nullptr), der(nullptr), altura(1) {}
};

/**
 * @class TreeRotations
 * @brief Clase base con operaciones de rotación compartidas
 * 
 * Proporciona las 6 rotaciones fundamentales usadas en árboles balanceados:
 * - Zig y Zag (rotaciones simples)
 * - Zig-Zig y Zag-Zag (rotaciones dobles del mismo lado)
 * - Zig-Zag y Zag-Zig (rotaciones dobles de lados opuestos)
 * 
 * Esta clase es una clase base que es heredada por AVLTree y SplayTree
 * para utilizar estas operaciones de rotación.
 */
class TreeRotations {
protected:
    /**
     * @brief Zig: Rotación simple a la izquierda
     * Usado en casos donde el desbalanceo está en el hijo izquierdo de la raíz
     * 
     * @param nodo Nodo sobre el cual se realiza la rotación
     * @return NODO* Nuevo nodo raíz después de la rotación
     * 
     * Operación:        Antes:              Después:
     *                     nodo                temp
     *                    /                      \
     *                 temp         -->          nodo
     *                   \                       /
     */
    NODO* zig(NODO* nodo);
    
    /**
     * @brief Zag: Rotación simple a la derecha
     * Usado en casos donde el desbalanceo está en el hijo derecho de la raíz
     * 
     * @param nodo Nodo sobre el cual se realiza la rotación
     * @return NODO* Nuevo nodo raíz después de la rotación
     * 
     * Operación:        Antes:              Después:
     *                     nodo                temp
     *                        \               /
     *                       temp   -->    nodo
     *                       /                \
     */
    NODO* zag(NODO* nodo);
    
    /**
     * @brief Zig-Zig: Dos rotaciones a la izquierda
     * Usado cuando tanto el nodo como su hijo izquierdo tienen desbalanceo a la izquierda
     * 
     * @param nodo Nodo sobre el cual se realiza la rotación
     * @return NODO* Nuevo nodo raíz después de las dos rotaciones
     */
    NODO* zigZig(NODO* nodo);
    
    /**
     * @brief Zag-Zag: Dos rotaciones a la derecha
     * Usado cuando tanto el nodo como su hijo derecho tienen desbalanceo a la derecha
     * 
     * @param nodo Nodo sobre el cual se realiza la rotación
     * @return NODO* Nuevo nodo raíz después de las dos rotaciones
     */
    NODO* zagZag(NODO* nodo);
    
    /**
     * @brief Zig-Zag: Rotación izquierda-derecha
     * Usado cuando el hijo izquierdo tiene desbalanceo a la derecha
     * 
     * @param nodo Nodo sobre el cual se realiza la rotación
     * @return NODO* Nuevo nodo raíz después de las dos rotaciones
     */
    NODO* zigZag(NODO* nodo);
    
    /**
     * @brief Zag-Zig: Rotación derecha-izquierda
     * Usado cuando el hijo derecho tiene desbalanceo a la izquierda
     * 
     * @param nodo Nodo sobre el cual se realiza la rotación
     * @return NODO* Nuevo nodo raíz después de las dos rotaciones
     */
    NODO* zagZig(NODO* nodo);
};

#endif

