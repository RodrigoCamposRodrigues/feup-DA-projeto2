#ifndef PROJETODA2_MANAGER_H
#define PROJETODA2_MANAGER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

#include "utils/csv_reader.h"

class Manager {
public:
    Manager (const char *nodes_file, const char *edges_file);

    void initialize_all();

    void initialize_selected(std::vector<std::string> lines); // TODO implement

    void printGraph();

    void test();

private:
    CsvReader nodes_reader;
    CsvReader edges_reader;

    // graph structure
    Graph delivery_graph;
    
    // subgraph structure for use without select segments
    // Graph sub_graph;

    // hash map of strings to vertex numbers
    std::unordered_map<std::string, int> vertex_map;
};

#endif //PROJETODA2_MANAGER_H