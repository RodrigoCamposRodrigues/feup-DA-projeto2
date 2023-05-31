#include "manager.h"

/// @brief Constrói um objeto Manager.
/// Responsável por gerenciar e chamar as funções que aplicam os algoritmos aos grafos.
/// @param nodes_file Filepath do arquivo de nós. 
/// @param edges_file Filepath do arquivo de arestas.
Manager::Manager(const char *nodes_file, const char *edges_file) : 
    nodes_reader(nodes_file),
    edges_reader(edges_file),
    delivery_graph(true) {}

/// @brief Constrói um objeto Manager.
/// Responsável por gerenciar e chamar as funções que aplicam os algoritmos aos grafos.
/// @param f_name Filepath do arquivo de nós e arestas.
Manager::Manager(const char *f_name) : 
    edges_reader(f_name),
    nodes_reader(f_name),
    delivery_graph(true) {}

/// @brief Inicializa os grafos.
/// Deve ser chamada caso o arquivo de nós e o arquivo de arestas estejam em arquivos separados.
void Manager::initialize_graphs_with_2_files(){
    std::vector<std::string> line;

    while(!nodes_reader.is_eof() && !nodes_reader.is_error()){
        line = nodes_reader.read_line();
        if(line.size() == 3){
            delivery_graph.addVertex(std::stoi(line[0]), std::stod(line[1]), std::stod(line[2]), "");
        }
    }

    while(!edges_reader.is_eof() && !edges_reader.is_error()){
        line = edges_reader.read_line();
        if(line.size() == 3){
            delivery_graph.addEdge(std::stoi(line[0]), std::stoi(line[1]), std::stod(line[2]));
        }
    }
}

/// @brief Inicializa os grafos.
/// Deve ser chamada caso o arquivo de nós e o arquivo de arestas estejam em um mesmo arquivo.
void Manager::initialize_graphs_with_1_file(){
    std::vector<std::string> line;

    while(!edges_reader.is_eof() && !edges_reader.is_error()){
        line = edges_reader.read_line();
        bool can_add_edge = false;

        if(line.size() == 5) {
            //se a origem não existe, adiciono
            if (!delivery_graph.vertexExists(std::stoi(line[0]))) {
                delivery_graph.addVertex(std::stoi(line[0]), 0, 0, line[3]);
                //se o destino não existe, adiciono
                if (!delivery_graph.vertexExists(std::stoi(line[1]))) {
                    delivery_graph.addVertex(std::stoi(line[1]), 0, 0, line[4]);
                    can_add_edge = true;
                } else can_add_edge = true;
                //Se o destino não existe mas a origem existe, adiciono o destino
            } else if (!delivery_graph.vertexExists(std::stoi(line[1]))) {
                delivery_graph.addVertex(std::stoi(line[1]), 0, 0, line[4]);
                can_add_edge = true;
            } else can_add_edge = true;
            //Se os dois vertices existem, adiciono a aresta
            if (can_add_edge) {
                delivery_graph.addEdge(std::stoi(line[0]), std::stoi(line[1]), std::stod(line[2]));
            }
        }
        else if(line.size() == 3){
            //se a origem nao existe, adiciona a origem
            if(!delivery_graph.vertexExists(std::stoi(line[0]))){
                delivery_graph.addVertex(std::stoi(line[0]), 0, 0, "");
                //se o destino nao existe, adiciona o destino
                if(!delivery_graph.vertexExists(std::stoi(line[1]))){
                    delivery_graph.addVertex(std::stoi(line[1]), 0, 0, "");
                    can_add_edge = true;
                }
                else can_add_edge = true;
            }
            //se o destino nao existe, mas a origem existe, adiciona o destino
            else if(!delivery_graph.vertexExists(std::stoi(line[1]))){
                delivery_graph.addVertex(std::stoi(line[1]), 0, 0, "");
                can_add_edge = true;
            }
            else can_add_edge = true;

            if(can_add_edge){
                delivery_graph.addEdge(std::stoi(line[0]), std::stoi(line[1]), std::stod(line[2]));
            }
        }
    }

}

/// @brief Corre o algoritmo de Backtracking.
/// Imprime também o custo e o tempo de execução do algoritmo.
void Manager::backtrack_tsp(){
    clock_t start = clock();

    double min_cost = std::numeric_limits<double>::max();
    std::vector<int> path = {0}; // Start from vertex 0
    std::vector<bool> visited(delivery_graph.getNumVertices(), false);
    visited[0] = true; // Mark the starting vertex as visited

    // Call the recursive function to find the minimum cost Hamiltonian cycle
    delivery_graph.tsp_backtrack(path, visited, min_cost, 0.0);

    clock_t end = clock();

    std::cout << "Minimum Distance: " << min_cost << std::endl;
    std::cout << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

}

/// @brief Imprime o grafo.
void Manager::printGraph(){
    delivery_graph.printGraph();
}

/// @brief Devolve a aproximação triangular do grafo.
/// Imprime também o custo e o tempo de execução do algoritmo.
void Manager::triangularApproximation() {
    clock_t start = clock();

    double ans = delivery_graph.triangularApproximation();

    clock_t end = clock();

    std::cout << "Minimum Distance: " << ans << std::endl;
    std::cout << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

/// @brief Encontra o caminho hamiltoniano de custo mínimo.
/// Este algoritmo tem complexidade 0(V^2) em que V é o número de vértices do grafo.
/// Imprime também o custo e o tempo de execução do algoritmo.
void Manager::christofides(){

    clock_t start = clock();

    std::vector<int> parent(delivery_graph.getNumVertices(), -1);
    std::vector<std::pair<int, int>> mst = delivery_graph.primMST(parent);

    //create subgraph with mst
    Graph mstGraph(true);
    buildMstGraph(mstGraph, mst);

    std::vector<std::pair<int, int>> mpm = findOddDegreeVerticesAndConnect(mstGraph);


    // //print Odd Degree Vertices
    // std::cout << "Odd Degree Vertices: ";
    // for(int i = 0; i < mpm.size(); i++){
    //     std::cout << mpm[i].first << " " << mpm[i].second << " ";
    // }
    // std::cout << std::endl;

    addMpmEdgesToMst(mpm, mstGraph);

    std::vector<int> circuit;

    mstGraph.findEulerianPath(0, circuit);

    // std::cout << "Eulerian Circuit: ";
    // for(int i = 0; i < circuit.size(); i++){
    //     std::cout << circuit[i] << " ";
    // }
    // std::cout << std::endl;

    std::vector<int> hamiltonian_path;

    getHamiltonianPath(circuit, hamiltonian_path);

    std::cout << "Hamiltonian Path: ";
    for(int i = 0; i < hamiltonian_path.size(); i++){
        std::cout << hamiltonian_path[i] << " ";
    }
    std::cout << std::endl;

    double result = delivery_graph.calculateTotalDistance(hamiltonian_path);

    clock_t end = clock();

    std::cout << "Minimum Distance: " << result << std::endl;
    std::cout << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

/// @brief Constrói um grafo MST, a partir de um vetor de arestas de uma Minimum Spanning Tree.
/// @param mstGraph Grafo MST a ser construído.
/// @param mst Vetor de arestas de uma Minimum Spanning Tree.
void Manager::buildMstGraph(Graph &mstGraph, std::vector<std::pair<int, int>> mst){
    for(int i = 0; i < mst.size(); i++){
        int v1 = mst[i].first;
        int v2 = mst[i].second;
        
        if(v1 == -1 || v2 == -1) continue;

        if(!mstGraph.vertexExists(v1)){
            mstGraph.addVertex(v1, delivery_graph.getLat(v1), delivery_graph.getLongi(v1), delivery_graph.getLabel(v1));

            if(!mstGraph.vertexExists(v2)){
                mstGraph.addVertex(v2, delivery_graph.getLat(v2), delivery_graph.getLongi(v2), delivery_graph.getLabel(v2));
                if(!mstGraph.check_if_nodes_are_connected(v1, v2)){
                    double distance = mstGraph.haversine(delivery_graph.getLat(v1), delivery_graph.getLongi(v1), delivery_graph.getLat(v2), delivery_graph.getLongi(v2));
                    //if the graph does not have lat and longi, just get the distance in the original graph
                    if(distance == 0.0) {
                        mstGraph.addEdge(v1, v2, delivery_graph.getDistance(v1, v2));
                        continue;
                    }
                    mstGraph.addEdge(v1, v2, distance);
                }
                else{
                    mstGraph.addEdge(v1, v2, delivery_graph.getDistance(v1, v2));
                }
            }
            else{
                if(!mstGraph.check_if_nodes_are_connected(v1, v2)){
                    double distance = mstGraph.haversine(delivery_graph.getLat(v1), delivery_graph.getLongi(v1), delivery_graph.getLat(v2), delivery_graph.getLongi(v2));
                    //if the graph does not have lat and longi, just get the distance in the original graph
                    if(distance == 0.0) {
                        mstGraph.addEdge(v1, v2, delivery_graph.getDistance(v1, v2));
                        continue;
                    }
                    mstGraph.addEdge(v1, v2, distance);
                }
                else{
                    mstGraph.addEdge(v1, v2, delivery_graph.getDistance(v1, v2));
                }
            }
        }
        else if(!mstGraph.vertexExists(v2)){
                mstGraph.addVertex(v2, delivery_graph.getLat(v2), delivery_graph.getLongi(v2), delivery_graph.getLabel(v2));            
                if(!mstGraph.check_if_nodes_are_connected(v1, v2)){
                    double distance = mstGraph.haversine(delivery_graph.getLat(v1), delivery_graph.getLongi(v1), delivery_graph.getLat(v2), delivery_graph.getLongi(v2));
                    //if the graph does not have lat and longi, just get the distance in the original graph
                    if(distance == 0.0) {
                        mstGraph.addEdge(v1, v2, delivery_graph.getDistance(v1, v2));
                        continue;
                    }
                    mstGraph.addEdge(v1, v2, distance);
                }
            else{
                mstGraph.addEdge(v1, v2, delivery_graph.getDistance(v1, v2));
            }
        }
        else{
            if(!mstGraph.check_if_nodes_are_connected(v1, v2)){
                double distance = mstGraph.haversine(delivery_graph.getLat(v1), delivery_graph.getLongi(v1), delivery_graph.getLat(v2), delivery_graph.getLongi(v2));
                    //if the graph does not have lat and longi, just get the distance in the original graph
                    if(distance == 0.0) {
                        mstGraph.addEdge(v1, v2, delivery_graph.getDistance(v1, v2));
                        continue;
                    }
                    mstGraph.addEdge(v1, v2, distance);
            }
            else{
                mstGraph.addEdge(v1, v2, delivery_graph.getDistance(v1, v2));
            }
        }
    }
}

/// @brief Encontra os vértices de grau ímpar de uma MST e conecta-os, formando uma MPM (Minimum Perfect Matching).
/// Esta função tem complexidade de tempo O(n^2), onde n é o número de vértices de grau ímpar.
/// @param mstGraph Grafo MST.
/// @return Vetor de pares de inteiros, representando as arestas da MPM.
std::vector<std::pair<int, int>> Manager::findOddDegreeVerticesAndConnect(Graph &mstGraph){

    std::vector<int> oddDegreeVertices = mstGraph.findOddDegreeVertices();

    //build the mpm
    std::vector<std::pair<int, int>> mpm;

    //visited
    std::vector<bool> visited(oddDegreeVertices.size(), false);
    
    for(int i = 0; i < oddDegreeVertices.size(); i++){
        double min_distance = std::numeric_limits<double>::max();

        int nearest_neighbor = -1;

        std::pair<int, int> edge; //stores the index of the vertices in oddDegreeVertices

        if(!visited[i]){
            for(int j = 0; j < oddDegreeVertices.size(); j++){
                if(i != j && !visited[j]){
                    double distance = delivery_graph.getDistance(oddDegreeVertices[i], oddDegreeVertices[j]);
                    if(distance < min_distance){
                        min_distance = distance;
                        nearest_neighbor = j;
                        edge = std::make_pair(i, nearest_neighbor);
                    }
                }
            }

            if(mstGraph.getDistance(oddDegreeVertices[edge.first], oddDegreeVertices[edge.second]) == 0){
                mpm.push_back(std::make_pair(oddDegreeVertices[edge.first], oddDegreeVertices[edge.second]));
                visited[edge.first] = true;
                visited[edge.second] = true;
            }
            
        }
    }

    return mpm;
}

/// @brief Adiciona as arestas de uma MPM para um grafo MST já existente.
/// Esta função tem complexidade de tempo O(n), onde n é o número de arestas da MPM.
/// @param mpm Vetor de pares de inteiros que representam as arestas da MPM.
/// @param mstGraph Grafo MST.
void Manager::addMpmEdgesToMst(std::vector<std::pair<int, int>> mpm, Graph &mstGraph){

    //add mpm edges to mst
    for(int i = 0; i < mpm.size(); i++){
        double distance = mstGraph.haversine(delivery_graph.getLat(mpm[i].first), delivery_graph.getLongi(mpm[i].first), delivery_graph.getLat(mpm[i].second), delivery_graph.getLongi(mpm[i].second));

        if(distance == 0.0){
            mstGraph.addEdge(mpm[i].first, mpm[i].second, delivery_graph.getDistance(mpm[i].first, mpm[i].second));
        }
        else{
            mstGraph.addEdge(mpm[i].first, mpm[i].second, distance);
        }
    }
}

/// @brief Gera um caminho hamiltoniano a partir de um caminho euleriano.
/// Esta função tem complexidade de tempo O(n), onde n é o número de vértices caminho euleriano.
/// @param eulerian_path Vetor de inteiros que representa o caminho euleriano.
/// @param hamiltonian_path Vetor de inteiros que representa o caminho hamiltoniano.
void Manager::getHamiltonianPath(std::vector<int> eulerian_path, std::vector<int> &hamiltonian_path){
    
     for (int vertex : eulerian_path) {
        // Check if the vertex is already in the hamiltonian_path
        auto it = std::find(hamiltonian_path.begin(), hamiltonian_path.end(), vertex);

        if (it == hamiltonian_path.end()) {
            // Add the vertex to the hamiltonian_path if it's not already present
            hamiltonian_path.push_back(vertex);
        }
    }

    // Complete the Hamiltonian cycle by adding the first vertex at the end
    hamiltonian_path.push_back(hamiltonian_path.front());
}
