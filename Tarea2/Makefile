CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -O2

# Directorios
SRC_DIR = src
INCLUDE_DIR = include

# Targets principales
all: create_tree search_value

construction:  $(SRC_DIR)/construction.cpp $(SRC_DIR)/avl-tree.cpp $(SRC_DIR)/splay-tree.cpp  $(SRC_DIR)/tree-rotations.cpp $(SRC_DIR)/main.cpp 
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

bonus:  $(SRC_DIR)/globals.cpp   $(SRC_DIR)/tree.cpp  $(SRC_DIR)/construction.cpp $(SRC_DIR)/consultas.cpp $(SRC_DIR)/sort-tile-recursive.cpp  $(SRC_DIR)/nearest-x.cpp $(SRC_DIR)/main.cpp 
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

clean:
	rm -f construction bonus

.PHONY: all clean
