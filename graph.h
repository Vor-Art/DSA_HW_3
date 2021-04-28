#ifndef GRAPH_H
#define GRAPH_H
#include <stdexcept>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>

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
    using Edge = typename GraphADT::Edge;
    using CollectionFrom = typename GraphADT::CollectionFrom;
    using CollectionTo = typename GraphADT::CollectionTo;

    using Container = std::unordered_map <Vertex, CollectionFrom, typename Vertex::Hash>;
    Container container_from;
    Container container_to;
    Container container_from_transpose;
    Container container_to_transpose;

    using VertexArr = std::vector<Vertex>;
    using Path = std::pair<E_type, VertexArr>;

    //decltype(E_type::operator+()) is required to:
    //      1) show that return value is the sum;
    //      2) oblige compiler statically checks that ‘operator+’ is a member of the E_type.

public:
    Graph() = default;
    virtual ~Graph() = default;
    const Vertex &addVertex(const V_type& value)                                                    override; // O(1)
    const Vertex &removeVertex(const Vertex& vertex)                                                 override; // O(1)
    const Edge   &addEdge(const Vertex& from_vertex, const Vertex& to_vertex, const E_type& weight) override; // O(1)
    const Edge   &removeEdge(const Edge& edge)                                                       override; // O(1)
    const CollectionFrom &edgesFrom(const Vertex& vertex)                                     const override; // O(1)
    const CollectionTo   &edgesTo(const Vertex& vertex)                                       const override; // O(1)
    const Vertex &findVertex(const V_type & value)                                            const override; // O(1)
    const Edge   &findEdge(const V_type& from_value, const V_type& to_value)                  const override; // O(1)
    const Edge   &findEdge(const Vertex& from_vertex, const Vertex& to_vertex)                const;
    bool          hasEdge(const Vertex& from_vertex, const Vertex& to_vertex)                 const override; // O(1)

    void transpose(void)      ; // O(1)
    Path isAcylcic(void) const; // O(n^2) , where n - number of vertex
    Path findMinPath(const Vertex& from, const Vertex& to) const; // O()

    std::string print();
private:
    const Vertex& getVertex (const V_type& value)                           const noexcept(false);
    const Edge& getEdge (const V_type& from_value, const V_type& to_value)  const noexcept(false);
//    const Vertex& assertVertex (const Vertex& vertex)   const noexcept(false);
//    const Edge& assertEdge (const Edge& edge)           const noexcept(false);
};


template<typename V_type, typename E_type>
const typename Graph<V_type, E_type>::Vertex &Graph<V_type, E_type>::addVertex(const V_type &value)
{
    Vertex vertex (value);

    container_from.emplace(vertex,CollectionFrom());//[vertex];
    container_to.emplace(vertex,CollectionFrom());
    container_from_transpose.emplace(vertex,CollectionFrom());
    container_to_transpose.emplace(vertex,CollectionFrom());

    return container_from.find(vertex)->first;
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::Vertex &Graph<V_type,E_type>::removeVertex(const Vertex &vertex)
{
    for (const auto& [base,edge]: container_from.at(vertex))
        container_to.at(base).erase(vertex);

    for (const auto& [base,edge]: container_to.at(vertex))
        container_from.at(base).erase(vertex);

    for (const auto& [base,edge]: container_from_transpose.at(vertex))
        container_to_transpose.at(base).erase(vertex);

    for (const auto& [base,edge]: container_to_transpose.at(vertex))
        container_from_transpose.at(base).erase(vertex);

    container_from.at(vertex).clear();
    container_to.at(vertex).clear();
    container_from_transpose.at(vertex).clear();
    container_to_transpose.at(vertex).clear();


    container_from.erase(vertex);
    container_to.erase(vertex);
    container_from_transpose.erase(vertex);
    container_to_transpose.erase(vertex);

    return vertex;
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::Edge &Graph<V_type,E_type>::addEdge(const Vertex &from_vertex, const Vertex &to_vertex, const E_type &weight)
{
    Edge tmp(from_vertex,to_vertex,weight);
    container_from.at(from_vertex).emplace(to_vertex,tmp);
    container_to.at(to_vertex).emplace(from_vertex,tmp);

    Edge tmp_transpose(to_vertex,from_vertex,weight);
    container_from_transpose.at(to_vertex).emplace(from_vertex,tmp_transpose);
    container_to_transpose.at(from_vertex).emplace(to_vertex,tmp_transpose);

    return container_from.at(from_vertex).at(to_vertex);
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::Edge &Graph<V_type,E_type>::removeEdge(const Edge &edge)
{
    container_from.at(edge.from()).erase(edge.to());
    container_to.at(edge.to()).erase(edge.from());

    container_from_transpose.at(edge.to()).erase(edge.from());
    container_to_transpose.at(edge.from()).erase(edge.to());
    return edge;
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
    return getVertex(value);
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::Edge &Graph<V_type,E_type>::findEdge(const V_type &from_value, const V_type &to_value) const
{
    return getEdge(from_value, to_value);
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::Edge &Graph<V_type,E_type>::findEdge(const Vertex &from_vertex, const Vertex &to_vertex) const
{
    return container_from.at(from_vertex).at(to_vertex);
}

template<typename V_type, typename E_type>
bool Graph<V_type,E_type>::hasEdge(const Vertex &from_vertex, const Vertex &to_vertex) const
{
    return container_from.at(from_vertex).count(to_vertex);
}

template<typename V_type, typename E_type>
void Graph<V_type,E_type>::transpose()
{
    swap(container_from,container_from_transpose);
    swap(container_to,container_to_transpose);
}

template<class value_T, class edge_T>
typename Graph<value_T, edge_T>::Path  Graph<value_T, edge_T>::isAcylcic() const
{
    auto hasCycle =  [](const VertexArr& path)
    {
        for(size_t i=0;i<path.size()-1;i++) // O(n)
            if(path[i] == path.back())
                return true;
        return false;
    };

    // finding a way that contains a cycle
    std::unordered_set<Vertex, typename Vertex::Hash> global_visited;
    bool success = false;
    Path way_with_cycle;

    for(const auto& [vertex,edge] : container_from){
        if(success)break;
//        if(global_visited.size() == container_from.size())break;
        if(global_visited.find(vertex) != global_visited.end())continue;

        std::stack<std::pair<Vertex,Path>> stack;

        stack.push({vertex, {{}, {vertex}}}); // initial stack

        while(!stack.empty()){
            if(success) break;
            auto obj = stack.top(); stack.pop();
            auto [cur_vertex, cur_path] = obj;

            global_visited.insert(cur_vertex);

            for(const auto& [next_vertex, edge]: edgesFrom(cur_vertex)){

                Path nextWay = {cur_path.first + edge.weight(), cur_path.second};
                nextWay.second.push_back(next_vertex);

                if(hasCycle(nextWay.second)) {way_with_cycle = nextWay;success = true; break;} // cycle
                if(global_visited.count(next_vertex)) continue; // already visited

                stack.push({next_vertex, nextWay});
            }
        }
    }
    if(!success) return {{},{}}; // No cycle


    edge_T weight = way_with_cycle.first;
    VertexArr vertexArr = way_with_cycle.second;

    // Finding a cycle in a path with a cycle.
    size_t i=0;
    for(; i<vertexArr.size()-1; i++){
        Vertex next = vertexArr[i+1];
        Vertex cur  = vertexArr[i];
        if(cur == vertexArr.back()) break;
        weight -= findEdge(cur, next). weight();
    }
    return {weight, VertexArr(vertexArr.begin()+i+1, vertexArr.end())};

}

template<class value_T, class edge_T>
typename Graph<value_T, edge_T>::Path Graph<value_T, edge_T>::findMinPath(const Vertex &source, const Vertex &target) const
{
    // Dijkstra
    std::unordered_map <Vertex, Path, typename Vertex::Hash > min_path;
    std::unordered_set <Vertex, typename Vertex::Hash> visited;
    min_path[source] = {{},{}};

    while(min_path.size()< container_from.size()){
        //iteration phase
        bool first = true;
        Edge minEdge;
        for(const auto& [vertex,tmp] : container_from){
            if (visited.find(vertex) != visited.end()) continue; //visited
            if (min_path.find(vertex) == min_path.end()) continue; //inf path
            if (first) {
                minEdge = {source, min_path[vertex].first, vertex};
                first = false;
                continue;
            }
            if (minEdge.weight() >  min_path[vertex].first)
                minEdge = {source, min_path[vertex].first, vertex};
        }
        if (first) continue;
        //marked
        visited.insert(minEdge.to());
        //relaxation phase
        Vertex cur_vertex = minEdge.to();
        for(const auto& [to, edge] : edgesFrom(cur_vertex)){
            if (min_path.find(to) == min_path.end()||
                min_path[to].first > (minEdge.weight() + edge.weight()))
            {
                min_path[to].first = min_path[cur_vertex].first + edge.weight();
                min_path[to].second = min_path[cur_vertex].second;
                min_path[to].second.push_back(cur_vertex);
            }
        }
    }

    if(min_path.find(target) == min_path.end())
        return {{},{}};  //empty
    min_path[target];
}

template<typename V_type, typename E_type>
std::string Graph<V_type,E_type>::print()
{
    std::stringstream ss;
    ss << "container_from:" << std::endl;
    size_t indx = 0;
    for (const auto& [from, list]:container_from)
    {
        ss <<indx<< ") " << from << ": ";
        for (const auto& [to, edge]:list)
            ss <<"[" << to<< ", " << edge.weight() << "]  ";
        ss << std::endl;
        indx++;
    }
    return ss.str();
}





template<typename V_type, typename E_type>
const typename Graph<V_type, E_type>::Vertex &Graph<V_type,E_type>::getVertex(const V_type &value) const noexcept(false)
{
    Vertex false_vertex = Vertex(value);
    auto it = container_from.find(false_vertex);
    if (it == container_from.end())
        throw std::runtime_error("there is no such vertex");
    return it->first; //true_vertex
}

template<typename V_type, typename E_type>
const typename Graph<V_type,E_type>::Edge & Graph<V_type,E_type>::getEdge(const V_type& from_value, const V_type& to_value) const noexcept(false)
{
    Vertex from;
    Vertex to;
    try {
        from = getVertex(from_value);
        to = getVertex(to_value);
    } catch (...) {
        throw std::runtime_error("incorrect vertices");
    }
    auto it = container_from.at(from).find(to);
    if (it == container_from.at(from).end())
        throw std::runtime_error("there is no connection between the vertices");
    return it->second;
}

//template<typename V_type, typename E_type>
//const typename Graph<V_type, E_type>::Vertex &Graph<V_type,E_type>::assertVertex(const Vertex &vertex) const noexcept(false)
//{
//    if (!container_from.count(vertex))
//        throw std::runtime_error("there is no such vertex");
//    return vertex;
//}

//template<typename V_type, typename E_type>
//const typename Graph<V_type,E_type>::Edge & Graph<V_type,E_type>::assertEdge(const Edge &edge) const noexcept(false)
//{
//    try {
//        assertVertex(edge.from());
//        assertVertex(edge.to());
//    } catch (...) {
//        throw std::runtime_error("incorrect vertices");
//    }

//    if (container_from.at(edge.from()).find(edge.to()) == container_from.at(edge.from()).end())
//        throw std::runtime_error("there is no connection between the vertices");
//    return edge;
//}

#endif // GRAPH_H
