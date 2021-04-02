#include "dialogdemo.h"
#include "ui_dialogdemo.h"
#include <QCloseEvent>
#include <qdesktopservices.h>
#include <QDebug>
#include "uishadow.h"

DialogDemo::DialogDemo(QWidget *parent,QString text) :
    QDialog(parent),
    ui(new Ui::DialogDemo)
{
    ui->setupUi(this);
    this->text = text;
    ui->textEdit->setText(text);
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    UIShadow* mShadow = new UIShadow();
    mShadow->setShadow(ui->btn_cancel);
    mShadow->setShadow(ui->btn_openlink_http);
    mShadow->setShadow(ui->btn_openlink_https);
    mShadow->setShadow(ui->label);
    mShadow->setShadow(ui->textEdit);





}

DialogDemo::~DialogDemo()
{
    delete ui;
}

void DialogDemo::on_btn_cancel_clicked()
{
    this->hide();
}


void DialogDemo::on_btn_openlink_https_clicked()
{
    QStringList link = text.split("https://");
    qDebug()<<"有几个:";
    qDebug()<<link.count();
    if(link.count()>1){
        qDebug()<<"打开链接";
        QDesktopServices::openUrl(QUrl("https://"+link[1].toLatin1()));
        this->hide();
    }
}

void DialogDemo::on_btn_openlink_http_clicked()
{
    QStringList link = text.split("http://");
    if(link.count()>1){
        qDebug()<<"打开链接";
        QDesktopServices::openUrl(QUrl("http://"+link[1].toLatin1()));
        this->hide();
    }
}
