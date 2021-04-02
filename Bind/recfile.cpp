#include "recfile.h"
#include "ui_recfile.h"
#include "adbcommand.h"
#include <QElapsedTimer>
#include <QDesktopServices>
#include "uishadow.h"

RecFile::RecFile(QString url,QStringList cmd,QWidget *parent,QString content) :
    QDialog(parent),
    ui(new Ui::RecFile)
{
    ui->setupUi(this);
    ui->textEdit->setText(content);
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    this->cmd = cmd;
    this->url = url;
    UIShadow* mShadow = new UIShadow();
    mShadow->setShadow(ui->textEdit);
    mShadow->setShadow(ui->btn_acceptFile);
    mShadow->setShadow(ui->btn_cancel);
    mShadow->setShadow(ui->label);




}

RecFile::~RecFile()
{
    delete ui;
}

void RecFile::on_btn_acceptFile_clicked()
{
    QElapsedTimer t;
    t.start();
    while(t.elapsed()<500);
    AdbCommand* adbc = new AdbCommand();//调试时无法正常收到文件，正常现象
    adbc->runCommand(cmd);
    QDesktopServices::openUrl(QUrl(url, QUrl::TolerantMode));
    hide();
}

void RecFile::on_btn_cancel_clicked()
{
    hide();
    //done(0);
}
