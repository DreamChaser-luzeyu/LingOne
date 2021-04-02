#include "widget.h"
#include "ui_widget.h"
#include <QStringListModel>
#include <QDesktopServices>
#include <QUrl>
#include <QListWidgetItem>
#include "dialogdemo.h"
#include <QMessageBox>
#include <QElapsedTimer>
#include "recfile.h"

bool needKillServer;//是否需要运行adb kill-server
QString devS;
QString devIP;//手机的IP地址
int devIndex;
QStringList deviceLstF;
AdbCommand* adbc;
MyTcp* mTcp;
QSettings* mConf;
QString oriPath;//手机上源文件的路径
bool isConnectedTcp = false;
bool isConnectedAdb = false;
extern QHostAddress ipAddr;//当前电脑IP
QString currentDir;
QSystemTrayIcon* tray;

int adbPort = 5555;//adb端口号
bool isFirstRun;//是不是首次运行
bool needConfirm = true;
int tcpPort = 2335;//tcp端口号


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始化当前路径
    currentDir = QDir::currentPath();
    qDebug()<<"当前路径:"<<currentDir;

    //初始化mConf对象
    mConf = new QSettings("Config.ini",QSettings::IniFormat);
    //写配置文件
    //mConf->setValue("Config/IPAddr","192.168.1.216");
    //mConf->setValue("Config/Port","2335");
    //从配置文件读取IP
    //defIPAddr = mConf->value("Config/IPAddr").toString();
    //if(defIPAddr==""){qDebug()<<"读取失败";}
    //qDebug()<<defIPAddr;
    //defPort = mConf->value("Config/Port").toInt();
    //if(defPort==0){qDebug()<<"读取失败";}
    //qDebug()<<defPort;
    //读取接收文件时是否确认
    readConf();
    qDebug()<<"ADB端口："+QString::number(adbPort);
    qDebug()<<"需不需要确认："+QString::number(needConfirm);
    qDebug()<<"是不是首次启动："+QString::number(isFirstRun);

    //设置主界面属性
    mainUI = new MainMenu();
    mainUI->setWindowFlags(mainUI->windowFlags() | Qt::Window);
    mainUI->w = this;
    //this->setWindowFlags(Qt::WindowStaysOnTopHint);
    //刷新配置
    readConf();

    //初始化托盘图标
    tray = new QSystemTrayIcon(this);
    tray->setIcon(QIcon(":/DreamLink_icon.png"));
    tray->show();
    connect(tray,&QSystemTrayIcon::activated,this,&Widget::trayIconAction);



    //显示控件阴影
    setUIShadow();

    //初始化TCP服务,作为服务器无需关心ip地址，端口保持默认2335
    mTcp = new MyTcp();
    //初始化UI
    ncui = new NotConnectedUI(this);
    //qDebug()<<"???";

    //隐藏不想显示的组件
    //ui->textEdit->setVisible(false);
    //ui->btn_connect->setVisible(false);
    ui->btn_finish->setVisible(false);
    ui->btn_finish_2->setVisible(false);

    //初始化adb对象
    //发布的时候改成下面的！
    //adbc = new AdbCommand("D:/PortableSoftware/platform-tools");
    adbc = new AdbCommand();

    //运行kill-server避免出现offline的情况
    QStringList qsl;
    qsl<<"kill-server";
    adbc->runCommand(qsl);

    refreshListView();

    //连接收到文件、文本或ip地址的信号
    connect(mTcp,&MyTcp::recIpAddr,this,&Widget::recIpAddr);
    connect(mTcp,&MyTcp::recFile,this,&Widget::recFilePath);
    connect(mTcp,&MyTcp::recText,this,&Widget::recText);

    //开启tcp服务
    if(mTcp->listen()){
        qDebug()<<"监听成功";
    }else{
        QMessageBox::information(mainUI,"错误","端口冲突，程序可能已在运行或端口被占用");
        exit(-1);
    }

    mainUI->show();
}

Widget::~Widget()
{
    delete ui;
}

//选中列表
void Widget::on_listView_clicked(const QModelIndex &index)
{
    devIndex = index.row();
    devS = deviceLstF[devIndex].split("\t")[0];
    qDebug()<<devS;
    isConnectedAdb = true;
    ui->btn_finish->setVisible(true);
    ui->btn_finish_2->setVisible(true);
}

void Widget::on_btn_connect_clicked()
{
    ncui = new NotConnectedUI();
    ncui->show();
    //this->hide();
}

void Widget::recIpAddr(QString ipAddr){
    devIP = ipAddr.split("\n")[0];
    qDebug()<<"收到信号：收到IP地址"<<devIP;
    QStringList actAdb;
    actAdb<<"-s"<<devS<<"tcpip" << QString::number(adbPort);
    devS = devIP + ":"+QString::number(adbPort);
    adbc->runCommand(actAdb);
    QStringList connAdb;
    connAdb<<"connect"<<devIP+":"+QString::number(adbPort);
    adbc->runCommand(connAdb);
    mainUI->refreshUI();
    refreshListView();
}

void Widget::recFilePath(QString path){
    //qDebug()<<"devS:"<<devS;
    oriPath = path.split("\n")[0];
    qDebug()<<"收到信号：收到文件路径" + oriPath;
    QString fileName = oriPath.split("/")[oriPath.split("/").count()-1];
    qDebug()<<"文件名："<<fileName;
    QStringList pullCommand;
    //adb的离谱bug
    pullCommand<<"-s"<<devS<<"pull"<<oriPath<<currentDir+"/FileReceive/"+fileName;
    RecFile* rcf = new RecFile("file:"+currentDir+"/FileReceive",pullCommand,mainUI,"来自"+devS+"的文件：\n"+path);
    rcf->exec();
}

void Widget::recText(QString text){
    qDebug()<<"收到信号：收到文本" + text;
    DialogDemo* diaRecText = new DialogDemo(this,text);
    diaRecText->exec();

}



void Widget::setUIShadow(){
    UIShadow* mShadow = new UIShadow();
    mShadow->setShadow(ui->btn_connect);
    mShadow->setShadow(ui->btn_finish);
    mShadow->setShadow(ui->listView);
    mShadow->setShadow(ui->label);
    mShadow->setShadow(ui->btn_finish_2);
    mShadow->setShadow(ui->btn_refresh);
    mShadow->setShadow(ui->btn_select);
}

//指定网卡按钮，我懒得改名了
void Widget::on_btn_finish_clicked()
{
    ui->btn_finish_2->setVisible(true);

    ncui = new NotConnectedUI(this);
    ncui->exec();

    //this->hide();
    QStringList sendIpArgs;
    sendIpArgs<<"-s"<<devS<<"shell"
              <<"am"<<"start"<<"-a"<<"android.intent.action.MAIN "
              <<"-n"<<"cn.dreamchaser.bindlinkfinal01/cn.dreamchaser.bindlinkfinal01.MainActivity"
              <<"--es"<<"PcIpAddr"<<"\""+ipAddr.toString()+"\"";
    adbc->runCommand(sendIpArgs);


    //mainUI = new MainMenu();
    //mainUI->setWindowFlags(mainUI->windowFlags() | Qt::Window);
    this->hide();
    mainUI->refreshUI();
    mainUI->show();
}

void Widget::refreshListView(){
    QStringList qsl;
    qsl<<"devices";
    QString result = adbc->runCommand(qsl);
    //把输出进行分割处理
    QStringList deviceLst = result.split("\n",Qt::SkipEmptyParts);
    //计算设备的数量
    int amount = deviceLst.count();
    //保存去除多余东西后的设备列表
    //放到头文件里面了
    deviceLstF.clear();
    for(int i=1; i<amount; i++){
        if(deviceLst[i]!="\r"){
            //ui->textEdit->append(deviceLst[i]);

            deviceLstF.append(deviceLst[i]);
            qDebug()<<deviceLst[i];
        }
    }
    //在listview里面加入设备
    QStringListModel* devLstModel = new QStringListModel();
    //清空列表
    //ui->listView->model()->removeRows(0,ui->listView->model()->rowCount());
    devLstModel->setStringList(deviceLstF);
    ui->listView->setModel(devLstModel);
}

//完成按钮
void Widget::on_btn_finish_2_clicked()
{
    //这一大堆用于刷新手机上的电脑IP地址
    QStringList sendIpArgs;
    sendIpArgs<<"-s"<<devS<<"shell"
              <<"am"<<"start"<<"-a"<<"android.intent.action.MAIN "
              <<"-n"<<"cn.dreamchaser.bindlinkfinal01/cn.dreamchaser.bindlinkfinal01.MainActivity"
              <<"--es"<<"PcIpAddr"<<"\""+ipAddr.toString()+"\"";
    adbc->runCommand(sendIpArgs);
    mainUI->refreshUI();
    this->hide();
    mainUI->show();
}
//刷新设备列表
void Widget::on_btn_refresh_clicked()
{
    refreshListView();

}

//点击托盘图标的槽函数
void Widget::trayIconAction( QSystemTrayIcon::ActivationReason reason )
/* 参数是Qt的保留字，表示对托盘图标的操作，该槽函数功能只实现了单击功能，
 * 可以实现其他功能比如双击、中击，具体可查文档或者Qt自带demo(关键字tray) */
{
    qDebug()<<"点击";
    if ( reason == QSystemTrayIcon::Trigger ){
        qDebug()<<"单击";
        mainUI->show();
    }

}

//延时函数
void Widget::mSleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//选中设备按钮
void Widget::on_btn_select_clicked()
{
    mainUI->refreshUI();
    this->hide();
    mainUI->show();
}

void Widget::readConf(){
    needConfirm = mConf->value("Config/needConfirm").toInt();
    isFirstRun = mConf->value("Config/isFirstRun").toInt();
    adbPort = mConf->value("Config/ADBPort").toInt();
    tcpPort = mConf->value("Config/TCPPort").toInt();
}
