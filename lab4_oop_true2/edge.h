#ifndef EDGE_H
#define EDGE_H
#include "vertex.h"

class Edge {
private:
    Vertex& _begin;
    Vertex& _end;
public:
    Edge(Vertex& _begin, Vertex& _end);
    Vertex& getBegin();
    Vertex& getEnd();
};

#endif // EDGE_H
