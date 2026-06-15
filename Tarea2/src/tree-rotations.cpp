#include "../include/tree-rotations.hpp"

// Zig: Rotación simple a la izquierda (caso hijo izquierdo de raíz)
NODO* TreeRotations::zig(NODO* nodo) {
    NODO* temp = nodo->izq;
    nodo->izq = temp->der;
    temp->der = nodo;
    return temp;
}

// Zag: Rotación simple a la derecha (caso hijo derecho de raíz)
NODO* TreeRotations::zag(NODO* nodo) {
    NODO* temp = nodo->der;
    nodo->der = temp->izq;
    temp->izq = nodo;
    return temp;
}

//  Zig-Zig: Dos rotaciones izquierda-izquierda
NODO* TreeRotations::zigZig(NODO* nodo) {
    nodo->izq = zig(nodo->izq);
    return zig(nodo);
}

// Zag-Zag: Dos rotaciones derecha-derecha
NODO* TreeRotations::zagZag(NODO* nodo) {
    nodo->der = zag(nodo->der);
    return zag(nodo);
}

// Zig-Zag: Rotación izquierda-derecha (casos mixtos)
NODO* TreeRotations::zigZag(NODO* nodo) {
    nodo->izq = zag(nodo->izq);
    return zig(nodo);
}

// Zag-Zig: Rotación derecha-izquierda (casos mixtos)
NODO* TreeRotations::zagZig(NODO* nodo) {
    nodo->der = zig(nodo->der);
    return zag(nodo);
}
