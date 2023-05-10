#include "manager.h"

#include <iostream>

Manager::Manager(const char *nodes_file, const char *edges_file) : 
    nodes_reader(nodes_file),
    edges_reader(edges_file),
    delivery_graph(false) {}

void Manager::initialize_all(){
    std::vector<std::string> line;

    while(!nodes_reader.is_eof()){
        line = nodes_reader.read_line();
        if(line.size() == 3){
            delivery_graph.addVertex(std::stoi(line[0]), std::stod(line[1]), std::stod(line[2]));
        }
    }

    while(!edges_reader.is_eof()){
        line = edges_reader.read_line();
        if(line.size() == 3){
            delivery_graph.addEdge(std::stoi(line[0]), std::stoi(line[1]), std::stod(line[2]));
        }
    }   
}

void Manager::printGraph(){
    delivery_graph.printGraph();
}

