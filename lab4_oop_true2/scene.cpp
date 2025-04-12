#include "scene.h"

Scene::Scene() {}

Scene::Scene(std::vector<Figure>& _figures) : _figures(_figures) {}

void Scene::TransformFigures(TransformMatrix matrix)
{
    for(size_t i = 0; i < _figures.size(); i++)
        _figures[i].transform(matrix);
}

vector<Figure> Scene::getFigures() const
{
    return _figures;
}
