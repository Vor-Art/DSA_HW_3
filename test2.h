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
}


#endif // TEST2_H
