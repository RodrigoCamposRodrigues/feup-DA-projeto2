#include <iostream>
#include "utils/csv_reader.h"
#include "utils/graph.h"
#include "manager.h"

int main() {
    Manager manager("../dataset/Toy-Graphs/shipping.csv");

    manager.initialize_selected();
    manager.printGraph();
    manager.backtrack_tsp();
    manager.triangularApproximation();
    return 0;
}
