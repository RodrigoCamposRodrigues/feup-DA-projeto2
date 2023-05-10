#include "utils/graph.h"

void Graph::backtrack_tsp(std::vector<bool>& visited, int current, int n, int count, int cost, double& ans){

    //if last node is reached and has link to the first node, keep the minimum value of the total cost of traversal and ans
    //Finally return to check for more possible values
    if (count == n && vertices[current].adj.front().vertex == 0){
        ans = std::min(ans, cost + vertices[current].adj.front().distance);
        return;
    }

    for (auto& edge : vertices[current].adj) {
        int nextVertex = edge.vertex;
        double edgeDistance = edge.distance;

        if (!visited[nextVertex]) {
            // Mark as visited
            visited[nextVertex] = true;
            backtrack_tsp(visited, nextVertex, n, count + 1,
                cost + edgeDistance, ans);
            std::cout << "Está a correr o backtrack_tsp" << std::endl;

            // Mark nextVertex node as unvisited
            visited[nextVertex] = false;
        }
    }
}


