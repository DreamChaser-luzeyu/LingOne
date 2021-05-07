#ifndef CONNECTDEV_H
#define CONNECTDEV_H

#include <QDialog>
#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include <QNetworkInterface>
#include <QList>
#include <iostream>
#include <QMessageBox>
#include <QMouseEvent>

#include "adbcommand.h"
#include "uishadow.h"

namespace Ui {
class ConnectDev;
}

class ConnectDev : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDev(QWidget *parent = nullptr);
    ~ConnectDev();
    void refreshListView();
    void getPhysicalIP();
    void initObj();
    void initIndex();
    void setUIShadow();

    //无边框移动
    bool m_bPressed = true;
    QPoint m_point;

    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_btn_help_clicked();
    void on_btn_refresh_clicked();
    void on_btn_switch_clicked();
    void on_btn_select_clicked();
    void on_listView_clicked(const QModelIndex &index);

    void on_btn_close_clicked();

private:
    Ui::ConnectDev *ui;
    int devIndex;                 //选中的设备下标
    int ipIndex;                  //当前使用的IP下标
};

#endif // CONNECTDEV_H
