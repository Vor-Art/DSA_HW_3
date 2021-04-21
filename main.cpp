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
    EdgeClass<std::string, double> tmp("A","B",3);graph.addEdge(tmp.from(),tmp.to(),tmp.weight());
    tmp = EdgeClass<std::string, double> {"A","C",4};graph.addEdge(tmp.from(),tmp.to(),tmp.weight());
    tmp = EdgeClass<std::string, double> {"A","D",5};graph.addEdge(tmp.from(),tmp.to(),tmp.weight());

    for (const auto & a: graph.edgesFrom(tmp.from())){
        cout << "From: "<< a.second.from().v()<< " To: "<< a.second.to().v() << " Weight: " << a.second.weight() << endl;
    }
    return 0;
}
