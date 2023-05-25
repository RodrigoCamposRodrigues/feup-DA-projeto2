#include <iostream>
#include "utils/csv_reader.h"
#include "utils/graph.h"
#include "manager.h"

int main() {
    Manager manager("../dataset/Real-World-Graphs/graph1/nodes.csv", "../dataset/Real-World-Graphs/graph1/edges.csv");

    manager.initialize_graphs_with_2_files();
    manager.printGraph();
    //manager.backtrack_tsp();
    //manager.triangularApproximation();
    return 0;
}
