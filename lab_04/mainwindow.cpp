#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    context.error = notSetNormalParam;
    doOperation(&context, Init);
    outputError();

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

void MainWindow::openFile()
{
    if (context.error != notSetNormalParam)
    {
        QString str;
        str = QFileDialog::getOpenFileName();
        ui->fileName->setText(str);
        ui->Normalization->setEnabled(false);

        string name = ui->fileName->text().toStdString();
        context.fileName = name.c_str();
        doOperation(&context, LoadData);
        outputModel();
        outputError();
    }

}

void MainWindow::onBtnNormalClick()
{
    if (!ui->normalLineMax->text().isEmpty() && !ui->normalLineMax->text().toDouble() &&
            !ui->normalLineMin->text().isEmpty() && !ui->normalLineMin->text().toDouble() &&
            !ui->normalLineStep->text().isEmpty() && !ui->normalLineStep->text().toDouble())
        context.error = notSetNormalParam;
    else
    {
        context.error = notError;
        context.normalParam.max = ui->normalLineMax->text().toDouble();
        context.normalParam.min = ui->normalLineMin->text().toDouble();
        context.normalParam.step = ui->normalLineStep->text().toDouble();
    }
    outputError();
}

void MainWindow::onBtnScaleClick()
{
    if (context.error != notError)
        return;
    context.k.x = ui->scaleLineX->text().toDouble();
    context.k.y = ui->scaleLineY->text().toDouble();
    context.k.z = ui->scaleLineZ->text().toDouble();
    doOperation(&context, Scale);
    if (context.error != notError)
    {
        outputError();
        return;
    }
    else
        outputModel();
}

void MainWindow::onBtnMoveClick()
{
    if (context.error != notError)
        return;
    context.k.x = ui->moveLineX->text().toDouble();
    context.k.y = -ui->moveLineY->text().toDouble();
    context.k.z = ui->moveLineZ->text().toDouble();
    doOperation(&context, Move);
    if (context.error != notError)
    {
        outputError();
        return;
    }
    else
        outputModel();
}

void MainWindow::onBtnRotateXClick()
{
    if (context.error != notError)
        return;
    context.rotateAxis = X;
    context.rotate = ui->rotateLineX->text().toDouble();
    doOperation(&context, Rotate);
    if (context.error != notError)
    {
        outputError();
        return;
    }
    else
        outputModel();
}

void MainWindow::onBtnRotateYClick()
{
    if (context.error != notError)
        return;
    context.rotateAxis = Y;
    context.rotate = ui->rotateLineY->text().toDouble();
    doOperation(&context, Rotate);
    if (context.error != notError)
    {
        outputError();
        return;
    }
    else
        outputModel();
}

void MainWindow::onBtnRotateZClick()
{
    if (context.error != notError)
        return;
    context.rotateAxis = Z;
    context.rotate = ui->rotateLineZ->text().toDouble();
    doOperation(&context, Rotate);
    if (context.error != notError)
    {
        outputError();
        return;
    }
    else
        outputModel();
}

void MainWindow::outputModel()
{
    QPixmap pix(ui->model->width(), ui->model->height());
    QPainter painter(&pix);
    pix.fill(Qt::white);

    painter.translate(pix.width() / 2, pix.height() / 2);
    painter.setPen(QColor(Qt::GlobalColor::black));

    for (size_t i = 0; i < context.columns - 1; i++)
        painter.drawLine(context.model[i].x, context.model[i].y,
                         context.model[i + 1].x, context.model[i + 1].y);
    for (size_t i = 0; i < context.rows - 1; i++)
        painter.drawLine(context.model[i * context.columns].x, context.model[i * context.columns].y,
                context.model[(i + 1) * context.columns].x, context.model[(i + 1) * context.columns].y);

    for (size_t i = context.columns + 1; i < context.countPoint; i++)
    {
        if (i % context.columns != 0)
        {
            painter.drawLine(context.model[i].x, context.model[i].y, context.model[i - 1].x, context.model[i - 1].y);
            painter.drawLine(context.model[i].x, context.model[i].y, context.model[i - context.columns].x, context.model[i - context.columns].y);
        }
    }
    ui->model->setPixmap(pix);
}

void MainWindow::outputError()
{
    switch (context.error)
    {
        case (notError):
            ui->errorLabel->clear();
            break;
        case (notSetNormalParam):
            ui->errorLabel->setText("Please set the normalization parameters");
            break;
        case (inCorrectParam):
            ui->errorLabel->setText("Check the input parameters");
            break;
        case (memoryError):
            ui->errorLabel->setText("Memory allocation error");
            break;
        case (fileError):
            ui->errorLabel->setText("The file did not open correctly");
            break;
        default:
            ui->errorLabel->clear();
    }
}
