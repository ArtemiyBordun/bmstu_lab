#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initialization();

    connect(ui->EnterLine, &QLineEdit::textEdited, this, &MainWindow::checkEnter);
    connect(ui->ConvertButton, &QPushButton::clicked, this, &MainWindow::onConvertClicked);
    connect(ui->SwapButton, &QPushButton::clicked, this, &MainWindow::swap);
    connect(ui->CopyButton, &QPushButton::clicked, this, &MainWindow::copyInClipboard);

    connect(ui->sourceBase, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &MainWindow::clickOnSourceGroup);
    connect(ui->linesourceOther, &QLineEdit::textEdited, this, &MainWindow::clickOnSourceGroup);
    connect(ui->newBase, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &MainWindow::clickOnNewGroup);
    connect(ui->linenewOther, &QLineEdit::textEdited, this, &MainWindow::clickOnNewGroup);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialization() {
    ui->sourceBase->setId(ui->sourceBinary, BINARY);  //меням id для каждой кнопки
    ui->sourceBase->setId(ui->sourceDecimal, DECIMAL);
    ui->sourceBase->setId(ui->sourceHexadecimal, HEXADECIMAL);
    ui->sourceBase->setId(ui->sourceOther, 0);

    ui->newBase->setId(ui->newBinary, BINARY);
    ui->newBase->setId(ui->newDecimal, DECIMAL);
    ui->newBase->setId(ui->newHexadecimal, HEXADECIMAL);
    ui->newBase->setId(ui->newOther, 0);

    setCat(0);
    doOperation(INITIALIZATION, &context, NULL);
    updateLabels(1);
}

void MainWindow::checkEnter() {
    AppParams* param = (AppParams*)malloc(sizeof(AppParams));
    std::string str = ui->EnterLine->text().toStdString();
    param->cstr = str.c_str();
    doOperation(MYSTRCPY, &context, param);
    free(param);

    updateLabels(0);
}

void MainWindow::clickOnSourceGroup() {
    int base = ui->sourceBase->checkedId();
    if (base)
        ui->linesourceOther->setEnabled(false);
    else {
        ui->linesourceOther->setEnabled(true);
        base = ui->linesourceOther->text().toInt();
    }
    context.sourceBase = base;
    doOperation(CHECK, &context, NULL);
    updateLabels(0);
}

void MainWindow::clickOnNewGroup() {
    int base = ui->newBase->checkedId();
    if (base)
        ui->linenewOther->setEnabled(false);
    else {
        ui->linenewOther->setEnabled(true);
        base = ui->linenewOther->text().toInt();
    }
    context.newBase = base;
    doOperation(CHECK, &context, NULL);
    updateLabels(0);
}

void MainWindow::onConvertClicked() {
    checkEnter();
    if (context.error == NOERROR) {
        setCat(1);
        doOperation(CONVERT, &context, NULL);
        updateLabels(1);
    }
}

void MainWindow::swap() {
    int basetoid = ui->newBase->checkedId();
    int basefromid = ui->sourceBase->checkedId();

    ui->sourceBase->button(basetoid)->setChecked(true);
    ui->newBase->button(basefromid)->setChecked(true);

    if (!basefromid || !basetoid) {
        int baseto = ui->linesourceOther->text().toInt();
        ui->linesourceOther->setText(QString::number(ui->linenewOther->text().toInt()));
        ui->linenewOther->setText(QString::number(baseto));
    }

    clickOnSourceGroup();
    clickOnNewGroup();
}

void MainWindow::copyInClipboard() {
    QApplication::clipboard()->setText(ui->ResultLabel->text());
}

void MainWindow::updateLabels(int result) {
    if (result)
        ui->ResultLabel->setText(context.number);

    switch (context.error) {
        case EMPTY:
            ui->ErrorLabel->setText("Please, enter number");
            break;
        case NOTINT:
            ui->ErrorLabel->setText("The number must be an integer");
            break;
        case NOTBASE:
            ui->ErrorLabel->setText("Incorrect characters have been entered");
            break;
        case NUMBERLONG:
            ui->ErrorLabel->setText("The number is too long");
            break;
        case RESULTLONG:
            ui->ErrorLabel->setText("The result will be too long");
            break;
        case BASESMALL:
            ui->ErrorLabel->setText("The base cannot be less than 2");
            break;
        case BASEBIG:
            ui->ErrorLabel->setText("The base cannot be more than 36");
            break;
        default:
            ui->ErrorLabel->clear();
    }
    if (context.error != NOERROR)
        setCat(-1);
    else if (!result)
        setCat(0);
}

void MainWindow::setCat(int mood) {
    switch (mood) {
        case -1:
            ui->Cat->setStyleSheet("image: url(:/back/sadCat.jpg)");
            break;
        case 0:
            ui->Cat->setStyleSheet("image: url(:/back/waitingCat.jpg)");
            break;
        case 1:
            ui->Cat->setStyleSheet("image: url(:/back/happyCat.jpg)");
            break;
    }
}
