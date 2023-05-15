#include "graph.h"


/** Construtor da classe Graph.
 * Este método tem complexidade de tempo O(1).
 * @param dir true se o grafo for direcionado, false caso contrário.
*/
Graph::Graph(bool dir) : num_vertices(0), num_edges(0), directed(dir) {
    vertices = std::vector<vertexNode>();
}      

// getters
/** Retorna o número de vértices do grafo.
 * Este método tem complexidade de tempo O(1).
 * @return número de vértices do grafo.
*/
int Graph::getNumVertices() const {
    return num_vertices;
}

/** Retorna o número de arestas do grafo.
 * Este método tem complexidade de tempo O(1).
 * @return número de arestas do grafo.
*/
int Graph::getNumEdges() const {
    return num_edges;
}

/** Retorna se o grafo é direcionado ou não.
 * Este método tem complexidade de tempo O(1).
 * @return true se o grafo for direcionado, false caso contrário.
*/
bool Graph::isDirected() const {
    return directed;
}

/** Adiciona um vertice ao grafo.
 * Este método tem complexidade de tempo O(1).
 */
bool Graph::addVertex(int vertex, double lat, double longi, std::string label) {
    // check if index already exists
    if(vertex < 0) {
        std::cout << "Invalid vertex" << std::endl;
        return false;
    }

    if(vertex >= num_vertices){
        num_vertices = vertex + 1;
        vertices.push_back({
           vertex,
           lat,
           longi,
           label,
           std::list<edgeNode>()
       });
        std::sort(vertices.begin(), vertices.end(), [](const vertexNode& a, const vertexNode& b) {
            return a.vertex < b.vertex;
        });
        return true;
    }

    // check if vertex already exists
    // if(vertices[vertex].vertex != -1) {
    //     std::cout << "Vertex already exists" << std::endl;
    //     return false;
    // }
    vertices.push_back({
        vertex,
        lat,
        longi,
        label,
        std::list<edgeNode>()
    });
    num_vertices++;
    std::sort(vertices.begin(), vertices.end(), [](const vertexNode& a, const vertexNode& b) {
        return a.vertex < b.vertex;
    });
    return true;
}

//returns true if vertex exists and false otherwise
bool Graph::vertexExists(int vertexID){
    for (const auto& vertex : vertices) {
        if (vertex.vertex == vertexID) {
            return true;
        }
    }
    return false;
}

/** Muda as informações de um vertice no grafo.
 * Este método tem complexidade de tempo O(1).
 */
void Graph::setVertexInfo(int vertex, double lat, double longi) {
    vertices[vertex].lat = lat;
    vertices[vertex].longi = longi;
}

/** Adiciona uma aresta ao grafo.
 * Este método tem complexidade de tempo O(E), onde E é o número de arestas.
 */
void Graph::addEdge(int v1, int v2, double distance) {
    if(v1 < 0 || v1 >= num_vertices || v2 < 0 || v2 >= num_vertices) {
        std::cout << "Invalid vertex" << std::endl;
        return;
    }
    // check if edge already exists
    for(auto e : vertices[v1].adj) {
        if(e.vertex == v2) {
            std::cout << "Edge already exists" << std::endl;
            return;
        }
    }

    vertices[v1].adj.emplace_back(edgeNode{v2, distance});

    if(directed) {
        vertices[v2].adj.emplace_back(edgeNode{v1, distance});
        num_edges++;
    }

    num_edges++;
}

/** Remove uma aresta do grafo.
 * Este método tem complexidade de tempo O(d_v1 + d_v2), onde d_v1 e d_v2 são os graus dos vértices v1 e v2.
 * @param v1
 * @param v2
 */
void Graph::removeEdge(int v1, int v2) {
    if (v1 < 0 || v1 >= num_vertices || v2 < 0 || v2 >= num_vertices) {
        std::cout << "Invalid vertex" << std::endl;
        return;
    }

    // check if edge exists
    bool edge_exists = false;
    for (auto e: vertices[v1].adj) {
        if (e.vertex == v2) {
            edge_exists = true;
            break;
        }
    }
    if (!edge_exists) {
        std::cout << "Edge does not exist" << std::endl;
        return;
    }

    // remove edge
    vertices[v1].adj.remove_if([v2](edgeNode e) { return e.vertex == v2; });
    if (!directed) {
        vertices[v2].adj.remove_if([v1](edgeNode e) { return e.vertex == v1; });
        num_edges--;
    }

    num_edges--;
}

/** Remove todas as arestas adjacentes a um vértice.
 * Este método tem complexidade de tempo O(d_v), onde d_v é o grau do vértice v.
 * @param v
 */
void Graph::removeAdjEdges(int v) {
    // Remove all adjacent edges going from and to v
    for (auto e: vertices[v].adj) {
        vertices[e.vertex].adj.remove_if([v](edgeNode e) { return e.vertex == v; });
        num_edges--;
    }
    vertices[v].adj.clear();
}

/** Imprime o grafo.
 * Este método tem complexidade de tempo O(V + E), onde V é o número de vértices e E é o número de arestas.
 */
void Graph::printGraph()
{
    std::sort(vertices.begin(), vertices.end(), [](const vertexNode& a, const vertexNode& b) {
        return a.vertex < b.vertex;
    });

    for (auto v : vertices) {
        std::cout << "Node " << v.vertex << " (" << v.lat << ", " << v.longi << ") " << "label: " << v.label << std::endl;
        for (auto e : v.adj) {
            std::cout << "  -> Node " << e.vertex << " distance " << e.distance << std::endl;
        }
    }
}

// void Graph::test() {
//     int nedges = 0;
//     for(int i = -0; i < num_vertices; i++) {
//         if(vertices[i].vertex != i) {
//             std::cout << "vertex: " << vertices[i].vertex << " i: " << i << std::endl;
//         }
//         for(auto e : vertices[i].adj) {
//             if(e.vertex < 0 || e.vertex >= num_vertices) {
//                 std::cout << "vertex: " << e.vertex << std::endl;
//             }
//             nedges++;
//         }
//     }
//     if(nedges != num_edges) {
//         std::cout << "nedges: " << nedges << " num_edges: " << num_edges << std::endl;
//     }
//     // std::cout << nedges << std::endl;
// }