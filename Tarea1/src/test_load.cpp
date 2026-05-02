#include "../include/rtree.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./test_load <archivo.bin>" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    std::vector<std::pair<float, float>> puntos = TreeUtils::load(path);

    if (puntos.empty()) {
        std::cerr << "No se pudieron cargar puntos de: " << path << std::endl;
        return 1;
    }

    std::cout << "--- Verificación de los primeros 32 puntos ---" << std::endl;
    std::cout << std::fixed << std::setprecision(6);

    int limite = std::min((int)puntos.size(), 32);
    for (int i = 0; i < limite; ++i) {
        std::cout << i + 1 << ": (" << puntos[i].first << ", " << puntos[i].second << ")" << std::endl;
    }

    std::cout << "Total de puntos cargados en memoria: " << puntos.size() << std::endl;
    return 0;
}
