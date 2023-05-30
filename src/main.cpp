#include <iostream>
#include "utils/csv_reader.h"
#include "utils/graph.h"
#include "manager.h"

int main() {
    Manager manager("../dataset/Toy-Graphs/stadiums.csv");

    manager.initialize_graphs_with_1_file();
    //manager.printGraph();
    //manager.backtrack_tsp();
    //manager.triangularApproximation();
    manager.test();
    return 0;
}
