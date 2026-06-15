NODO* ARBOL::splay(int x) {
    return splay(arbol.raiz, x);
}

NODO* ARBOL::splay(NODO* nodo, int x) {
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

        if (x < nodo->izq->valor) {
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

NODO* ARBOL::search(int x) {
    Nodo* nodo = raiz;
    Nodo* anterior = nullptr;

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

void ARBOL::insert(int x) {
    if (raiz == nullptr) {
        raiz = new Nodo(x);
        return;
    }

    Nodo* nodo = raiz;

    while (true) {
        if (x < nodo->valor) {
            if (nodo->izq == nullptr) {
                nodo->izq = new Nodo(x);
                break;
            }

            nodo = nodo->izq;
        } else if (x > nodo->valor) {
            if (nodo->der == nullptr) {
                nodo->der = new Nodo(x);
                break;
            }
            
            nodo = nodo->der;
        } else {
            return raiz;
        }
    }

    return splay(x);
}