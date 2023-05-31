#include "utils/graph.h"

/// @brief Encontra o ciclo hamiltoniano de menor custo em um grafo.
/// Esta função tem complexidade O(n!), onde n é o número de vértices do grafo.
/// @param path Vetor de inteiros, onde cada inteiro é um vértice do ciclo.
/// @param visited Vetor de booleanos, onde cada booleano indica se o vértice correspondente já foi visitado.
/// @param min_cost Referência para o custo do ciclo hamiltoniano de menor custo encontrado até o momento.
/// @param cost_so_far Custo do ciclo hamiltoniano parcialmente construído até o momento.
/// @return Vetor de inteiros, onde cada inteiro é um vértice do ciclo.
void Graph::tsp_backtrack(std::vector<int>& path, std::vector<bool>& visited, double &min_cost, double cost_so_far) {
    // Base case: if all vertices have been visited, check if the current cycle is a Hamiltonian cycle
    if (path.size() == vertices.size()) {
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

/// @brief Calcula uma solução aproximada para o problema TSP, utilizando aproximação triangular.
/// É construída uma MST do grafo utilizando o algoritmo de Prim, e então é feita uma DFS na MST para obter a ordem de visitação das cidades.
/// Esta função tem complexidade O(V^2), onde V é o número de vértices do grafo.
/// @return Distância total percorrida na solução aproximada.
double Graph::triangularApproximation() {
    // Create the MST using Prim's algorithm
    std::vector<int> parent(vertices.size(), -1);
    primMST(parent);

    // Perform DFS traversal to obtain the order of visited cities
    std::vector<bool> visited(vertices.size(), false);
    std::vector<int> path;
    std::stack<int> cityStack;
    dfs(0, parent, visited, cityStack, path);

    // Print the order of visited cities
    std::cout << "Order of visited cities: ";
    for (int i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i != path.size() - 1)
            std::cout << " -> ";
    }
    std::cout << " -> 0"<< std::endl;

    double total_distance = calculateTotalDistance(path);

    return total_distance;
}




