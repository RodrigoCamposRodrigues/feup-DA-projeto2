//
// Created by lulaz on 5/30/23.
//

#include "menu.h"
#include "../manager.h"

/// @brief Constrói um objeto Menu, responsável por gerenciar o menu do programa.
Menu::Menu() : m("../dataset/Extra_Fully_Connected_Graphs/edges_900.csv") {}
void Menu::menuLoop() {
    while(!exited) {
        switch (menuState) {
            case -1:
                graphSelectionMenu();
                break;
            case 0:
                algorithmSelectionMenu();
                break;
            case 1:
                break;
            case 2:
                break;
            default:
                std::cout << "Invalid menu state" << std::endl;
                break;
        }
    }
}

/// @brief Imprime o menu que permite selecionar diferentes grafos.
void Menu::graphSelectionMenu() {
    while((menuState == -1) && !exited) {
        std::cout << "Select a graph:" << std::endl;
        std::cout << "1 - shipping.csv (Toy-Graph)" << std::endl;
        std::cout << "2 - stadiums.csv (Toy-Graph)" << std::endl;
        std::cout << "3 - tourism.csv (Toy-Graph)" << std::endl;
        std::cout << "4 - graph1 (Real-World-Graph)" << std::endl;
        std::cout << "5 - graph2 (Real-World-Graph)" << std::endl;
        std::cout << "6 - graph3 (Real-World-Graph)" << std::endl;
        std::cout << "7 - select an extra graph from Extra_Fully_Connected_Graphs folder" << std::endl;
        std::cout << "0 - Exit" << std::endl;
        std::cout << "Option: ";
        int option = -1;
        std::cin >> option;
        switch (option) {
            case 0:
                exited = true;
                break;
            case 1: {
                m = Manager("../dataset/Toy-Graphs/shipping.csv");
                m.initialize_graphs_with_1_file();
                menuState = 0;
                break;
            }
            case 2: {
                m = Manager("../dataset/Toy-Graphs/stadiums.csv");
                m.initialize_graphs_with_1_file();
                menuState = 0;
                break;
            }
            case 3: {
                m = Manager("../dataset/Toy-Graphs/tourism.csv");
                m.initialize_graphs_with_1_file();
                menuState = 0;
                break;
            }
            case 4: {
                m = Manager("../dataset/Real-World-Graphs/graph1/nodes.csv",
                            "../dataset/Real-World-Graphs/graph1/edges.csv");
                m.initialize_graphs_with_2_files();
                menuState = 0;
                break;
            }
            case 5: {
                m = Manager("../dataset/Real-World-Graphs/graph2/nodes.csv",
                            "../dataset/Real-World-Graphs/graph2/edges.csv");
                m.initialize_graphs_with_2_files();
                menuState = 0;
                break;
            }
            case 6: {
                m = Manager("../dataset/Real-World-Graphs/graph3/nodes.csv",
                            "../dataset/Real-World-Graphs/graph3/edges.csv");
                m.initialize_graphs_with_2_files();
                menuState = 0;
                break;
            }
            case 7: {
                std::cout << "Enter the name of the file (without the .csv extension): ";
                std::string filename;
                std::cin >> filename;

                std::string edge_path = EXTRA_FULLY_CONNECTED_GRAPHS_PATH + filename + ".csv";
                std::cout << "nodes_path: " << edge_path << std::endl;
                m = Manager(edge_path.c_str());
                m.initialize_graphs_with_1_file();
                menuState = 0;
                break;
            }
            default:
                std::cout << "Invalid option" << std::endl;
                break;
        }
    }
}

/// @brief Imprime o menu que permite aplicar um algoritmo a um grafo anteriormente selecionado.
void Menu::algorithmSelectionMenu() {
    while((menuState == 0) && !exited) {
        std::cout << "Select an algorithm:" << std::endl;
        std::cout << "1 - Backtracking" << std::endl;
        std::cout << "2 - Triangular Approximation" << std::endl;
        std::cout << "0 - Exit" << std::endl;
        std::cout << "Option: ";
        int option = -1;
        std::cin >> option;
        switch (option) {
            case 0:
                exited = true;
                break;
            case 1: {
                std::cout << "##############################################" << std::endl;
                m.backtrack_tsp();
                std::cout << "##############################################" << std::endl;
                menuState = 0;
                break;
            }
            case 2: {
                std::cout << "##############################################" << std::endl;
                m.triangularApproximation();
                std::cout << "##############################################" << std::endl;
                menuState = 0;
                break;
            }
            default:
                std::cout << "Invalid option" << std::endl;
                break;
        }
    }
}
