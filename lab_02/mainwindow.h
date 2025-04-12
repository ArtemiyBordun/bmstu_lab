#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <string.h>
#include <QFileDialog>
#include <QPainter>

#include "entrypoint.h"
#include "appcontex.h"

using namespace std;

enum GRAPHPARAMETR {
    ROTATE = 90,
    FIRSTYEAR = 1990
};

enum TABELPARAM {
    YEAR = 0,
    REGION = 1,
    NPG = 2,
    BR = 3,
    DR = 4,
    GDW = 5,
    URBAN = 6
};

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
    RegionData region;
    AppParam param;

    void preInitialize();
    void openFile();
    void calculateAndDrawMetrics();
    void selectColumn();
    void enterNameRegion();
    void updateError(ERRORLIST error);
    void setTable();
    int updateTable(int withRegion);
    int updateTablewithRegion(int rowsCount);
    void updateIteminTable(List* list, int tableRow, int whichTabel);
    void updateInfoLabel(int correctLines);
    void clearTabel();
    void deleteList();

    double drawAxis(QPainter* painter, double height);
    double drawOffSet(QPainter* painter, double oy);
    void nameAxis(QPainter* painter);
    void drawMetrics(QPainter* painter, double k, double metric);
    void drawParam(QPainter* painter, double k, double offsetForOx);
    void drawGraph();

    double calculateK();

};
#endif // MAINWINDOW_H
