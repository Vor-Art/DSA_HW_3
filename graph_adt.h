#ifndef GRAPH_ADT_H
#define GRAPH_ADT_H
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include <sstream>

template <typename VertexClass, typename E_type>
class EdgeClass
{
    VertexClass _from;
    VertexClass _to;
    E_type _weight;
public:
    EdgeClass() = default;
    ~EdgeClass() = default;
    explicit EdgeClass(const VertexClass& from, const VertexClass& to, const E_type& weight)
        :_from(from),_to(to),_weight(weight)
    {}
    explicit operator E_type()const{return _weight;}
    bool operator ==(const EdgeClass& E) const  {return E._from==_from && E._to == _to;}
    EdgeClass reverse() const {return EdgeClass(_to,_from,_weight);}
    const VertexClass& to()     const {return _to;}
    const VertexClass& from()   const {return _from;}
    const E_type&   weight() const {return _weight;}
    struct Hash {
          std::size_t operator()(const EdgeClass& E) const {
              return typename VertexClass::Hash{}(E._from) + typename VertexClass::Hash{}(E._to);
          }
      };
};

template <typename V_type>
class VertexClass
{
    V_type _v;
public:
    VertexClass() = default;
    ~VertexClass() = default;
    VertexClass(const V_type& V):_v(V){}
    explicit operator V_type()const{return _v;}
    const V_type &v() const {return _v ;}
    bool operator ==(const VertexClass& V) const {return _v == V._v;}
    struct Hash {
        std::size_t operator()(const VertexClass& V) const {
            return std::hash<V_type>{}(V_type(V));
        }
    };

};

//template <typename V_type, typename E_type >
template<typename V_type, typename E_type/*, class Collection*/>
class GraphADT
{
protected:
    using Vertex = VertexClass <V_type>;
    using VertexPtr = std::shared_ptr<Vertex>; // I wanted to introduce them so that when you delete an element, you can return the object by reference without copying it. But I collapsed from an oak tree to implement it.
    using Edge = EdgeClass <Vertex,E_type>;
    using EdgePtr = std::shared_ptr<Edge>; // simular
//    using CollectionFrom = Collection;
//    using CollectionTo = Collection;
    using CollectionFrom = std::unordered_map <Vertex, Edge, typename Vertex::Hash>;// - in default case
    using CollectionTo = std::unordered_map <Vertex, Edge,typename Vertex::Hash >;  // - in default case

public:
    virtual const CollectionFrom    &addVertex(const V_type& value)                           = 0; //add a vertex with value value to the graph and return reference to the created vertex object;
    virtual Vertex  /*VertexPtr*/   removeVertex(const Vertex& vertex)                       = 0; //remove a vertex, provided a reference to vertex object;
    virtual const Edge  &addEdge(const Vertex& from_vertex, const Vertex& to_vertex, const E_type& weight) = 0; //add a edge between from and to vertices with weight, return reference to the created edge object;
    virtual Edge     /*EdgePtr*/    removeEdge(const Edge& edge)                             = 0; //remove an edge, given a reference to an edge object;
    virtual const CollectionFrom    &edgesFrom(const Vertex& vertex)                    const = 0; //return a collection or edge objects that are going from vertex v;
    virtual const CollectionTo      &edgesTo(const Vertex& vertex)                      const = 0; //return a collection or edge objects that are going into vertex v;
    virtual const CollectionFrom    &findVertex(const V_type & value)                   const = 0; //find any vertex with the specified value;
    virtual const Edge  &findEdge(const V_type& from_value, const V_type& to_value)     const = 0; //find any edge with specified values in the source and target vertices;
    virtual const Edge  &hasEdge(const Vertex& from_vertex, const Vertex& to_vertex)    const = 0; //determine whether there exists a directed edge from v to u;

};

#endif // GRAPH_ADT_H

