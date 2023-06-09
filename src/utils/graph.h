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
#include <cmath>

#define EARTH_RADIUS (double)6371000.0

struct Edge{
    int origin;
    int dest;
    double distance;
};

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

class Graph {
    public:
        Graph(bool dir);

        int getNumVertices() const;

        int getNumEdges() const;

        bool isDirected() const;

        // vertex exists
        bool vertexExists(int vertex);

        //get lat
        double getLat(int vertex);

        //get longi
        double getLongi(int vertex);

        //get label
        std::string getLabel(int vertex);

        //get vertices
        std::unordered_map<int, vertexNode> getVertices();

        //get distance
        double getDistance(int v1, int v2);

        void setVertexInfo(int vertex, double lat, double longi);

        bool addVertex(int vertex, double lat, double longi, std::string label);

        // add edge from v1 to v2, and from v2 to v1 if directed
        void addEdge(int v1, int v2, double distance);

        void printGraph();

        void tsp_backtrack(std::vector<int>& path, std::vector<bool>& visited, double& min_cost, double cost_so_far);

        std::vector<std::pair<int, int>> primMST(std::vector<int>& parent);

        void dfs(int current, const std::vector<int>& parent, std::vector<bool>& visited, std::stack<int>& cityStack, std::vector<int>& path);

        double calculateTotalDistance(const std::vector<int>& path);

        double triangularApproximation();

        bool check_if_nodes_are_connected(int v1, int v2);

        double haversine(double lat1, double lon1, double lat2, double lon2);

        std::vector<int> nearestNeighbour(int start_vertex);


    protected:
        int num_edges;
        bool directed;

        std::unordered_map<int, vertexNode> vertices;

};

#endif