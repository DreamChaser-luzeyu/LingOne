#ifndef NOTCONNECTEDUI_H
#define NOTCONNECTEDUI_H

#include <QDialog>
//#include <QWidget>
#include <QHostInfo>
#include <QHostAddress>

namespace Ui {
class NotConnectedUI;
}

class NotConnectedUI : public QDialog
{
    Q_OBJECT

public:
    explicit NotConnectedUI(QWidget *parent = nullptr);
    ~NotConnectedUI();
    bool in_loop;
    void Show_QRcode_Picture(QString message="Hello world!");
    bool isLocalAddress(QHostAddress addr);
    //void doExec();
    //void doClose();

private slots:
    void on_Create_Button_clicked();

    //void on_pushButton_clicked();

    void on_btn_SwitchIP_clicked();

    void on_btn_use_clicked();

private:
    Ui::NotConnectedUI *ui;

    QList<QHostAddress> ipAddrLst;



};

#endif // NOTCONNECTEDUI_H
