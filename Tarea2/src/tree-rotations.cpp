/*
 * ============================================================================
 * tree-rotations.cpp
 * ============================================================================
 * Implementación de las operaciones de rotación para árboles binarios de búsqueda
 * balanceados. Las rotaciones son operaciones fundamentales que mantienen la
 * estructura de BST mientras reorganizan los nodos para mejorar el balance.
 * ============================================================================
 */

#include "../include/tree-rotations.hpp"

/**
 * @brief Zig: Rotación simple a la izquierda
 * 
 * Rotación de un nodo padre con su hijo izquierdo. El hijo izquierdo se
 * convierte en el nuevo padre, y el padre original se convierte en el
 * hijo derecho del nuevo padre.
 * 
 * Estructura antes:       Estructura después:
 *        nodo                   temp
 *       /    \                 /    \
 *     temp    d     -->       a      nodo
 *    /   \                        /    \
 *   a     c                      c      d
 * 
 * @param nodo Nodo sobre el cual se realiza la rotación
 * @return NODO* Nuevo nodo raíz después de la rotación (temp)
 */
NODO* TreeRotations::zig(NODO* nodo) {
    NODO* temp = nodo->izq;
    nodo->izq = temp->der;
    temp->der = nodo;
    return temp;
}

/**
 * @brief Zag: Rotación simple a la derecha
 * 
 * Rotación de un nodo padre con su hijo derecho. El hijo derecho se
 * convierte en el nuevo padre, y el padre original se convierte en el
 * hijo izquierdo del nuevo padre.
 * 
 * Estructura antes:       Estructura después:
 *        nodo                   temp
 *       /    \                 /    \
 *      a     temp    -->     nodo    d
 *          /    \           /   \
 *         b      d         a     b
 * 
 * @param nodo Nodo sobre el cual se realiza la rotación
 * @return NODO* Nuevo nodo raíz después de la rotación (temp)
 */
NODO* TreeRotations::zag(NODO* nodo) {
    NODO* temp = nodo->der;
    nodo->der = temp->izq;
    temp->izq = nodo;
    return temp;
}

/**
 * @brief Zig-Zig: Dos rotaciones a la izquierda
 * 
 * Se aplica cuando el nodo y su hijo izquierdo tienen ambos el desbalanceo
 * a la izquierda (el hijo izquierdo tiene a su vez un hijo izquierdo desbalanceado).
 * Se realizan dos rotaciones zig seguidas.
 * 
 * @param nodo Nodo sobre el cual se realiza la doble rotación
 * @return NODO* Nuevo nodo raíz después de las dos rotaciones
 */
NODO* TreeRotations::zigZig(NODO* nodo) {
    nodo->izq = zig(nodo->izq);
    return zig(nodo);
}

/**
 * @brief Zag-Zag: Dos rotaciones a la derecha
 * 
 * Se aplica cuando el nodo y su hijo derecho tienen ambos el desbalanceo
 * a la derecha (el hijo derecho tiene a su vez un hijo derecho desbalanceado).
 * Se realizan dos rotaciones zag seguidas.
 * 
 * @param nodo Nodo sobre el cual se realiza la doble rotación
 * @return NODO* Nuevo nodo raíz después de las dos rotaciones
 */
NODO* TreeRotations::zagZag(NODO* nodo) {
    nodo->der = zag(nodo->der);
    return zag(nodo);
}

/**
 * @brief Zig-Zag: Rotación izquierda-derecha
 * 
 * Se aplica cuando el nodo tiene desbalanceo a la izquierda pero su hijo
 * izquierdo tiene desbalanceo a la derecha (casos opuestos/anidados).
 * Primero se realiza una rotación zag en el hijo, luego una zig en el padre.
 * 
 * @param nodo Nodo sobre el cual se realiza la doble rotación
 * @return NODO* Nuevo nodo raíz después de las dos rotaciones
 */
NODO* TreeRotations::zigZag(NODO* nodo) {
    nodo->izq = zag(nodo->izq);
    return zig(nodo);
}

/**
 * @brief Zag-Zig: Rotación derecha-izquierda
 * 
 * Se aplica cuando el nodo tiene desbalanceo a la derecha pero su hijo
 * derecho tiene desbalanceo a la izquierda (casos opuestos/anidados).
 * Primero se realiza una rotación zig en el hijo, luego una zag en el padre.
 * 
 * @param nodo Nodo sobre el cual se realiza la doble rotación
 * @return NODO* Nuevo nodo raíz después de las dos rotaciones
 */
NODO* TreeRotations::zagZig(NODO* nodo) {
    nodo->der = zig(nodo->der);
    return zag(nodo);
}
