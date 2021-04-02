#ifndef MYTCP_H
#define MYTCP_H
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>

class MyTcp : public QObject
{
    Q_OBJECT
public:
    MyTcp();
    MyTcp(QString, int);
    void connectToHost();
    QString getReceiveData();
    void writeData(QByteArray);
    bool listen();

private:
    QString ipAddr;
    int port;
    QString recData;
    QTcpServer* mServer;
    QTcpSocket* mSocket;

signals:
    void recFile(QString path);
    void recHandShake();
    void recIpAddr(QString ipAddr);
    void recText(QString text);
};

#endif // UISHADOW_H
