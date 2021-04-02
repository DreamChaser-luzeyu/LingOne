#include "notconnectedui.h"
#include "ui_notconnectedui.h"
#include <QImage>
#include <string>
#include <vector>
#include "QrCode.hpp"
#include <QNetworkInterface>
#include <QDebug>
#include "mytcp.h"
#include <QApplication>
#include <QEventLoop>

QString pcName;
QHostAddress ipAddr;//注意：这是电脑的IP！！！
//QHostAddress ipAddrClient;//注意：这是手机IP！！
QString ipAddrClientStr;//手机IP的字符串形式
QList<QHostAddress> ipAddrLstF;//所有有效的IP列表
int index=0;//正在使用的IP编号
int validIPs;//电脑有效的ip数量
extern MyTcp* mTcp;

using namespace qrcodegen;
NotConnectedUI::NotConnectedUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotConnectedUI)
{
    ui->setupUi(this);
    //获得计算机名和IP地址
    pcName = QHostInfo::localHostName();
    qDebug()<<pcName;
    //获得所有IP地址
    this->ipAddrLst = QNetworkInterface::allAddresses();
    int len = ipAddrLst.count();
    qDebug()<<len;
    for(int i=0; i<len; i++){
        //qDebug()<<ipAddrLst[i].toString();
        if(isLocalAddress(ipAddrLst[i])){
            qDebug()<<ipAddrLst[i].toString();
            ipAddrLstF.append(ipAddrLst[i]);
        }
    }
    ipAddr = ipAddrLstF[0];
    validIPs = ipAddrLstF.count();
    qDebug()<<"finish";
    on_Create_Button_clicked();




}

NotConnectedUI::~NotConnectedUI()
{
    delete ui;
}


//我也不知道这块儿是怎么做的
void NotConnectedUI::Show_QRcode_Picture(QString message)
{

    // Manual operation
    std::vector<QrSegment> segs =
        QrSegment::makeSegments(message.toUtf8());
    QrCode qr1 = QrCode::encodeSegments(
        segs, QrCode::Ecc::HIGH, 5, 10, 2, false);
    //创建二维码画布
    QImage QrCode_Image=QImage(qr1.getSize(),qr1.getSize(),QImage::Format_RGB888);

    for (int y = 0; y < qr1.getSize(); y++) {
        for (int x = 0; x < qr1.getSize(); x++) {
            if(qr1.getModule(x, y)==0)
                QrCode_Image.setPixel(x,y,qRgb(255,255,255));
            else
                QrCode_Image.setPixel(x,y,qRgb(0,0,0));
        }
    }

    //图像大小转换为适当的大小
    QrCode_Image=QrCode_Image.scaled(ui->label->width(),ui->label->height(),
                    Qt::KeepAspectRatio);
    //转换为QPixmap在Label中显示
    ui->label->setPixmap(QPixmap::fromImage(QrCode_Image));

}


//判断是不是普通局域网ipv4地址
bool NotConnectedUI::isLocalAddress(QHostAddress addr){
    quint32 nIPv4 = addr.toIPv4Address();
        quint32 nMinRange1 = QHostAddress("10.0.0.0").toIPv4Address();
        quint32 nMaxRange1 = QHostAddress("10.255.255.255").toIPv4Address();

        quint32 nMinRange2 = QHostAddress("172.16.0.0").toIPv4Address();
        quint32 nMaxRange2 = QHostAddress("172.31.255.255").toIPv4Address();

        quint32 nMinRange3 = QHostAddress("192.168.0.0").toIPv4Address();
        quint32 nMaxRange3 = QHostAddress("192.168.255.255").toIPv4Address();

        if ((nIPv4 >= nMinRange1 && nIPv4 <= nMaxRange1)
                || (nIPv4 >= nMinRange2 && nIPv4 <= nMaxRange2)
                || (nIPv4 >= nMinRange3 && nIPv4 <= nMaxRange3)) {
            return true;
        } else {
            return false;
        }
}

//实现应用程序级阻塞
/*
void NotConnectedUI::doExec(){
    this->show();
    in_loop = true;
    //QApplication::eventLoop()->enterLoop();
}

void NotConnectedUI::doClose(){
    if (in_loop){
        in_loop = false;
        //QApplication::eventLoop()->exitLoop();
    }
    this->close();
}*/





void NotConnectedUI::on_Create_Button_clicked()
{

    Show_QRcode_Picture(ipAddr.toString()+"\n"+pcName);
    qDebug()<<ipAddr.toString()+"\n"+pcName;
    ui->textEdit->setText(ipAddr.toString()+"\n"+pcName);
    //Show_QRcode_Picture(ui->textEdit->toPlainText());
}

void NotConnectedUI::on_btn_SwitchIP_clicked()
{
    index++;
    if(index==validIPs){index = 0;}
    ipAddr = ipAddrLstF[index];
    on_Create_Button_clicked();

}

void NotConnectedUI::on_btn_use_clicked()
{
    //parent->hide();
    this->hide();
}
