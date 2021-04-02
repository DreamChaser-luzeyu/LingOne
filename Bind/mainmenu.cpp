#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QDebug>
#include "adbcommand.h"
#include "uishadow.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QShortcut>
#include <QApplication>

extern QSettings* mConf;
extern Widget w;
extern bool isFirstRun;//是不是首次运行
extern QString pcName;
extern QHostAddress ipAddr;//注意：这是电脑的IP！！！
extern QList<QHostAddress> ipAddrLstF;//所有有效的IP列表
extern int index;//正在使用的IP编号
extern int validIPs;//电脑有效的ip数量
extern QString devS;//设备名称
extern int devIndex;
extern QStringList deviceLstF;//设备列表，还需要去掉后面的东西
extern AdbCommand* adbc;
AdbCommand* scrc;

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    frw = new FirstRunWizard(this);

    ui->setupUi(this);
    this->parent = parent;
    //debug用
    //qDebug()<<"MainMenu里面";
    //qDebug()<<ipAddr.toString();
    //qDebug()<<pcName;
    //qDebug()<<index;
    //qDebug()<<validIPs;
    //qDebug()<<deviceLstF[devIndex];
    //qDebug()<<devS;
    UIShadow* mShadow = new UIShadow();
    mShadow->setShadow(ui->label);
    mShadow->setShadow(ui->label_2);
    mShadow->setShadow(ui->pushButton);
    mShadow->setShadow(ui->pushButton_2);
    mShadow->setShadow(ui->pushButton_3);
    mShadow->setShadow(ui->label_3);

    ui->label_3->setText("     已连接到："+devS);
    if(devS==""){ui->label_3->setText("     未连接"+devS);}

    if(isFirstRun){
        frw->exec();
        mConf->setValue("Config/isFirstRun","0");
    }

    //QShortcut* qsc = new QShortcut(QKeySequence(Qt::Key_F12), this);
    //qsc->setContext(Qt::ApplicationShortcut);
    //connect(qsc,&QShortcut::activated,this,[](){qDebug()<<"Pressed";});


}

MainMenu::~MainMenu()
{
    delete ui;
}


void MainMenu::on_pushButton_clicked()
{
    qDebug()<<devS;
    QStringList args;
    args<<"-s"<<devS;
    //发布时记得改过来！
    //scrc = new AdbCommand("D:/PortableSoftware/scrcpy-win64-v1.17");
    scrc = new AdbCommand();
    scrc->runOtherCommand("scrcpy.exe",args);
}

//切换设备的按钮，忘命名了
void MainMenu::on_pushButton_2_clicked()
{
    this->hide();
    w->show();
}

void MainMenu::on_pushButton_3_clicked()
{
    this->hide();
}

//初始化界面
void MainMenu::refreshUI(){
    UIShadow* mShadow = new UIShadow();
    mShadow->setShadow(ui->label);
    mShadow->setShadow(ui->label_2);
    mShadow->setShadow(ui->pushButton);
    mShadow->setShadow(ui->pushButton_2);
    mShadow->setShadow(ui->pushButton_3);
    mShadow->setShadow(ui->label);
    ui->label_3->setText("     已连接到："+devS);
}

//关于
void MainMenu::on_pushButton_4_clicked()
{
    QMessageBox::information(this,"关于","作者：酷安@肉包砸_\nbilibili@绫依的肉包砸");
}

//检查更新
void MainMenu::on_pushButton_5_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.dreamchaser-luzeyu.info/index.php/2021/02/07/%e7%89%88%e6%9c%ac%e5%8f%91%e5%b8%83/", QUrl::TolerantMode));
}

void MainMenu::on_btn_settings_clicked()
{
    frw->show();
}

void MainMenu::keyPressEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_C  &&  event->modifiers() == (Qt::AltModifier | Qt::ControlModifier)){
        qDebug()<<"快捷键";
    }

}
