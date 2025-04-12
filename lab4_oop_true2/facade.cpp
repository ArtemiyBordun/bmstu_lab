#include "facade.h"

Facade::Facade() {}

Facade::Facade(QPixmap* pix)
{
    _fileReader = make_shared<FileReader>();
    _sceneDrawer = make_shared<QtSceneDrawer>(pix);
    _scene = make_shared<Scene>();
}

FacadeOperationResult Facade::loadScene(string path, NormalizationParameters parametes)
{
    FacadeOperationResult result;
    try
    {
        _scene = _fileReader->readScene(path, parametes);
    }
    catch (const runtime_error & error) {
        result.setErrorMessage(error.what());
    }
    return result;
}

void Facade::drawScene()
{
    _sceneDrawer->DrawScene(_scene);
}

FacadeOperationResult Facade::scaleScene(float x, float y, float z)
{
    FacadeOperationResult result;
    result.setErrorMessage("");
    TransformMatrix matr;
    if (x <= 0 || y <= 0 || z <= 0) {
        result.setErrorMessage("Uncorrected parameters");
    }
    else
    {
        matr = TransformMatrixBuilder::createScaleMatrix(x, y, z);
        _scene->TransformFigures(matr);
    }
    return result;
}

FacadeOperationResult Facade::moveScene(float x, float y, float z)
{
    FacadeOperationResult result;
    result.setErrorMessage("");
    TransformMatrix matr;
    matr = TransformMatrixBuilder::createMoveMatrix(x, -y, z);
    _scene->TransformFigures(matr);
    return result;
}

FacadeOperationResult Facade::rotateScene(float x, float y, float z)
{
    FacadeOperationResult result;
    result.setErrorMessage("");
    TransformMatrix matr;
    if (x == 0 && y == 0 && z == 0)
    {
        result.setErrorMessage("Uncorrected parameters");
        return result;
    }
    if (x != 0)
        matr = TransformMatrixBuilder::createRotationXMatrix(x);

    if (y != 0)
        matr = TransformMatrixBuilder::createRotationYMatrix(y);

    if (z != 0)
        matr = TransformMatrixBuilder::createRotationZMatrix(z);

    _scene->TransformFigures(matr);
    return result;
}

