CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Directorios
SRC_DIR = src
INCLUDE_DIR = include

# Targets principales
all: create_tree search_value

create_tree: $(SRC_DIR)/create_tree.cpp $(SRC_DIR)/tree.cpp 
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

search_value: $(SRC_DIR)/search_value.cpp $(SRC_DIR)/tree.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

test_load: $(SRC_DIR)/test_load.cpp $(SRC_DIR)/tree.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

nearest_x: $(SRC_DIR)/create_tree.cpp $(SRC_DIR)/tree.cpp $(SRC_DIR)/sort-tile-recursive.cpp 
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

test:  $(SRC_DIR)/globals.cpp   $(SRC_DIR)/tree.cpp  $(SRC_DIR)/construction.cpp $(SRC_DIR)/consultas.cpp $(SRC_DIR)/sort-tile-recursive.cpp  $(SRC_DIR)/nearest-x.cpp $(SRC_DIR)/main.cpp 
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

clean:
	rm -f create_tree search_value tree.bin test_load

.PHONY: all clean
