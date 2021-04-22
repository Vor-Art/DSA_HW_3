#ifndef GRAPH_H
#define GRAPH_H
#include <graph_adt.h>

template <typename V_type, typename E_type >
class GraphSupplement{
    using VertexClass = typename GraphADTSupplement< V_type, E_type>::VertexClass;
    using EdgeClass   = typename GraphADTSupplement< V_type, E_type>::EdgeClass;
public:
    using GraphADT_   = GraphADT< V_type, E_type, std::unordered_map, VertexClass, EdgeClass ,typename VertexClass::Hash>;
};

template <typename V_type, typename E_type >
class Graph : public GraphSupplement< V_type, E_type>::GraphADT_
{
    using GraphADT = typename GraphSupplement< V_type, E_type>::GraphADT_;
    using Vertex = typename GraphADT::Vertex;
    using VertexPtr = typename GraphADT::VertexPtr;
    using Edge = typename GraphADT::Edge;
    using EdgePtr = typename GraphADT::EdgePtr;
    using CollectionFrom = typename GraphADT::CollectionFrom;
    using CollectionTo = typename GraphADT::CollectionTo;

    std::unordered_map <Vertex, CollectionFrom, typename Vertex::Hash> container_from;
    std::unordered_map <Vertex, CollectionTo,   typename Vertex::Hash> container_to;

public:
    Graph() = default;
    virtual ~Graph() = default;
    const Vertex &addVertex(const V_type& value)                                                    override; // O(1)
          Vertex removeVertex(const Vertex& vertex)                                                 override; // O(1)
    const Edge   &addEdge(const Vertex& from_vertex, const Vertex& to_vertex, const E_type& weight) override; // O(1)
          Edge   removeEdge(const Edge& edge)                                                       override; // O(1)
    const CollectionFrom &edgesFrom(const Vertex& vertex)                                     const override; // O(1)
    const CollectionTo   &edgesTo(const Vertex& vertex)                                       const override; // O(1)
    const Vertex &findVertex(const V_type & value)                                            const override; // O(1)
    const Edge   &findEdge(const V_type& from_value, const V_type& to_value)                  const override; // O(1)
    const Edge   &hasEdge(const Vertex& from_vertex, const Vertex& to_vertex)                 const override; // O(1)
};


template<typename V_type, typename E_type>
const typename Graph<V_type, E_type>::Vertex &Graph<V_type, E_type>::addVertex(const V_type &value)
{
    Vertex vertex (value);
    container_from[vertex];
    container_to[vertex];
    return container_from.find(vertex)->first;
}

template<typename V_type, typename E_type>
typename Graph<V_type,E_type>::Vertex Graph<V_type,E_type>::removeVertex(const Vertex &vertex)
{
    Vertex tmp (vertex);
    container_from.erase(tmp);
    container_to.erase(tmp);
    return tmp;
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::Edge &Graph<V_type,E_type>::addEdge(const Vertex &from_vertex, const Vertex &to_vertex, const E_type &weight)
{
    Edge tmp(from_vertex,to_vertex,weight);
    container_from[from_vertex][to_vertex] = tmp;
    container_to[to_vertex][from_vertex] = tmp;
    return container_from[from_vertex][to_vertex];
}

template<typename V_type, typename E_type>
typename Graph<V_type,E_type>::Edge Graph<V_type,E_type>::removeEdge(const Edge &edge)
{
    Edge tmp (edge);
    container_from[tmp.from()].erase(tmp.to());
    container_to[tmp.to()].erase(tmp.from());
    return tmp;
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::CollectionFrom &Graph<V_type,E_type>::edgesFrom(const Vertex &vertex) const
{
    return container_from.at(vertex);
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::CollectionTo &Graph<V_type,E_type>::edgesTo(const Vertex &vertex) const
{
    return container_to.at(vertex);
}

template<typename V_type, typename E_type>
const typename Graph<V_type, E_type>::Vertex &Graph<V_type,E_type>::findVertex(const V_type &value) const
{
    return container_from.find(value)->first;
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::Edge &Graph<V_type,E_type>::findEdge(const V_type &from_value, const V_type &to_value) const
{
    return container_from.at(Vertex(from_value)).at(Vertex(to_value));
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::Edge &Graph<V_type,E_type>::hasEdge(const Graph::Vertex &from_vertex, const Graph::Vertex &to_vertex) const
{
    return container_from.at(from_vertex).at(to_vertex);
}

#endif // GRAPH_H
