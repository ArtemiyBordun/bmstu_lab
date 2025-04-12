#ifndef POINT_H
#define POINT_H


class Point3D {
public:
    Point3D() : x(0), y(0), z(0) {}
    Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

    float x;
    float y;
    float z;
};

#endif // POINT_H
