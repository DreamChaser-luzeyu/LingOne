#include "MyTcp.h"
#include <QDebug>
#include <QTextCodec>

extern QString ipAddrClientStr;
extern bool isConnectedTcp;

MyTcp::MyTcp(){
    this->ipAddr = "127.0.0.1";
    this->port = 2335;
    mSocket = new QTcpSocket;
    mServer = new QTcpServer;
}

MyTcp::MyTcp(QString ipAddr, int port){
    this->ipAddr = ipAddr;
    this->port = port;
    mSocket = new QTcpSocket;
}

void MyTcp::connectToHost(){
    mSocket->connectToHost(QHostAddress(ipAddr),port);
    //连接 连接服务器成功的信号
    connect(mSocket,&QTcpSocket::connected,this,[](){qDebug()<<"Connected";});
    //连接 收到数据的信号
    connect(mSocket,&QTcpSocket::readyRead,this,[this](){
        QByteArray ba;
        ba = mSocket->readLine();
        //recData = ba;
        QTextCodec* tc = QTextCodec::codecForName("UTF-8");
        recData = tc-> toUnicode(ba);
        qDebug()<<"接收数据 "+recData;
        qDebug()<<ba;
    });
    //连接 连接断开的信号
    connect(mSocket,&QTcpSocket::disconnected,this,[](){qDebug()<<"Disconnected";});
}

QString MyTcp::getReceiveData(){
    return this->recData;
}

void MyTcp::writeData(QByteArray content){
    mSocket->write(content);
    //注意：与安卓通信时，如果使用了readLine方法，那么必须再手动发送一个换行符
    //QByteArray ba("\n", 1);
    //mSocket->write(ba);
}

bool MyTcp::listen(){
    bool flag = mServer->listen(QHostAddress::Any,port);
    if(flag){
        qDebug()<<"监听成功";
        //有客户端连接，触发信号
        connect(mServer,&QTcpServer::newConnection,this,[this](){
            //准备接收并处理消息
            //返回下一个即将连接的套接字
            mSocket = mServer->nextPendingConnection();
            qDebug()<<"接收到连接";
            connect(mSocket,&QTcpSocket::readyRead,this,[this](){
                QByteArray ba;
                ba = mSocket->readAll();
                //recData = ba;
                //qDebug()<<"接收到消息："+recData;
                QTextCodec* tc = QTextCodec::codecForName("UTF-8");
                recData = tc-> toUnicode(ba);
                qDebug()<<"接收数据 "+recData;
                qDebug()<<ba;

                //握手
                if(recData=="Connected\n"){
                    qDebug()<<"TCP连接成功";

                }
                if(recData.split('\t').count()>0){
                //接收手机IP地址
                    if(recData.split("\t",Qt::SkipEmptyParts)[0]=="#IP"){
                        qDebug()<<"收到IP地址";
                        isConnectedTcp = true;
                        //writeData("Connected\n");
                        emit recIpAddr((recData.split("\t",Qt::SkipEmptyParts))[1]);
                    }
                    else if(recData.split("\t",Qt::SkipEmptyParts)[0]=="#FILE"){
                        qDebug()<<"收到文件：" + recData.split("\t",Qt::SkipEmptyParts)[1];
                        emit recFile((recData.split("\t",Qt::SkipEmptyParts))[1]);
                        //isConnectedTcp = true;
                        //writeData("Connected\n");
                    }
                    else if(recData.split("\t",Qt::SkipEmptyParts)[0]=="#TEXT"){
                        qDebug()<<"收到文本：" + recData.split("\t",Qt::SkipEmptyParts)[1];
                        emit recText((recData.split("\t",Qt::SkipEmptyParts))[1]);
                    }else{}
                }

            });
        });
        return true;
    }
    else{qDebug()<<"监听失败"; return false;}
}

/*
void MyTcp::recIpAddr(QString ipAddr){
    qDebug()<<"发送信号：收到IP地址";
}

void MyTcp::recFile(QString path){
    qDebug()<<"发送信号：收到IP地址";
}*/
