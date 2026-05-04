#include "rtree.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<RTreeNode> s_t_r(const std::string &path, const int n);
std::vector<RTreeNode> nearest_x(const std::string &path, const int n);
