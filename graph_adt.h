#ifndef GRAPH_ADT_H
#define GRAPH_ADT_H
#include <memory>
#include <ostream>
#include <functional>

/* class GraphADTSupplement
 * Template parameters:
 *  E_type - type of the edge value
 *  V_type - type of the vertex value
 *
 * This is a helper class required to provide access to the Vertex Class and EdfeClass
 */
template< typename V_type, typename E_type>
struct GraphADTSupplement
{
    class EdgeClass;
    class VertexClass;
};


/* Abstract class GraphADT
 * Template parameters:
 *  E_type - type of the edge value
 *  V_type - type of the vertex value
 */
template< typename V_type, typename E_type, template <class, class ...> class Collection, typename T, typename ... Args >
class GraphADT
{

protected:
    using Vertex    = typename GraphADTSupplement< V_type, E_type>::VertexClass;
    using Edge      = typename GraphADTSupplement < V_type, E_type>::EdgeClass;

    using CollectionFrom = Collection < T, Args...> ;
    using CollectionTo   = Collection < T, Args...> ;

public:
    virtual const Vertex  &addVertex(const V_type& value)                                   = 0; //add a vertex with value value to the graph and return reference to the created vertex object;
    virtual const Vertex  &removeVertex(const Vertex& vertex)                                = 0; //remove a vertex, provided a reference to vertex object;
    virtual const Edge    &addEdge(const Vertex& from_vertex, const Vertex& to_vertex, const E_type& weight) = 0; //add a edge between from and to vertices with weight, return reference to the created edge object;
    virtual const Edge    &removeEdge(const Edge& edge)                                      = 0; //remove an edge, given a reference to an edge object;
    virtual const CollectionFrom &edgesFrom(const Vertex& vertex)                     const = 0; //return a collection or edge objects that are going from vertex v;
    virtual const CollectionTo   &edgesTo(const Vertex& vertex)                       const = 0; //return a collection or edge objects that are going into vertex v;
    virtual const Vertex  &findVertex(const V_type & value)                           const = 0; //find any vertex with the specified value;
    virtual const Edge    &findEdge(const V_type& from_value, const V_type& to_value) const = 0; //find any edge with specified values in the source and target vertices;
    virtual bool          hasEdge(const Vertex& from_vertex, const Vertex& to_vertex) const = 0; //determine whether there exists a directed edge from v to u;

};

/* Class Vertex
 * Template parameters:
 *  V_type - type of the vertex value
 *  E_type - type of the Edge value
 */
template<typename V_type, typename E_type>
class GraphADTSupplement<V_type, E_type>::VertexClass
{
    std::shared_ptr<V_type> _v;
public:
    VertexClass() = default;
    ~VertexClass() = default;
    explicit VertexClass(const V_type& V):_v(new V_type(V)){}
    explicit operator V_type()const{return *_v;}
    const V_type &v() const {return *_v ;}
    bool operator ==(const VertexClass& V) const {return *_v == *V._v;}
    bool operator >=(const VertexClass& V) const {return *_v >= *V._v;}
    bool operator <=(const VertexClass& V) const {return *_v <= *V._v;}
    bool operator >(const VertexClass& V) const {return *_v > *V._v;}
    bool operator <(const VertexClass& V) const {return *_v < *V._v;}
    struct Hash {
        std::size_t operator()(const VertexClass& V) const {
            return std::hash<V_type>{}(*(V._v));
        }
    };
    friend std::ostream &operator << (std::ostream& out, const VertexClass& vertex){
        return out << *(vertex._v);
    }

};


/* Class Edge
 * Template parameters:
 *  Vertex - type of the vertex class
 *  E_type - type of the Edge value
 */
template<typename V_type, typename E_type>
class GraphADTSupplement<V_type, E_type>::EdgeClass
{
    VertexClass _from;
    VertexClass _to;
    std::shared_ptr<E_type> _weight;
public:
    EdgeClass() = default;
    ~EdgeClass() = default;
    explicit EdgeClass(const VertexClass& from, const VertexClass& to, const E_type& weight)
        :_from(from),_to(to),_weight(new E_type(weight))
    {}
    EdgeClass(const VertexClass& from, const VertexClass& to, const std::shared_ptr<E_type>& weight_ptr)
        :_from(from),_to(to),_weight(weight_ptr)
    {}
    explicit operator E_type()const{return *_weight;}
    bool operator ==(const EdgeClass& E) const  {return E._from==_from && E._to == _to;}
    EdgeClass reverse() const {return EdgeClass(_to,_from,_weight);}
    const VertexClass& to()     const {return _to;}
    const VertexClass& from()   const {return _from;}
    const E_type&   weight()    const {return *_weight;}
    struct Hash {
          std::size_t operator()(const EdgeClass& E) const {
              return typename VertexClass::Hash{}(E._from) ^ typename VertexClass::Hash{}(E._to)<<1 ^ std::hash<V_type>{}(*E._weight)<<2;
          }
      };
};





#endif // GRAPH_ADT_H

