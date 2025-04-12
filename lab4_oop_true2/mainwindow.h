#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QFileDialog>
#include <QPainter>

#include "facade.h"
#include "facadeoperationresult.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPixmap pix;
    Facade facade;
    FacadeOperationResult result;
    NormalizationParameters param;

    void init();

    void openFile();
    void onBtnNormalClick();

    void onBtnScaleClick();
    void onBtnMoveClick();

    void onBtnRotateXClick();
    void onBtnRotateYClick();
    void onBtnRotateZClick();

    void outputModel();
    void outputError(FacadeOperationResult* error);
};
#endif // MAINWINDOW_H
