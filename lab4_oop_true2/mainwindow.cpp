#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();

    connect(ui->btnOpenFile, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->btnNormal, &QPushButton::clicked, this, &MainWindow::onBtnNormalClick);

    connect(ui->btnScale, &QPushButton::clicked, this, &MainWindow::onBtnScaleClick);
    connect(ui->btnMove, &QPushButton::clicked, this, &MainWindow::onBtnMoveClick);

    connect(ui->btnRotateX, &QPushButton::clicked, this, &MainWindow::onBtnRotateXClick);
    connect(ui->btnRotateY, &QPushButton::clicked, this, &MainWindow::onBtnRotateYClick);
    connect(ui->btnRotateZ, &QPushButton::clicked, this, &MainWindow::onBtnRotateZClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    pix = QPixmap();
    pix = QPixmap(ui->model->width(), ui->model->height());
    facade = Facade(&pix);

    ui->normalLineMax->setText("100");
    ui->normalLineMin->setText("0");
    ui->normalLineStep->setText("10");
    onBtnNormalClick();

    ui->scaleLineX->setText("1");
    ui->scaleLineY->setText("1");
    ui->scaleLineZ->setText("1");

    ui->moveLineX->setText("5");
    ui->moveLineY->setText("0");
    ui->moveLineZ->setText("0");

    ui->rotateLineX->setText("45");
    ui->rotateLineY->setText("45");
    ui->rotateLineZ->setText("45");

    result.setErrorMessage("Open the file");
    outputError(&result);
}

void MainWindow::openFile()
{
    if (result.getErrorMessage() == "Open the file")
    {
        QString str;
        str = QFileDialog::getOpenFileName(this, tr("Choose file"), QDir::currentPath(), tr("*.csv"));
        if (str.isEmpty())
            return;
        ui->fileName->setText(str);
        ui->Normalization->setEnabled(false);
        ui->btnOpenFile->setEnabled(false);

        string name = ui->fileName->text().toStdString();

        facade.loadScene(name, param);

        //facade.rotateScene(45, 0, 0);
        outputModel();
        result.setErrorMessage("");
        outputError(&result);
    }

}

void MainWindow::onBtnNormalClick()
{
    if (!ui->normalLineMax->text().isEmpty() && !ui->normalLineMax->text().toDouble() &&
            !ui->normalLineMin->text().isEmpty() && !ui->normalLineMin->text().toDouble() &&
            !ui->normalLineStep->text().isEmpty() && !ui->normalLineStep->text().toDouble())
        result.setErrorMessage("Set the normalization parameters");
    else
    {
        param.max = ui->normalLineMax->text().toDouble();
        param.min = ui->normalLineMin->text().toDouble();
        param.step = ui->normalLineStep->text().toDouble();

    }
    outputError(&result);
}

void MainWindow::onBtnScaleClick()
{
    if (result.getErrorMessage() != "Open the file")
    {
        float x = ui->scaleLineX->text().toDouble();
        float y = ui->scaleLineY->text().toDouble();
        float z = ui->scaleLineZ->text().toDouble();

        result = facade.scaleScene(x, y, z);

        if (result.isSuccess())
        {
            outputModel();
        }
        outputError(&result);
    }
}

void MainWindow::onBtnMoveClick()
{
    if (result.getErrorMessage() != "Open the file")
    {
        float x = ui->moveLineX->text().toDouble();
        float y = ui->moveLineY->text().toDouble();
        float z = ui->moveLineZ->text().toDouble();

        result = facade.moveScene(x, y, z);

        if (result.isSuccess())
        {
            outputModel();
        }
        outputError(&result);
    }
}

void MainWindow::onBtnRotateXClick()
{
    if (result.getErrorMessage() != "Open the file")
    {
        float x = ui->rotateLineX->text().toDouble();
        result = facade.rotateScene(x, 0, 0);
        if (result.isSuccess())
        {
            outputModel();
        }
        outputError(&result);
    }
}

void MainWindow::onBtnRotateYClick()
{
    if (result.getErrorMessage() != "Open the file")
    {
        float y = ui->rotateLineY->text().toDouble();
        result = facade.rotateScene(0, y, 0);
        if (result.isSuccess())
        {
            outputModel();
        }
        outputError(&result);
    }
}

void MainWindow::onBtnRotateZClick()
{
    if (result.getErrorMessage() != "Open the file")
    {
        float z = ui->rotateLineZ->text().toDouble();
        result = facade.rotateScene(0, 0, z);
        if (result.isSuccess())
        {
            outputModel();
        }
        outputError(&result);
    }
}

void MainWindow::outputModel()
{
    facade.drawScene();
    ui->model->setPixmap(pix);
}

void MainWindow::outputError(FacadeOperationResult* result)
{
    ui->errorLabel->setText(QString::fromStdString(result->getErrorMessage()));
}
