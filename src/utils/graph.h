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
#include <climits>

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

        void setVertexInfo(int vertex, double lat, double longi);

        bool addVertex(int vertex, double lat, double longi);

        // add edge from v1 to v2, and from v2 to v1 if directed
        void addEdge(int v1, int v2, double distance);

        void removeEdge(int v1, int v2);

        void removeAdjEdges(int v);

        void printGraph();

    protected:
        int num_vertices;
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

            std::list<edgeNode> adj;
        };

        std::vector<vertexNode> vertices; 
};

#endif