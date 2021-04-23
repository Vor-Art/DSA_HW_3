#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

#include <graph.h>



int main()
{

    const std::string path = "/home/vorart/workspace/qt projects/DSA_HW_3/input.txt";
    std::ifstream in(path);
    assert(in.is_open() && "file is not found");

    Graph<std::string,std::string> graph;
    std::string	line;
    while(getline(in, line,'\n'))
    {
        std::stringstream inputstream(line);
        std::string command;
        inputstream >> command;
        if ("ADD_VERTEX" == command){
            std::string vertex;
            inputstream >> vertex;
            graph.addVertex(vertex);
            continue;
        }
        if ("REMOVE_VERTEX" == command){
            std::string vertex;
            inputstream >> vertex;
            graph.removeVertex(vertex);
            continue;
        }
        if ("ADD_EDGE" == command){
            std::string from, to, weight;
            inputstream >> from >> to >> weight;
            graph.addEdge(from, to, weight);
            continue;
        }
        if ("REMOVE_EDGE" == command){
            std::string from, to;
            inputstream >> from >> to;
            graph.removeEdge(graph.findEdge(from, to));
            continue;
        }
        if ("HAS_EDGE" == command){
            std::string from, to;
            inputstream >> from >> to;
            try {
                graph.findEdge(from, to);
            } catch (...) {
                std::cout << "FALSE" << std::endl;
                continue;
            }
            std::cout << "TRUE" << std::endl;
            continue;
        }
        if ("TRANSPOSE" == command){
            graph.transpose();
            continue;
        }
        if ("IS_ACYCLIC" == command){
            auto [weight,path] = graph.isAcylcic();
            if (path.empty())
                continue;

            std::cout << "ACYCLIC" << std::endl;
            std::cout << weight << " ";
            for (const auto& vertex: path)
                std::cout << vertex << " ";
            std::cout << std::endl;
            continue;
        }
    }
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("T");

    auto vetrex = graph.findVertex("A");

    graph.addEdge(vetrex, graph.findVertex("B"), "3");
    graph.addEdge(vetrex, graph.findVertex("C"), "4");
    graph.addEdge(vetrex, graph.findVertex("D"), "5");
    graph.addEdge(graph.findVertex("T"), vetrex, "6");

    for (const auto & a: graph.edgesFrom(vetrex)){
        std::cout << "From: "<< a.second.from().v()<< " To: "<< a.second.to().v() << " Weight: " << a.second.weight() << std::endl;
    }

    for (const auto & a: graph.edgesTo(vetrex)){
        std::cout << "From: "<< a.second.from().v()<< " To: "<< a.second.to().v() << " Weight: " << a.second.weight() << std::endl;
    }
    std::cout << "TRANSPOSE" << std::endl;
    graph.transpose();
    for (const auto & a: graph.edgesFrom(vetrex)){
        std::cout << "From: "<< a.second.from().v()<< " To: "<< a.second.to().v() << " Weight: " << a.second.weight() << std::endl;
    }

    for (const auto & a: graph.edgesTo(vetrex)){
        std::cout << "From: "<< a.second.from().v()<< " To: "<< a.second.to().v() << " Weight: " << a.second.weight() << std::endl;
    }
    return 0;
}
