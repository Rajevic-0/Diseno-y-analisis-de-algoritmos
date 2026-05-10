#include "../include/bulk_loading.hpp"
#include "../include/creation.hpp"
#include "../include/rtree.hpp"
#include <chrono>
#include <iostream>
#include <vector>
int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr
        << "Uso:\n  1) ./test construction <archivo1.bin> <archivo2.bin>\n"
        << "  2) ./test query" << std::endl;
    return 1;
  }
  std::string bonus = argv[0];
  std::string type = argv[1];
  if (bonus.contains("bonus")) {
    if (type == "construction") {
      std::string path = argv[2];
      bonus_construction(path);
    } else if (type == "query")
      bonus_query();
    return 0;
  } else {
    if (type == "construction") {
      if (argc < 4) {
        std::cerr << "Uso: ./test construction <archivo1.bin> <archivo2.bin>"
                  << std::endl;
        return 1;
      }
      std::string path1 = argv[2], path2 = argv[3];
      construction(path1, path2);
    } else if (type == "query")
      r_query();
    return 0;
  }
}
