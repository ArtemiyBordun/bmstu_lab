#ifndef SCENE_H
#define SCENE_H
#include "figure.h"

class Scene {
    private:
        std::vector<Figure> _figures;
    public:
        Scene();
        Scene(std::vector<Figure>& _figures);
        std::vector<Figure> getFigures() const;
        void TransformFigures(TransformMatrix);
};

#endif // SCENE_H
