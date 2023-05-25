#ifndef PROJETODA2_MANAGER_H
#define PROJETODA2_MANAGER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iostream>

#include "utils/csv_reader.h"
#include "utils/graph.h"

class Manager {
public:

    Manager();
    Manager (const char *nodes_file, const char *edges_file);
    Manager (const char *f_name);

    void initialize_graphs_with_2_files();

    void initialize_graphs_with_1_file(); // TODO implement

    void backtrack_tsp();

    void printGraph();

    void test();

    void triangularApproximation();

    double degrees_to_radians(double degrees);

    double haversine(double lat1, double lon1, double lat2, double lon2);

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