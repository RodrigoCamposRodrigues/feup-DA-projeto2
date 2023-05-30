//
// Created by lulaz on 5/30/23.
//

#ifndef PROJETO2DA_MENU_H
#define PROJETO2DA_MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../manager.h"

#define TOY_GRAPH_PATH "../dataset/Toy-Graphs/"
#define REAL_WORLD_GRAPH_PATH "../dataset/Real-World-Graphs/"
#define EXTRA_FULLY_CONNECTED_GRAPHS_PATH "../dataset/Extra_Fully_Connected_Graphs/"

class Menu {
public:
    Menu();

    void menuLoop();
private:
    void graphSelectionMenu(); // -1
    void algorithmSelectionMenu(); // 0

    Manager m;
    int menuState = -1; // -1 means a graph has not been selected yet
    bool exited = false;
};

#endif //PROJETO2DA_MENU_H
