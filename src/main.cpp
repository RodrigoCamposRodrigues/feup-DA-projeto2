#include <iostream>
#include "utils/csv_reader.h"
#include "utils/graph.h"
#include "manager.h"

int main() {
    Manager manager("../dataset/Toy-Graphs/shipping.csv");

    manager.initialize_selected();
    manager.printGraph();
    std::cout << manager.backtrack_tsp() << std::endl;
    return 0;
}
