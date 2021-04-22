#include <iostream>
#include <string>

#include <graph.h>

using namespace std;


int main()
{
    Graph<std::string, double> graph;
//    ADD_VERTEX A
//    ADD_VERTEX B
//    ADD_EDGE A B 3
//    HAS_EDGE A B
//    HAS_EDGE B A
//    REMOVE_EDGE A B
//    HAS_EDGE A B


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
        cout << "From: "<< a.second.from().v()<< " To: "<< a.second.to().v() << " Weight: " << a.second.weight() << endl;
    }

    for (const auto & a: graph.edgesTo(vetrex)){
        cout << "From: "<< a.second.from().v()<< " To: "<< a.second.to().v() << " Weight: " << a.second.weight() << endl;
    }
    return 0;
}
