#ifndef PROJETO2DA_GRAPH_H
#define PROJETO2DA_GRAPH_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <limits>
#include <stack>

struct Edge{
    int origin;
    int dest;
    double distance;
};

class Graph {
    public:
        Graph(bool dir);

        int getNumVertices() const;

        int getNumEdges() const;

        bool isDirected() const;

        // vertex exists
        bool vertexExists(int vertexID);

        void setVertexInfo(int vertex, double lat, double longi);

        bool addVertex(int vertex, double lat, double longi, std::string label);

        // add edge from v1 to v2, and from v2 to v1 if directed
        void addEdge(int v1, int v2, double distance);

        void removeEdge(int v1, int v2);

        void removeAdjEdges(int v);

        void printGraph();

        void tsp_backtrack(std::vector<int>& path, std::vector<bool>& visited, double& min_cost, double cost_so_far);

        int minKey(std::vector<double>& key, std::vector<bool>& inMST);

        void primMST(std::vector<int>& parent);

        void dfs(int current, const std::vector<int>& parent, std::vector<bool>& visited, std::stack<int>& cityStack, std::vector<int>& path);

        double calculateTotalDistance(const std::vector<int>& path);

        double triangularApproximation();

    protected:
        int num_edges;
        bool directed;

        struct edgeNode{
            int vertex; //dest vertex
            double distance;
        };

        struct vertexNode{
            int vertex;
            double lat;
            double longi;
            std::string label;

            std::vector<edgeNode> adj;
        };

        std::vector<vertexNode> vertices;
};

#endif