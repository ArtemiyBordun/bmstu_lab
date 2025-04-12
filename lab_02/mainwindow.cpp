#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    preInitialize();

    connect(ui->openFileButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->calculateMetricsButton, &QPushButton::clicked, this, &MainWindow::calculateAndDrawMetrics);
    connect(ui->nameRegion, &QLineEdit::textEdited, this, &MainWindow::enterNameRegion);
}

MainWindow::~MainWindow()
{
    deleteList();
    delete ui;
}

void MainWindow::preInitialize() {
    ui->errorLabel->clear();
    ui->infoLabel->clear();
    ui->nameFilelabel->clear();
    context.list = init(region);
    doOperation(INIT, &context, NULL);
}

void MainWindow::openFile() {
    QString str;
    str = QFileDialog::getOpenFileName();
    ui->nameFilelabel->setText(str);

    string name = ui->nameFilelabel->text().toStdString();
    context.fileName = name.c_str();

    doOperation(OPENFILE, &context, NULL);

    if (!context.isFileOpen) {
        context.error = FILEINCOTTECT;
        clearTabel();
    }
    else {
        context.error = NOTERROR;
        enterNameRegion();
    }
    updateError(context.error);
}

void MainWindow::calculateAndDrawMetrics() {
    selectColumn();
    if (context.error == REGIONMISS || context.error == EMPTY) {
        context.error = NOTENTER;
        updateError(context.error);
    }
    if (context.error == NOTERROR) {
        doOperation(CALCULATE, &context, &param);
        updateIteminTable(0, 0, 1);
        drawGraph();
    }
}

void MainWindow::selectColumn() {
    param.columnId = NPG + ui->selectColumn->currentIndex();
}

void MainWindow::enterNameRegion() {
    strncpy(context.prevRegionName, context.regionName, strlen(context.regionName));
    string regionName = ui->nameRegion->text().toStdString();
    strncpy(context.regionName, regionName.c_str(), strlen(regionName.c_str()));
    context.regionName[strlen(regionName.c_str())] = 0;
    if (context.isFileOpen) {
        doOperation(CHECKNAME, &context, &param);
        setTable();
    }
    updateError(context.error);
}

void MainWindow::updateError(ERRORLIST error) {
    if (!context.isFileOpen)
        error = NOTFILE;
    switch (error) {
        case (NOTERROR):
            ui->errorLabel->clear();
            break;
        case (NOTFILE):
            ui->errorLabel->setText("Please download the file!");
            break;
        case (FILEINCOTTECT):
            ui->errorLabel->setText("The file was opened uncorrected!");
            break;
        case(REGIONMISS):
            ui->errorLabel->setText("The entered region is missing!!");
            break;
        case(NOTENTER):
            ui->errorLabel->setText("Enter the region!");
            break;
        default:
            ui->errorLabel->clear();
            break;
    }
}

void MainWindow::setTable() {
    int tableRow = 0;
    ui->table->setColumnCount(URBAN + 1);
    ui->table->setRowCount(context.list->size);
    ui->table->setHorizontalHeaderLabels(QStringList()
                                         << "Year" << "Region"<< "NPG" << "BR" << "DR" << "GDW" << "Urbanization");
    if (param.countRegion) {
        ui->table->setRowCount(param.countRegion);
        tableRow = updateTable(1);
    } else {
        ui->table->setRowCount(context.list->size);
        tableRow = updateTable(0);
    }

    if (tableRow || context.error == EMPTY)
        updateInfoLabel(tableRow);
    else {
        context.error = FILEINCOTTECT;
        clearTabel();
    }
}

int MainWindow::updateTable(int withRegion) {
    int rowsCount = context.list->size;
    List* curList = (List*)malloc(sizeof(List));
    curList->head = context.list->head;

    int tableRow = 0; // Счетчик для отслеживания текущей позиции в таблице
    while (hasNext(curList)) {
        if ((withRegion && strcmp(context.regionName, curList->head->data.region))) {
            rowsCount--;
        }
        else {
            updateIteminTable(curList, tableRow, 0); // Вызываем функцию с текущей позицией в таблице
            tableRow++; // Увеличиваем счетчик текущей позиции в таблице
        }
        next(curList);
    }
    free(curList);
    return rowsCount;
}

void MainWindow::updateIteminTable(List* list, int tableRow, int whichTabel) {
    QTableWidgetItem* item;
    if (!whichTabel) {
        for (int j = 0; j <= URBAN; j++) {
            if (j == YEAR)
                item = new QTableWidgetItem(QString::number(list->head->data.year));
            else if (j == REGION)
                item = new QTableWidgetItem(QString::fromStdString(list->head->data.region));
            else if (j == NPG)
                item = new QTableWidgetItem(QString::number(list->head->data.npg));
            else if (j == BR)
                item = new QTableWidgetItem(QString::number(list->head->data.br));
            else if (j == DR)
                item = new QTableWidgetItem(QString::number(list->head->data.dr));
            else if (j == GDW)
                item = new QTableWidgetItem(QString::number(list->head->data.gdw));
            else if (j == URBAN)
                item = new QTableWidgetItem(QString::number(list->head->data.urban));
            ui->table->setItem(tableRow, j, item); // Используем tableRow для установки элемента в нужную позицию в таблице
        }
    } else {
        for (int j = 0; j <= URBAN; j++) {
            if (j == 0)
                item = new QTableWidgetItem(QString::number(param.metrics.min));
            else if (j == 1)
                item = new QTableWidgetItem(QString::number(param.metrics.max));      //устанавливаем значения в таблицу метрик
            else if (j == TWO)
                item = new QTableWidgetItem(QString::number(param.metrics.median));
            ui->tableMetrics->setItem(j, 0, item);
        }
    }
}

void MainWindow::updateInfoLabel(int correctLines) {
    int errorLines = context.list->size - correctLines;
    QString infoText = QString("Total lines in the file: %1\nThe number of lines with an error: %2\nThe number of lines recorded: %3")
            .arg(context.list->size)
            .arg(errorLines)
            .arg(correctLines);
    ui->infoLabel->setText(infoText);
}

void MainWindow::clearTabel() {
    ui->table->clear();
    ui->table->setRowCount(0);
    ui->table->setColumnCount(0);

    for (int i = 0; i <= TWO; i++) {
        ui->tableMetrics->setItem(i, 0, 0);
    }
}

void MainWindow::deleteList() {
    doOperation(DELETE, &context, NULL);
}

void MainWindow::drawGraph() {
    ui->graph->clear();
    double width = ui->graph->width();
    double height = ui->graph->height();
    QPixmap pix(width, height);
    QPainter painter(&pix);
    pix.fill(Qt::white);

    double oy = drawAxis(&painter, height);

    double offsetForOx = drawOffSet(&painter, oy);

    painter.translate(50, oy); //перемещает центр начала координат

    double k = calculateK();

    drawMetrics(&painter, k, param.metrics.max);
    drawMetrics(&painter, k, param.metrics.min);
    drawMetrics(&painter, k, param.metrics.median);

    drawParam(&painter, k, offsetForOx);

    ui->graph->setPixmap(pix);
}

double MainWindow::drawAxis(QPainter* painter, double height) {
    nameAxis(painter);

    painter->setPen(QColor(0, 0, 0, 255));
    painter->drawLine(50, 30, 50, 160); //верхняя ось Oy
    painter->drawLine(50, 160, 50, 290); //нижняя ось Oy

    double oy = height / TWO;
    if (param.metrics.min >= 0) {
        oy = height + 100;
    } else if(param.metrics.max <= 0) {
        oy = height - 100;
    }

    painter->drawLine(50, oy, 571, oy); //ось Ox
    painter->drawLine(571, oy, 566, oy - 5); //стрелка оси x
    painter->drawLine(571, oy, 566, oy + 5);

    return oy;
}

void MainWindow::nameAxis(QPainter* painter) {
    QTableWidgetItem* item_x = ui->table->horizontalHeaderItem(0);
    QString header_for_ox = item_x->text();
    if (header_for_ox == "Year")
        painter->drawText(600, 200, header_for_ox);  //подписываем ось Ox

    QTableWidgetItem *item_y = ui->table->horizontalHeaderItem(param.columnId); //выводим название метрики на ось y
    QString header_for_oy = item_y->text();
    painter->drawText(50, 20, header_for_oy);
}

double MainWindow::drawOffSet(QPainter* painter, double oy) {
    QFont font;
    font.setPixelSize(12);
    int rows_for_ox = ui->table->rowCount();
    int offsetForOx = 531 / (rows_for_ox + 1); //высчитываем шаг
    for (int i = 1; i <= rows_for_ox; i++) {
        QString years = QString::number(FIRSTYEAR + i - 1);
        painter->rotate(-90); //поворот на 90 градусов осей
        painter->setFont(font);
        painter->drawText(-(oy + 40), 50 + i * offsetForOx, years); //выводим год
        painter->rotate(90); //поворот осей обратно
        painter->drawLine(45 + i * offsetForOx, oy - 5, 45 + i * offsetForOx, oy + 5);
    }
    return offsetForOx;
}

void MainWindow::drawMetrics(QPainter* painter, double k, double metric) {
    painter->setPen(QColor(154, 156, 27));
    QString metrics_max = QString::number(metric);   //выводим метрики
    painter->drawText(-30, k * metric, metrics_max);
    painter->drawLine(-5, k * metric, 550, k * metric);
}

double MainWindow::calculateK() {
    double k;
    if (abs(param.metrics.max) >= abs(param.metrics.min))   //считаем коэффицент смещения
        k = -100 / param.metrics.max;
    else
        k = 100 / param.metrics.min;

    return k;
}

void MainWindow::drawParam(QPainter* painter, double k, double offsetForOx) {
    QString stats_item = ui->table->item(0, param.columnId)->text(); // отрисовываем первую точку
    double curMetric = stats_item.toDouble();
    painter->drawEllipse(-10 + 1 * offsetForOx, k * curMetric - 2.5, 5, 5);
    painter->fillRect(-10 + 1 * offsetForOx, k * curMetric - 2.5, 5, 5, QColor(38, 80, 105));

    for (int i = 1; i <= ui->table->rowCount(); i++) {  //выводим точки
        double prevMetrics = curMetric;
        QString stats_item = ui->table->item(i - 1, param.columnId)->text(); // получаем статистику
        curMetric = stats_item.toDouble();

        painter->drawEllipse(-10 + i * offsetForOx, k * curMetric - 2.5, 5, 5);  //рисуем точку
        painter->fillRect(-10 + i * offsetForOx, k * curMetric - 2.5, 5, 5, QColor(38, 80, 105));

        painter->setPen(QColor(38, 80, 105));
        painter->drawLine(-3.5 + (i - 1) * offsetForOx, k * prevMetrics, -3.5 + i * offsetForOx, k * curMetric); //соединяем точки
    }
}
