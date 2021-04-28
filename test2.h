#ifndef TEST2_H
#define TEST2_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

#include "graph.h"

void test2(void)
{
//    const std::string path = "/home/vorart/workspace/qt projects/DSA_HW_3/input.txt";
//    std::ifstream in(path);
//    assert(in.is_open() && "file is not found");
//    std::stringstream stream ;

    Graph<std::string, int> graph;
    std::string	line;
//    std::cout << "start"  << std::endl;
    while(getline(std::cin, line,'\n'))
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
            auto vertex_class = graph.findVertex(vertex);
            graph.removeVertex(vertex_class);
            continue;
        }
        if ("ADD_EDGE" == command){
            std::string from, to, weight;
            inputstream >> from >> to >> weight;
            auto vertex_from = graph.findVertex(from);
            auto vertex_to = graph.findVertex(to);
            graph.addEdge(vertex_from, vertex_to, std::stoi(weight));
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
            auto vertex_from = graph.findVertex(from);
            auto vertex_to = graph.findVertex(to);
            if (graph.hasEdge(vertex_from, vertex_to))
                std::cout  << "TRUE" << std::endl;
            else
                std::cout  << "FALSE" << std::endl;
            continue;
        }
        if ("TRANSPOSE" == command){
            graph.transpose();
            continue;
        }
        if ("IS_ACYCLIC" == command){
            auto [weight,path] = graph.isAcylcic();
            if (path.empty()){
                std::cout  << "ACYCLIC" << std::endl;
                continue;
            }
            std::cout  << weight << " ";
            for (const auto& vertex: path)
                std::cout  << vertex << " ";
            std::cout  << std::endl;
                    continue;
        }
        assert(false && "command is not found");
    }
//    in.close();
//    std::ofstream fout("output.txt");
//    fout << stream.str();
//    fout.close();

}


#endif // TEST2_H
