#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setFixedHeight(370);
    exp = "0";

    connect(ui->btn0, &QPushButton::clicked, this, &MainWindow::onBtnNumClick);
    connect(ui->btn1, &QPushButton::clicked, this, &MainWindow::onBtnNumClick);
    connect(ui->btn2, &QPushButton::clicked, this, &MainWindow::onBtnNumClick);
    connect(ui->btn3, &QPushButton::clicked, this, &MainWindow::onBtnNumClick);
    connect(ui->btn4, &QPushButton::clicked, this, &MainWindow::onBtnNumClick);
    connect(ui->btn5, &QPushButton::clicked, this, &MainWindow::onBtnNumClick);
    connect(ui->btn6, &QPushButton::clicked, this, &MainWindow::onBtnNumClick);
    connect(ui->btn7, &QPushButton::clicked, this, &MainWindow::onBtnNumClick);
    connect(ui->btn8, &QPushButton::clicked, this, &MainWindow::onBtnNumClick);
    connect(ui->btn9, &QPushButton::clicked, this, &MainWindow::onBtnNumClick);

    connect(ui->btnSum, &QPushButton::clicked, this, &MainWindow::onBtnOperClick);
    connect(ui->btnSub, &QPushButton::clicked, this, &MainWindow::onBtnOperClick);
    connect(ui->btnMult, &QPushButton::clicked, this, &MainWindow::onBtnOperClick);
    connect(ui->btnDiv, &QPushButton::clicked, this, &MainWindow::onBtnOperClick);
    connect(ui->btnDeg, &QPushButton::clicked, this, &MainWindow::onBtnOperClick);

    connect(ui->btnStartBrac, &QPushButton::clicked, this, &MainWindow::onBtnBrkClick);
    connect(ui->btnEndBrac, &QPushButton::clicked, this, &MainWindow::onBtnBrkClick);
    connect(ui->btnPoint, &QPushButton::clicked, this, &MainWindow::onBtnPntClick);

    connect(ui->btnPropor, &QPushButton::clicked, this, &MainWindow::onBtnAddComandClick);
    connect(ui->btnPercent, &QPushButton::clicked, this, &MainWindow::onBtnAddComandClick);

    connect(ui->btnSqrt, &QPushButton::clicked, this, &MainWindow::onBtnMathCommandClick);
    connect(ui->btnSin, &QPushButton::clicked, this, &MainWindow::onBtnMathCommandClick);
    connect(ui->btnCos, &QPushButton::clicked, this, &MainWindow::onBtnMathCommandClick);
    connect(ui->btnTg, &QPushButton::clicked, this, &MainWindow::onBtnMathCommandClick);
    connect(ui->btnCtg, &QPushButton::clicked, this, &MainWindow::onBtnMathCommandClick);

    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onBtnClrClick);
    connect(ui->btnDel, &QPushButton::clicked, this, &MainWindow::onBtnClrClick);

    connect(ui->btnEqual, &QPushButton::clicked, this, &MainWindow::onBtnEqlClick);
    connect(ui->radioBtn, &QRadioButton::clicked, this, &MainWindow::onBntMoreClick);
    connect(ui->btnCow, &QRadioButton::clicked, this, &MainWindow::onBtnCowClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBtnNumClick()
{
    QPushButton* btn = (QPushButton*)sender();
    string num = btn->text().toStdString();
    status = Calculate;
    if (exp == "0")
        exp = num;
    else if (exp[exp.length() - 1] == ')')
        exp += '*' + num;
    else
        exp += num;
    printEquals(exp);
}

void MainWindow::onBtnOperClick()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QString oper = btn->text();
    int length = exp.length();
    if (length > 0 && (isdigit(exp[length - 1]) || exp[length - 1] == ')')) {
        exp += oper.toStdString();
    }
    printEquals(exp);
}

void MainWindow::onBtnBrkClick()
{
    QPushButton* btn = (QPushButton*)sender();
    string bracket = btn->text().toStdString();
    if (exp == "0")
        exp = bracket;
    else if (bracket == "(" && isdigit(exp[exp.length() - 1]))
        exp += '*' + bracket;
    else
        exp += bracket;
    printEquals(exp);
}

void MainWindow::onBtnClrClick()
{
    QPushButton* btn = (QPushButton*)sender();
    string oper = btn->text().toStdString();
    if (oper == "C" || status == Answer)
        exp = "0";
    else
        if (exp != "0" && !exp.empty() && exp.length() != 1)
            exp.pop_back();
        else
            exp = "0";

    status = Calculate;
    printEquals(exp);
}

void MainWindow::onBtnEqlClick()
{
    verificate(false);
    if (status != Error)
    {
        status = Answer;

        try
        {
            shared_ptr<Command<Calculator>> calc = make_shared<CalculatorCommand<Calculator>>(&Calculator::findAnswer);
            shared_ptr<Calculator> obj = make_shared<Calculator>(exp, "");
            calc->execute(obj);
            exp = obj->getExp();
        }
        catch (const runtime_error &e)
        {
            (new QErrorMessage(this))->showMessage(e.what());
        }

        printEquals(exp);
    }
}

void MainWindow::onBtnPntClick()
{
    verificate(true);
    if (status != Error)
    {
        exp += '.';
        printEquals(exp);
    }
    status = Calculate;
}

void MainWindow::onBtnAddComandClick()
{
    QPushButton* btn = (QPushButton*)sender();
    string command = btn->text().toStdString();
    try
    {
        status = Answer;
        shared_ptr<Command<Calculator>> calc = make_shared<CalculatorCommand<Calculator>>(&Calculator::findNum);
        shared_ptr<Calculator> obj = make_shared<Calculator>(exp, command);
        calc->execute(obj);
        exp = obj->getExp();
    }
    catch (const runtime_error &e)
    {
        (new QErrorMessage(this))->showMessage(e.what());
    }
    printEquals(exp);
}

void MainWindow::onBtnMathCommandClick()
{
    QPushButton* btn = (QPushButton*)sender();
    string command = btn->text().toStdString();

    shared_ptr<Command<Calculator>> calc = make_shared<CalculatorCommand<Calculator>>(&Calculator::addMathCommand);
    shared_ptr<Calculator> obj = make_shared<Calculator>(exp, command);
    calc->execute(obj);
    exp = obj->getExp();

    printEquals(exp);
}

void MainWindow::verificate(bool isPoint)
{
    try
    {
        shared_ptr<Command<Validate>> val = make_shared<CalculatorCommand<Validate>>(&Validate::validate);
        shared_ptr< Validate> obj = make_shared<Validate>(exp, isPoint);
        val->execute(obj);
        if (!obj->getErr())
            status = Error;
        else
            status = Calculate;
    }
    catch (const runtime_error &e)
    {
        (new QErrorMessage(this))->showMessage(e.what());
        status = Calculate;
    }
}

void MainWindow::printEquals(string exp)
{
    ui->output->setText(QString::fromStdString(exp));
}

void MainWindow::onBntMoreClick()
{
    if (ui->radioBtn->isChecked())
    {
        MainWindow::setFixedWidth(400);
    }
    else
    {
        MainWindow::setFixedWidth(250);
    }
}

void MainWindow::onBtnCowClick()
{
    QMovie* movie = new QMovie(":/cow.gif");
    ui->Cow->setMovie(movie);
    movie->start();
    cowActive = !cowActive;
    if (cowActive)
        MainWindow::setFixedWidth(1000);
    else
        MainWindow::setFixedWidth(400);

}
