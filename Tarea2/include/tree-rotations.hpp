#ifndef TREE_ROTATIONS_HPP
#define TREE_ROTATIONS_HPP

/**
 * @brief Estructura que representa un nodo de árbol binario de búsqueda
 */
struct NODO {
    int valor;
    NODO* izq;
    NODO* der;
    int altura; // Para AVL
    
    NODO(int val) : valor(val), izq(nullptr), der(nullptr), altura(1) {}
};

/**
 * @brief Clase base con operaciones de rotación compartidas
 * Proporciona las 6 rotaciones fundamentales usadas en árboles balanceados
 */
class TreeRotations {
protected:
    /**
     * @brief Zig: Rotación simple a la izquierda (caso hijo izquierdo de raíz)
     */
    NODO* zig(NODO* nodo);
    
    /**
     * @brief Zag: Rotación simple a la derecha (caso hijo derecho de raíz)
     */
    NODO* zag(NODO* nodo);
    
    /**
     * @brief Zig-Zig: Dos rotaciones izquierda-izquierda
     */
    NODO* zigZig(NODO* nodo);
    
    /**
     * @brief Zag-Zag: Dos rotaciones derecha-derecha
     */
    NODO* zagZag(NODO* nodo);
    
    /**
     * @brief Zig-Zag: Rotación izquierda-derecha (casos mixtos)
     */
    NODO* zigZag(NODO* nodo);
    
    /**
     * @brief Zag-Zig: Rotación derecha-izquierda (casos mixtos)
     */
    NODO* zagZig(NODO* nodo);
};

#endif
