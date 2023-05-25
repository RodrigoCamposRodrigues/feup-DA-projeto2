#include "manager.h"

Manager::Manager(const char *nodes_file, const char *edges_file) : 
    nodes_reader(nodes_file),
    edges_reader(edges_file),
    delivery_graph(true) {}

Manager::Manager(const char *f_name) : 
    edges_reader(f_name),
    nodes_reader(f_name),
    delivery_graph(true) {}

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

    delivery_graph.connect_all_nodes();   
}

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

void Manager::printGraph(){
    delivery_graph.printGraph();
}

void Manager::triangularApproximation() {
    clock_t start = clock();

    double ans = delivery_graph.triangularApproximation();

    clock_t end = clock();

    std::cout << "Minimum Distance: " << ans << std::endl;
    std::cout << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
}





