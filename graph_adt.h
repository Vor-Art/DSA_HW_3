#ifndef GRAPH_ADT_H
#define GRAPH_ADT_H
#include <vector>
#include <unordered_map>

template <typename Vertex, typename E>
struct Edge
{
    Vertex from; Vertex to; E weight;
};

template <typename V>
struct Vertex
{
    V data;
};

template <typename V_type, typename E_type >
class Graph_ADT
{
    using Vertex = Vertex <V_type>;
    using Edge = Edge <Vertex,E_type>;
    using CollectionFrom = std::unordered_map <Vertex, Edge>;
    using CollectionTo = std::unordered_map <Vertex, Edge>;

    std::unordered_map<Vertex,CollectionFrom> container_from;
    std::unordered_map<Vertex,CollectionTo> container_to;

public:
    const CollectionFrom    &addVertex(const V_type& value)                           = 0; //add a vertex with value value to the graph and return reference to the created vertex object;
    Vertex                  &removeVertex(const Vertex& vertex)                       = 0; //remove a vertex, provided a reference to vertex object;
    const Edge  &addEdge(const Vertex& from_vertex, const Vertex& to_vertex, const E_type& weight_value) = 0; //add a edge between from and to vertices with weight, return reference to the created edge object;
    Edge        &removeEdge(const Edge& edge)                                         = 0; //remove an edge, given a reference to an edge object;
    const CollectionFrom    &edgesFrom(const Vertex& vertex)                    const = 0; //return a collection or edge objects that are going from vertex v;
    const CollectionTo      &edgesTo(const Vertex& vertex)                      const = 0; //return a collection or edge objects that are going into vertex v;
    const CollectionFrom    &findVertex(const V_type & value)                   const = 0; //find any vertex with the specified value;
    const Edge  &findEdge(const E_type& from_value, const E_type& to_value)     const = 0; //find any edge with specified values in the source and target vertices;
    const Edge  &findEdge(const E_type& value)                                  const = 0; //find edge with specified values;
    const Edge  &hasEdge(const Vertex& from_vertex, const Vertex& to_vertex)    const = 0; //determine whether there exists a directed edge from v to u;

};

#endif // GRAPH_ADT_H
