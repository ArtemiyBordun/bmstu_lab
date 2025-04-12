#include "qtscenedrawer.h"
QtSceneDrawer::QtSceneDrawer(QPixmap* pic) : _pic(pic) {}

void QtSceneDrawer::DrawScene(std::shared_ptr<Scene> scene)
{
    QPainter painter(_pic);
    _pic->fill(Qt::white);
    painter.translate(_pic->width() / 2, _pic->height() / 2);
    painter.setPen(QColor(Qt::GlobalColor::black));
    vector<Figure> figure = scene->getFigures();
    for (size_t i = 0; i < figure[0].getEdges()->size(); i++)
    {
        Point3D begin = figure[0].getEdges()->at(i).getBegin().getPosition();
        Point3D end = figure[0].getEdges()->at(i).getEnd().getPosition();
        painter.drawLine(begin.x, begin.y, end.x, end.y);
    }
}
