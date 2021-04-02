#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "notconnectedui.h"
#include "mainmenu.h"
#include "adbcommand.h"
#include <QSettings>
#include "uishadow.h"
#include "mytcp.h"
#include <QSystemTrayIcon>



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public slots:
    void trayIconAction(QSystemTrayIcon::ActivationReason reason);


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void refreshListView();





private slots:
    //void on_pushButton_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_btn_connect_clicked();

    void on_btn_finish_clicked();

    void recIpAddr(QString ipAddr);

    void recFilePath(QString path);
    //void on_listView_indexesMoved(const QModelIndexList &indexes);

    void recText(QString text);

    void on_btn_finish_2_clicked();

    void on_btn_refresh_clicked();


    void on_btn_select_clicked();

private:
    void setUIShadow();
    void mSleep(int msec);
    void readConf();
    Ui::Widget *ui;
    NotConnectedUI* ncui;
    MainMenu* mainUI;



    QSettings* mConf;
    QString defIPAddr;
    int defPort;

};
#endif // WIDGET_H
