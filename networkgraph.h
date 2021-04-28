#ifndef NETWORKGRAPH_H
#define NETWORKGRAPH_H
#include <functional>

#include "graph.h"

namespace NWG {

struct Wire{
    int length;
    uint32_t bwidth;
    explicit Wire(int l=0, uint32_t w=-1 )
        :length(l),bwidth(w)
    {} // -1 : max
    Wire  operator  -(const Wire& w) const;
    Wire &operator -=(const Wire& w);
    Wire  operator  +(const Wire& w) const;
    Wire &operator +=(const Wire& w);
    bool  operator  <(const Wire& w) const;
    bool  operator  >(const Wire& w) const;
};

template<class vertex_T>
class NetWorkGraph : public Graph<vertex_T, Wire>
{
    using Vertex = typename Graph<vertex_T, Wire>::Vertex;
    using Edge   = typename Graph<vertex_T, Wire>::Edge;
    using VertexArr = typename Graph<vertex_T, Wire>::VertexArr;
    using Path = typename Graph<vertex_T, Wire>::Path;
    using CondFunc = typename Graph<vertex_T, Wire>::CondFunc;
public:
    /*
     * Time complexity same with findMinPath:
     *      Average: O(|V|*|V|)
     * By requirements of minimum bandwidth this function find path between vertices
     */
    Path findMinPathWithMinBandwidth(const Vertex& s, const Vertex& t, unsigned int minBw);
};

template<class vertex_T>
typename NetWorkGraph<vertex_T>::Path NetWorkGraph<vertex_T>::findMinPathWithMinBandwidth(const Vertex &source, const Vertex &target,  uint32_t minBw)
{
    CondFunc lessThan = [minBw](const Edge& edge){
        return edge.weight().bwidth >= minBw;
    };
    Path path = this->findMinPath(source, target, lessThan);
    return path;
}

Wire Wire::operator -(const Wire &w) const
{
    return Wire(length - w.length,bwidth);
}

Wire &Wire::operator -=(const Wire &w)
{
    length -= w.length;return *this;
}

Wire Wire::operator +(const Wire &w) const
{
    return Wire(length + w.length, std::min(bwidth,w.bwidth));
}

Wire &Wire::operator +=(const Wire &w)
{
    length += w.length;
    bwidth = std::min(bwidth,w.bwidth);
    return *this;
}

bool Wire::operator <(const Wire &w) const
{
    if( length == w.length)
        return bwidth < w.bwidth;
    return length < w.length;
}

bool Wire::operator >(const Wire &w) const
{
    if( length == w.length)
        return bwidth > w.bwidth;
    return length > w.length;
}
} // end NWG namespace


#endif // NETWORKGRAPH_H
