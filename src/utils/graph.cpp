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

/// @brief Retorna a latitude de um vértice.
/// @param vertex Vértice a ser consultado.
/// @return Latitude do vértice.
double Graph::getLat(int vertex) const {
    return vertices[vertex].lat;
}

/// @brief Retorna a longitude de um vértice.
/// @param vertex Vértice a ser consultado.
/// @return Longitude do vértice.
double Graph::getLongi(int vertex) const {
    return vertices[vertex].longi;
}

/// @brief Retorna o label de um vértice.
/// @param vertexID Vértice a ser consultado.
/// @return Label do vértice.
std::string Graph::getLabel(int vertexID) const {
    return vertices[vertexID].label;
}

/// @brief Calcula a distância entre dois vértices.
/// @param v1 Vértice 1.
/// @param v2 Vértice 2.
/// @return Distância entre os vértices.
double Graph::getDistance(int v1, int v2) const {
    for(auto &edge : vertices[v1].adj) {
        if(edge.vertex == v2) {
            return edge.distance;
        }
    }
    return 0;
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

    int index = 0;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].vertex == v1){
            index = i;
            break;
        }
    }

    // check if edge already exists
    for(auto e : vertices[index].adj) {
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

std::vector<std::pair<int, int>> Graph::primMST(std::vector<int>& parent) {

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


    std::vector<std::pair<int, int>> mst;

    //Print the MST
    std::cout << "Minimum Spanning Tree:" << std::endl;
    for (int i = 1; i < vertices.size(); ++i) {
        //fill the mst
        mst.push_back(std::make_pair(parent[i], i));
    }

    return mst;
}

/// @brief Corre do algoritmo de Depth First Search (DFS) para encontrar o caminho mais curto entre dois vértices.
/// @param current Vértice atual.
/// @param parent Vetor de pais.
/// @param visited Vetor de visitados.
/// @param cityStack Pilha de cidades.
/// @param path Vetor de caminho.
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

/// @brief Calcula a distância total de um caminho.
/// @param path Vetor de inteiros, representando o caminho.
/// @return Retorna a distância total do caminho.
double Graph::calculateTotalDistance(const std::vector<int> &path) {
    double totalDistance = 0.0;

    // Calculate the total distance
    for (int i = 0; i < path.size() - 1; ++i) {
        int v1 = path[i];
        int v2 = path[i + 1];

        if(!check_if_nodes_are_connected(v1, v2)){
            totalDistance += haversine(vertices[v1].lat, vertices[v1].longi, vertices[v2].lat, vertices[v2].longi);
            continue;
        }

        for (const edgeNode& edge : vertices[v1].adj) {
            if (edge.vertex == v2) {
                totalDistance += edge.distance;
                break;
            }
        }
    }

    //add final distance to total distance
    int final_city = path.back();
    if(!check_if_nodes_are_connected(final_city, path[0])){
        totalDistance += haversine(vertices[final_city].lat, vertices[final_city].longi, vertices[path[0]].lat, vertices[path[0]].longi);
    }
    else{
        for(const edgeNode& edge : vertices[final_city].adj){
            if(edge.vertex == path[0]){
                totalDistance += edge.distance;
                break;
            }
        }
    }

    return totalDistance;
}


/// @brief Verifica se dois vértices são conectados.
/// @param v1 Vértice 1.
/// @param v2 Vértice 2.
/// @return Retorna true se os vértices são conectados, false caso contrário.
bool Graph::check_if_nodes_are_connected(int v1, int v2){
    int index_v1;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].vertex == v1){
            index_v1 = i;
        }
    }

    for(const edgeNode& edge : vertices[index_v1].adj){
        if(edge.vertex == v2){
            return true;
        }
    }
    return false;
}

/// @brief Conversão de graus para radianos.
/// @param degrees Graus.
/// @return Retorna o valor em radianos.
double Graph::degrees_to_radians(double degrees){
    return degrees * M_PI / 180;
}

/// @brief Calcula a distância entre dois pontos na superfície da Terra.
/// @param lat1 Latitude do ponto 1.
/// @param lon1 Longitude do ponto 1.
/// @param lat2 Latitude do ponto 2.
/// @param lon2 Longitude do ponto 2.
/// @return Retorna a distância entre os dois pontos.
double Graph::haversine(double lat1, double lon1, double lat2, double lon2){

    if(lat1 == 0 && lon1 == 0 && lat2 == 0 && lon2 == 0){
        return 0.0;
    }

    double dLat = degrees_to_radians(lat2 - lat1);
    double dLon = degrees_to_radians(lon2 - lon1);

    lat1 = degrees_to_radians(lat1);
    lat2 = degrees_to_radians(lat2);

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * asin(sqrt(a));

    return EARTH_RADIUS * c;
}

/// @brief Econtra os vértices com grau ímpar.
/// @return Retorna um vetor com os vértices de grau ímpar.
std::vector<int> Graph::findOddDegreeVertices(){

    std::vector<int> oddDegreeVertices;

    // Find vertices in MST with odd degrees
    for (int vertex = 0; vertex < vertices.size(); ++vertex) {
        if (vertices[vertex].adj.size() % 2 != 0) {
            oddDegreeVertices.push_back(vertex);
        }
    }

    return oddDegreeVertices;
}

/// @brief Encontra um caminho euleriano, a partir de um vértice inicial.
/// @param start_vertex Vértice inicial.
/// @param circuit Vetor de inteiros, representando o caminho euleriano.
/// Esta função tem complexidade O(E), sendo E o número de arestas do grafo.
void Graph::findEulerianPath(int start_vertex, std::vector<int> &circuit){
    std::stack<int> stack;
    stack.push(start_vertex);

    while (!stack.empty()) {
        int current_vertex = stack.top();

        if (!vertices[current_vertex].adj.empty()) {
            int next_vertex = vertices[current_vertex].adj.back().vertex;
            vertices[current_vertex].adj.pop_back();
            stack.push(next_vertex);
        }
        else {
            circuit.push_back(current_vertex);
            stack.pop();
        }
    }
}

