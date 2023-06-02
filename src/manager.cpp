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

/// @brief Corre o algoritmo nearest neighbor para diferentes starting vertex.
/// Este algoritmo tem complexidade 0(V²) em que V é o número de vértices do grafo.
/// Imprime também o custo e o tempo de execução do algoritmo.
void Manager::nearest_neighbor(){

    clock_t start = clock();

    std::unordered_map<int, vertexNode> vertices_original_graph = delivery_graph.getVertices();
    double min_cost = std::numeric_limits<double>::max();
    std::vector<int> min_path;
    for(int i = 0; i < vertices_original_graph.size(); i++){
        std::vector<int> path = delivery_graph.nearestNeighbour(i);
        double result = delivery_graph.calculateTotalDistance(path);
        if(result < min_cost){
            min_cost = result;
            min_path = path;
        }
    }
    double result = delivery_graph.calculateTotalDistance(min_path);

    clock_t end = clock();

    std::cout << "Minimum Distance: " << result << std::endl;
    std::cout << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

