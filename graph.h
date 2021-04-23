#ifndef GRAPH_H
#define GRAPH_H
#include <stdexcept>
#include <graph_adt.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>

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
    using Edge = typename GraphADT::Edge;
    using CollectionFrom = typename GraphADT::CollectionFrom;
    using CollectionTo = typename GraphADT::CollectionTo;

    using Container = std::unordered_map <Vertex, CollectionFrom, typename Vertex::Hash>;
    Container container_from;
    Container container_to;
    Container container_from_transpose;
    Container container_to_transpose;

    using VertexArr = std::vector<Vertex>;
    using Cycle = std::pair<E_type, VertexArr>;

    //decltype(E_type::operator+()) is required to:
    //      1) show that return value is the sum;
    //      2) oblige compiler statically checks that ‘operator+’ is a member of the E_type.

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

    void transpose(void)      ; // O(1)
    Cycle isAcylcic(void) const; // O(n^2) , where n - number of vertex
private:
    const Vertex& assertVertex (const Vertex& vertex)   const noexcept(false);
    const Edge& assertEdge (const Edge& edge)           const noexcept(false);
};


template<typename V_type, typename E_type>
const typename Graph<V_type, E_type>::Vertex &Graph<V_type, E_type>::addVertex(const V_type &value)
{
    Vertex vertex (value);
    container_from[vertex];
    container_to[vertex];
    container_from_transpose[vertex];
    container_to_transpose[vertex];
    return container_from.find(vertex)->first;
}

template<typename V_type, typename E_type>
typename Graph<V_type,E_type>::Vertex Graph<V_type,E_type>::removeVertex(const Vertex &vertex)
{
    assertVertex(vertex);
    Vertex tmp (vertex);
    container_from.erase(tmp);
    container_to.erase(tmp);
    container_from_transpose.erase(tmp);
    container_to_transpose.erase(tmp);
    return tmp;
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::Edge &Graph<V_type,E_type>::addEdge(const Vertex &from_vertex, const Vertex &to_vertex, const E_type &weight)
{
    assertVertex(from_vertex);
    assertVertex(to_vertex);
    Edge tmp(from_vertex,to_vertex,weight);
    container_from[from_vertex][to_vertex] = tmp;
    container_to[to_vertex][from_vertex] = tmp;

    Edge tmp_transpose(to_vertex,from_vertex,weight);
    container_from_transpose[to_vertex][from_vertex] = tmp_transpose;
    container_to_transpose[from_vertex][to_vertex] = tmp_transpose;

    return container_from[from_vertex][to_vertex];
}

template<typename V_type, typename E_type>
typename Graph<V_type,E_type>::Edge Graph<V_type,E_type>::removeEdge(const Edge &edge)
{
    assertEdge(edge);
    Edge tmp (edge);
    container_from[tmp.from()].erase(tmp.to());
    container_to[tmp.to()].erase(tmp.from());

    container_from_transpose[tmp.to()].erase(tmp.from());
    container_to_transpose[tmp.from()].erase(tmp.to());
    return tmp;
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::CollectionFrom &Graph<V_type,E_type>::edgesFrom(const Vertex &vertex) const
{
    assertVertex(vertex);
    return container_from.at(vertex);
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::CollectionTo &Graph<V_type,E_type>::edgesTo(const Vertex &vertex) const
{
    assertVertex(vertex);
    return container_to.at(vertex);
}

template<typename V_type, typename E_type>
const typename Graph<V_type, E_type>::Vertex &Graph<V_type,E_type>::findVertex(const V_type &value) const
{
    return assertVertex(container_from.find(value)->first);
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::Edge &Graph<V_type,E_type>::findEdge(const V_type &from_value, const V_type &to_value) const
{
    assertVertex(from_value);
    assertVertex(to_value);
    return assertEdge(container_from.at(from_value).at(to_value));
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::Edge &Graph<V_type,E_type>::hasEdge(const Graph::Vertex &from_vertex, const Graph::Vertex &to_vertex) const
{
    assertVertex(from_vertex);
    assertVertex(to_vertex);
    return assertEdge(container_from.at(from_vertex).at(to_vertex));
}

template<typename V_type, typename E_type>
void Graph<V_type,E_type>::transpose()
{
    swap(container_from,container_from_transpose);
    swap(container_to,container_to_transpose);
}

template<class value_T, class edge_T>
typename Graph<value_T, edge_T>::Cycle  Graph<value_T, edge_T>::isAcylcic() const
{
    // finding a way that contains a cycle
    std::unordered_set<Vertex, typename Vertex::Hash> global_visited;
    bool success = false;
    Cycle way_with_cycle;

    for(const auto& [vertex,edge] : container_from){
        if(success)break;
        if(global_visited.size() == container_from.size())break;
        if(global_visited.find(vertex) != global_visited.end())continue;

        std::unordered_set<Vertex, typename Vertex::Hash> local_marked;


        global_visited.insert(vertex);
        local_marked.insert(vertex);

        std::stack<std::pair<Vertex,Cycle>> stack;
        stack.push({vertex, {{}, {vertex}}});

        while(!stack.empty()){
            if(success) break;
            auto obj = stack.top(); stack.pop();
            Vertex cur_vertex = obj.first;
            Cycle cur_path = obj.second;

            for(const auto& [next_vertex, edge]: edgesFrom(cur_vertex)){

                Cycle nextWay = {cur_path.first + edge.weight(), cur_path.second};

                if(local_marked.find(next_vertex) != local_marked.end()) {way_with_cycle = nextWay;success = true; break;} // cycle
                if(global_visited.find(next_vertex) != global_visited.end()) continue; // already visited

                nextWay.second.push_back(next_vertex);
                stack.push({next_vertex, nextWay});

                global_visited.insert(next_vertex);
                local_marked.insert(next_vertex);
            }
        }
    }

    if(!success) return {{},{}}; // No cycle
    return way_with_cycle;
}

template<typename V_type, typename E_type>
const typename Graph<V_type, E_type>::Vertex &Graph<V_type,E_type>::assertVertex(const Vertex &vertex) const noexcept(false)
{
    if (container_from.find(vertex) == container_from.end())
        throw std::runtime_error("there is no such vertex");
    return vertex;
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::Edge & Graph<V_type,E_type>::assertEdge(const Edge &edge) const noexcept(false)
{
    try {
        assertVertex(edge.from());
        assertVertex(edge.to());
    } catch (...) {
        throw std::runtime_error("incorrect vertices");
    }
    if (container_from.at(edge.from()).find(edge.to()) == container_from.at(edge.from()).end())
        throw std::runtime_error("there is no connection between the vertices");
    return edge;
}

#endif // GRAPH_H
