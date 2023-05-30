#include <iostream>
#include "utils/csv_reader.h"
#include "utils/graph.h"
#include "manager.h"
#include "menu/menu.h"

int main() {
//    Manager manager("../dataset/Extra_Fully_Connected_Graphs/edges_900.csv");

//    manager.initialize_graphs_with_1_file();
    //manager.printGraph();
    //manager.backtrack_tsp();
//    manager.triangularApproximation();
    Menu menu = Menu();
    menu.menuLoop();
    return 0;
}
