#ifndef FACADE_H
#define FACADE_H
#include "normalizationparameters.h"
#include "filereader.h"
#include "qtscenedrawer.h"
#include "facadeoperationresult.h"
#include "transformmatrixbuilder.h"

class Facade {
private:
    shared_ptr<BaseFileReader> _fileReader;
    shared_ptr<SceneDrawerBase> _sceneDrawer;
    shared_ptr<Scene> _scene;
public:
    Facade();
    Facade(QPixmap* pix);
    void drawScene();

    FacadeOperationResult loadScene(string path, NormalizationParameters parameters);
    FacadeOperationResult scaleScene(float x, float y, float z);
    FacadeOperationResult moveScene(float x, float y, float z);
    FacadeOperationResult rotateScene(float x, float y, float z);
};

#endif // FACADE_H
