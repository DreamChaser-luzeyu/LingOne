#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adbcommand.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    AdbCommand adbc;
    QStringList args;
    args << "devices";
    ui->textEdit->append(adbc.runCommand(args));
}
