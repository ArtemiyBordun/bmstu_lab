#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //AppContext context;

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addClicked() {

   //context.fileName = name.c_str();

    List<int> gfgd;
}
