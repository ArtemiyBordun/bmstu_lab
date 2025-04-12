#ifndef VERTEX_H
#define VERTEX_H
#include "sceneobject.h"

class Vertex : public SceneObject{
private:
    Point3D position;
public:
    Vertex(Point3D position);
    Point3D getPosition();
    void transform(TransformMatrix) override;
};

#endif // VERTEX_H
