#include "vertex.h"
Vertex::Vertex(Point3D position) : position(position) {}

Point3D Vertex::getPosition() {
    return position;
}

void Vertex::transform(TransformMatrix matrix) {
    Point3D newPoint;
    newPoint = matrix.transformPoint(position);
    position = newPoint;
}
