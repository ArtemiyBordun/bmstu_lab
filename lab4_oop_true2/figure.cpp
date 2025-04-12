#include "figure.h"

Figure::Figure(vector<Vertex>* _vertices, vector<Edge>* _edges) : _vertices(_vertices), _edges(_edges) {}

void Figure::transform(TransformMatrix matrix) {
    for (size_t i = 0; i < _vertices->size(); i++)
        _vertices->at(i).transform(matrix);
}

vector<Vertex>* Figure::getVertices()
{
    return _vertices;
}

vector<Edge>* Figure::getEdges()
{
    return _edges;
}
