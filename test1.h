#ifndef TEST1_H
#define TEST1_H

#include <iostream>
#include <string>

#include "graph.h"

void test1(void)
{
    Graph<std::string,int> graph;

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("T");

    auto vetrex = graph.findVertex("A");

    graph.addEdge(vetrex, graph.findVertex("B"), 3);
    graph.addEdge(vetrex, graph.findVertex("C"), 4);
    graph.addEdge(vetrex, graph.findVertex("D"), 5);
    graph.addEdge(graph.findVertex("T"), vetrex, 6);

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

}
#endif // TEST1_H
