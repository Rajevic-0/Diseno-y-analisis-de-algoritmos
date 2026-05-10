#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include "rtree.hpp"
#include <vector>

/**
 * @brief Factor determinado por el exacto de cada nodo.
 */
extern int b;

/**
 * @brief Contenedor temporal de nodos durante el bulk-loading
 */
extern std::vector<RTreeNode> nodos;

#endif
