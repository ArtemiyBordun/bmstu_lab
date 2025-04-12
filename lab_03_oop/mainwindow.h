#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QErrorMessage>
#include <QKeyEvent>
#include <QMovie>

#include <string>
#include <iostream>

#include "calculatorcommand.h"

using namespace std;

enum programStatus
{
    Calculate,
    Error,
    Answer
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
    void printEquals(string exp);

private:
    Ui::MainWindow *ui;
    //void keyPressEvent(QKeyEvent *e) override;

    void onBtnNumClick();
    void onBtnOperClick();
    void onBtnBrkClick();
    void onBtnClrClick();
    void onBtnEqlClick();
    void onBtnPntClick();
    void onBtnAddComandClick();
    void onBtnMathCommandClick();

    void verificate(bool isPoint);
    void onBntMoreClick();
    void onBtnCowClick();
    string exp;

    bool cowActive = false;
    programStatus status = Calculate;
};
#endif // MAINWINDOW_H
