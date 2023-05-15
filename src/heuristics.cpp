#include "utils/graph.h"

void Graph::tsp_backtrack(std::vector<int>& path, std::vector<bool>& visited, double& min_cost, double cost_so_far) {
    // Base case: if all vertices have been visited, check if the current cycle is a Hamiltonian cycle
    if (path.size() == num_vertices) {
        // Check if the last vertex is adjacent to the starting vertex
        int start_vertex = path.front();
        int last_vertex = path.back();
        for (auto edge : vertices[last_vertex].adj) {
            if (edge.vertex == start_vertex) {
                // If it is, this is a Hamiltonian cycle; update the minimum cost if necessary
                double cycle_cost = cost_so_far + edge.distance;
                if (cycle_cost < min_cost) {
                    min_cost = cycle_cost;
                }
                break;
            }
        }
        return;
    }

    // Recursively consider all unvisited neighbors of the last vertex in the current path
    int last_vertex = path.back();
    for (auto edge : vertices[last_vertex].adj) {
        if (!visited[edge.vertex]) {
            // Add the next vertex to the current path
            path.push_back(edge.vertex);
            visited[edge.vertex] = true;
            // Recursively explore the updated path
            tsp_backtrack(path, visited, min_cost, cost_so_far + edge.distance);
            // Remove the last vertex from the path and mark it as unvisited for the next iteration
            path.pop_back();
            visited[edge.vertex] = false;
        }
    }
}




