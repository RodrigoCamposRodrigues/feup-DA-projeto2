#include "manager.h"

Manager::Manager(const char *nodes_file, const char *edges_file) : 
    nodes_reader(nodes_file),
    edges_reader(edges_file),
    delivery_graph(false) {}

Manager::Manager(const char *f_name) : 
    edges_reader(f_name),
    nodes_reader(f_name),
    delivery_graph(false) {}

void Manager::initialize_all(){
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

void Manager::initialize_selected(bool file_column_csv){
    std::vector<std::string> line;

    if(file_column_csv){
        while(!edges_reader.is_eof() && !edges_reader.is_error()){
            line = edges_reader.read_line();
            bool can_add_edge = false;
            if(!delivery_graph.vertexExists(std::stoi(line[0]))){
                delivery_graph.addVertex(std::stoi(line[0]), 0, 0, line[3]);

                if(!delivery_graph.vertexExists(std::stoi(line[1]))){
                    delivery_graph.addVertex(std::stoi(line[1]), 0, 0, line[4]);
                    can_add_edge = true;
                }
                else can_add_edge = true;
            }
            else if(!delivery_graph.vertexExists(std::stoi(line[1]))){
                delivery_graph.addVertex(std::stoi(line[1]), 0, 0, line[4]);
                can_add_edge = true;
            }
            else can_add_edge = true;

            if(can_add_edge){
                delivery_graph.addEdge(std::stoi(line[0]), std::stoi(line[1]), std::stod(line[2]));
            }
        }
    }
    else{
        while(!edges_reader.is_eof()){
            line = edges_reader.read_line();
            bool can_add_edge = false;

            if(line.size() == 3){
                if(!delivery_graph.vertexExists(std::stoi(line[0]))){
                    delivery_graph.addVertex(std::stoi(line[0]), 0, 0, "");

                    if(!delivery_graph.vertexExists(std::stoi(line[1]))){
                        delivery_graph.addVertex(std::stoi(line[1]), 0, 0, "");
                        can_add_edge = true;
                    }
                    else can_add_edge = true;
                }
                else if(!delivery_graph.vertexExists(std::stoi(line[1]))){
                    delivery_graph.addVertex(std::stoi(line[1]), 0, 0, "");
                    can_add_edge = true;
                }
                else can_add_edge = true;
            }

            if(can_add_edge){
                delivery_graph.addEdge(std::stoi(line[0]), std::stoi(line[1]), std::stod(line[2]));
                std::cout << "Added edge" << line[0] << " " << line[1] << " " << line[2] << std::endl;
            }
        } 
    }
}

double Manager::backtrack_tsp(){
    std::vector<bool> visited(delivery_graph.getNumVertices(), false);
    visited[0] = true;
    double ans = INT_MAX;
    delivery_graph.backtrack_tsp(visited, 0, delivery_graph.getNumVertices(), 1, 0, ans);
    return ans;
}

void Manager::printGraph(){
    delivery_graph.printGraph();
}

