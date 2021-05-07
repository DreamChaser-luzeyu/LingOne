#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QDir>
#include <QSettings>
#include <qsystemtrayicon.h>
#include <QMessageBox>
#include <QMouseEvent>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

#include "uishadow.h"
#include "mytcp.h"
#include "adbcommand.h"
#include "connectdev.h"
#include "settings.h"
#include "receivefile.h"
#include "receivetext.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

    void initApp();//获取运行目录、IP地址等信息
    void initObj();//实例化对象
    void initDev();//初始化设备
    void readConf();//读取配置文件
    void initNetwork();//初始化网络
    void initWindow();//初始化窗口

    //无边框移动
    bool m_bPressed = true;
    QPoint m_point;

    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


public slots:
    void trayIconAction(QSystemTrayIcon::ActivationReason reason);
    void recIpAddr(QString ipAddr);
    void recFilePath(QString path);
    void recText(QString text);

private slots:
    void on_btn_minimize_clicked();
    void on_btn_close_clicked();
    void on_btn_scrcpy_clicked();
    void on_btn_settings_clicked();
    void on_btn_switchdev_clicked();
    void on_btn_wechat_clicked();
    void on_btn_tim_clicked();
    void on_btn_qq_clicked();

    void on_pushButton_clicked();

    //void on_btn_scrcpy_2_clicked();

    void on_btn_allfile_clicked();

    void on_btn_wechat_file_clicked();

    void on_btn_tim_file_clicked();

    void on_btn_qq_file_clicked();

private:
    Ui::MainMenu *ui;
    void setUIShadow();//显示控件阴影

    //窗口列表
    ConnectDev* conD;               //连接设备的窗口
    Settings* st;                   //设置的窗口
    ReceiveFile* rcf;               //收到文件的窗口
    ReceiveText* rct;               //收到文本的窗口

};
#endif // MAINMENU_H
