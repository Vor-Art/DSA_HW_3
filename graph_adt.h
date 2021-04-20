#ifndef GRAPH_ADT_H
#define GRAPH_ADT_H
#include <vector>
#include <memory>
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
protected:
    using Vertex = Vertex <V_type>;
    using VertexPtr = std::shared_ptr<Vertex>; // I wanted to introduce them so that when you delete an element, you can return the object by reference without copying it. But I collapsed from an oak tree to implement it.
    using Edge = Edge <Vertex,E_type>;
    using EdgePtr = std::shared_ptr<Edge>; // simular
    using CollectionFrom = std::unordered_map <Vertex, Edge>;
    using CollectionTo = std::unordered_map <Vertex, Edge>;

    std::unordered_map<Vertex,CollectionFrom> container_from;
    std::unordered_map<Vertex,CollectionTo> container_to;

public:
    virtual const CollectionFrom    &addVertex(const V_type& value)                           = 0; //add a vertex with value value to the graph and return reference to the created vertex object;
    virtual Vertex  /*VertexPtr*/   &removeVertex(const Vertex& vertex)                       = 0; //remove a vertex, provided a reference to vertex object;
    virtual const Edge  &addEdge(const Vertex& from_vertex, const Vertex& to_vertex, const E_type& weight) = 0; //add a edge between from and to vertices with weight, return reference to the created edge object;
    virtual Edge     /*EdgePtr*/    &removeEdge(const Edge& edge)                             = 0; //remove an edge, given a reference to an edge object;
    virtual const CollectionFrom    &edgesFrom(const Vertex& vertex)                    const = 0; //return a collection or edge objects that are going from vertex v;
    virtual const CollectionTo      &edgesTo(const Vertex& vertex)                      const = 0; //return a collection or edge objects that are going into vertex v;
    virtual const CollectionFrom    &findVertex(const V_type & value)                   const = 0; //find any vertex with the specified value;
    virtual const Edge  &findEdge(const V_type& from_value, const V_type& to_value)     const = 0; //find any edge with specified values in the source and target vertices;
    virtual const Edge  &hasEdge(const Vertex& from_vertex, const Vertex& to_vertex)    const = 0; //determine whether there exists a directed edge from v to u;

};

#endif // GRAPH_ADT_H
