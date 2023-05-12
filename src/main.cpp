#include <iostream>
#include "utils/csv_reader.h"
#include "utils/graph.h"
#include "manager.h"

int main() {
    Manager manager("../dataset/Real-World-Graphs/graph1/reduced_nodes.csv", "../dataset/Real-World-Graphs/graph1/reduced_edges.csv");

    manager.initialize_all();
    manager.printGraph();
    //std::cout << manager.backtrack_tsp() << std::endl;
    return 0;
}
