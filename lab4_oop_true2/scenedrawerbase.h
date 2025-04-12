#ifndef SCENEDRAWERBASE_H
#define SCENEDRAWERBASE_H
#include "scene.h"
#include "QPainter"
#include "QPixmap"
#include "memory"
#define TWO 2

class SceneDrawerBase {
public:
    virtual void DrawScene(std::shared_ptr<Scene> scene) = 0;
    virtual ~SceneDrawerBase() {}
};
#endif // SCENEDRAWERBASE_H
