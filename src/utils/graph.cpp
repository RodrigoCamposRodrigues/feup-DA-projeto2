#include "graph.h"


/** Construtor da classe Graph.
 * Este método tem complexidade de tempo O(1).
 * @param dir true se o grafo for direcionado, false caso contrário.
*/
Graph::Graph(bool dir) : num_edges(0), directed(dir) {
    vertices = std::vector<vertexNode>();
}      

// getters
/** Retorna o número de vértices do grafo.
 * Este método tem complexidade de tempo O(1).
 * @return número de vértices do grafo.
*/
int Graph::getNumVertices() const {
    return vertices.size();
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
        std::vector<edgeNode>()
    });
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

    auto it = max_element(vertices.begin(), vertices.end(), [](const vertexNode& a, const vertexNode& b) {
        return a.vertex < b.vertex;
    });
    int numVertices = it->vertex + 1;

    if(v1 < 0 || v1 >= numVertices|| v2 < 0 || v2 >= numVertices) {
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

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].vertex == v1){
            vertices[i].adj.emplace_back(edgeNode{v2, distance});
        }
    }

    if(directed) {
        for(int i = 0; i < vertices.size(); i++){
            if(vertices[i].vertex == v2){
                vertices[i].adj.emplace_back(edgeNode{v1, distance});
            }
        }
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

    auto it = max_element(vertices.begin(), vertices.end(), [](const vertexNode& a, const vertexNode& b) {
        return a.vertex < b.vertex;
    });
    int numVertices = it->vertex + 1;

    if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) {
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
    //vertices[v1].adj.remove_if([v2](edgeNode e) { return e.vertex == v2; });
    if (!directed) {
        //vertices[v2].adj.remove_if([v1](edgeNode e) { return e.vertex == v1; });
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
        //vertices[e.vertex].adj.remove_if([v](edgeNode e) { return e.vertex == v; });
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

int Graph::minKey(std::vector<double> &key, std::vector<bool> &inMST){
    double min = std::numeric_limits<double>::max();
    int minIndex = -1;
    int numVertices = key.size();

    for (int v = 0; v < numVertices; ++v) {
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

void Graph::primMST(std::vector<int>& parent) {

    std::vector<double> key(vertices.size(), std::numeric_limits<double>::max());
    std::vector<bool> inMST(vertices.size(), false);

    int startVertex = 0;  // Starting vertex for MST

    key[startVertex] = 0.0;  // Start with the first vertex

    for (int count = 0; count < vertices.size() - 1; ++count) {
        int u = minKey(key, inMST);
        inMST[u] = true;

        // Update key and parent index of adjacent vertices
        for (const edgeNode& edge : vertices[u].adj) {
            int v = edge.vertex;
            double weight = edge.distance;

            if (!inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    // Print the MST
    std::cout << "Minimum Spanning Tree:" << std::endl;
    for (int i = 1; i < vertices.size(); ++i) {
        std::cout << parent[i] << " - " << i << std::endl;
    }
}

void Graph::dfs(int current, const std::vector<int> &parent, std::vector<bool> &visited, std::stack<int> &cityStack, std::vector<int> &path) {
    visited[current] = true;
    cityStack.push(current);

    while (!cityStack.empty()) {
        int city = cityStack.top();
        cityStack.pop();

        // Process the city or print its order
        path.push_back(city);

        for (int neighbor = 0; neighbor < parent.size(); ++neighbor) {
            if (parent[neighbor] == city && !visited[neighbor]) {
                visited[neighbor] = true;
                cityStack.push(neighbor);
            }
        }
    }
}

double Graph::calculateTotalDistance(const std::vector<int> &path) {
    double totalDistance = 0.0;

    // Calculate the total distance
    for (int i = 0; i < path.size() - 1; ++i) {
        int v1 = path[i];
        int v2 = path[i + 1];

        for (const edgeNode& edge : vertices[v1].adj) {
            if (edge.vertex == v2) {
                totalDistance += edge.distance;
                break;
            }
        }
    }

    //add final distance to total distance
    int final_city = path.back();
    for(const edgeNode& edge : vertices[final_city].adj){
        if(edge.vertex == path[0]){
            totalDistance += edge.distance;
            break;
        }
    }

    return totalDistance;
}

void Graph::connect_all_nodes(){

    for(int i = 0; i < vertices.size(); i++){
        for(int j = 0; j < vertices.size(); j++){
            if(check_if_nodes_are_connected(i, j)){
                continue;
            }
            else if(i == j){
                continue;
            }
            else{
                double distance = haversine(vertices[i].lat, vertices[i].longi, vertices[j].lat, vertices[j].longi);
                addEdge(i, j, distance);
            }
        }
    }

}

bool Graph::check_if_nodes_are_connected(int v1, int v2){
    for(const edgeNode& edge : vertices[v1].adj){
        if(edge.vertex == v2){
            return true;
        }
    }
    return false;
}


double Graph::degrees_to_radians(double degrees){
    return degrees * M_PI / 180;
}

double Graph::haversine(double lat1, double lon1, double lat2, double lon2){
    double dLat = degrees_to_radians(lat2 - lat1);
    double dLon = degrees_to_radians(lon2 - lon1);

    lat1 = degrees_to_radians(lat1);
    lat2 = degrees_to_radians(lat2);

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * asin(sqrt(a));

    return EARTH_RADIUS * c;
}

