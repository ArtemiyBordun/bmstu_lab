#include "edge.h"

Edge::Edge(Vertex& _begin, Vertex& _end) : _begin(_begin), _end(_end) {}

Vertex& Edge::getBegin()
{
    return _begin;
}

Vertex& Edge::getEnd()
{
    return _end;
}
