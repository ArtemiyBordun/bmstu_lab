#ifndef FIGURE_H
#define FIGURE_H
#include "vector"
#include "vertex.h"
#include "edge.h"

class Figure : public SceneObject{
    private:
        vector<Vertex>* _vertices;
        vector<Edge>* _edges;
    public:
        Figure(vector<Vertex>* _vertices, vector<Edge>* _edges);
        vector<Vertex>* getVertices();
        vector<Edge>* getEdges();
        void transform(TransformMatrix) override;
};

#endif // FIGURE_H
