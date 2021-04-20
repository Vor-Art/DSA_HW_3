#ifndef GRAPH_H
#define GRAPH_H
#include <graph_adt.h>

template <typename V, typename E>
class Graph : public Graph_ADT<V,E>
{
    using Vertex = Vertex<V>;
    using CollectionFrom = std::unordered_map<Vertex,E>;
    using CollectionTo = std::unordered_map<Vertex,E>;

    std::unordered_map<Vertex,std::unordered_map<Vertex,E>> container_from;
    std::unordered_map<Vertex,std::unordered_map<Vertex,E>> container_to;

public:
    const CollectionFrom  &addVertex(const Vertex& v)          = 0;                            //add a vertex with value value to the graph and return reference to the created vertex object;
    Vertex                 &removeVertex(const Vertex& v)       = 0;                            //remove a vertex, provided a reference to vertex object;
    const Edge<Vertex,E>   &addEdge(const Vertex& from, const Vertex& to, const E& weight) = 0; //add a edge between from and to vertices with weight, return reference to the created edge object;
    Edge<Vertex,E>         &removeEdge(const Edge<Vertex,E>& e) = 0;                            //remove an edge, given a reference to an edge object;
    const CollectionFrom  &edgesFrom(const Vertex& v)    const = 0;                            //return a collection or edge objects that are going from vertex v;
    const CollectionTo    &edgesTo(const Vertex& v)      const = 0;                            //return a collection or edge objects that are going into vertex v;
    const CollectionFrom  &findVertex(const Vertex& v)   const = 0;                            //find any vertex with the specified value;
    const Edge<Vertex,E>   &findEdge(const E& from_value, const E& to_value)         const = 0; //find any edge with specified values in the source and target vertices;
    const Edge<Vertex,E>   &findEdge(const E& value)      const = 0;                            //find edge with specified values;
    const Edge<Vertex,E>   &hasEdge(const Vertex& from, const Vertex& to)            const = 0; //determine whether there exists a directed edge from v to u;

};

#endif // GRAPH_H
