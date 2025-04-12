#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QFileDialog>
#include <QPainter>

#include "appcontex.h"
#include "entrypoint.h"

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
    AppContext context;

    void openFile();
    void onBtnNormalClick();

    void onBtnScaleClick();
    void onBtnMoveClick();

    void onBtnRotateXClick();
    void onBtnRotateYClick();
    void onBtnRotateZClick();

    void outputModel();
    void outputError();
};
#endif // MAINWINDOW_H
