#ifndef QTSCENEDRAWER_H
#define QTSCENEDRAWER_H
#include "scenedrawerbase.h"

class QtSceneDrawer : public SceneDrawerBase{
private:
    QPixmap* _pic;
public:
    QtSceneDrawer(QPixmap* pic);
    void DrawScene(shared_ptr<Scene>) override;
};

#endif // QTSCENEDRAWER_H
