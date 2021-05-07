#include "mainmenu.h"
#include "ui_mainmenu.h"
//#include <iostream>

//全局变量
QString currentDir;
QString exeDir;
bool isFirstRun;
int adbPort;
int tcpPort;
QString devS;//设备序列号
QString devName; //设备名称
QString devIP;//设备IP
QString oriPath;//从手机上接收的文件路径

//全局对象
QSettings* mConf;
QSystemTrayIcon* tray;
MyTcp* mTcp;
AdbCommand* adbc;
AdbCommand* progc;

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenu)
{
    //std::cout<<"Hello,world!";

    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    initApp();      //初始化程序
    readConf();     //读取配置文件
    initObj();      //初始化对象
    initWindow();   //初始化窗口
    initDev();      //初始化设备
    initNetwork();  //初始化网络
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());
}

void MainMenu::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void MainMenu::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}




/*************************************初始化函数开始*********************************************/
//init functions begin

void MainMenu::initApp(){
    //初始化当前路径
    currentDir = QDir::currentPath();               //打开可执行文件的路径
    exeDir = QApplication::applicationDirPath();    //可执行文件所在的路径

    //初始化托盘图标
    tray = new QSystemTrayIcon(this);
    tray->setIcon(QIcon(":/BindIcon.png"));
    tray->show();
    connect(tray,&QSystemTrayIcon::activated,this,&MainMenu::trayIconAction);

    //显示控件阴影
    setUIShadow();
    ui->pushButton->setVisible(false);
}

void MainMenu::readConf(){
    //初始化mConf对象,必须在这里事先初始化，不能跟别的一起
    mConf = new QSettings("Config.ini",QSettings::IniFormat);
    isFirstRun = mConf->value("Config/isFirstRun").toInt();
    adbPort = mConf->value("Config/ADBPort").toInt();
    tcpPort = mConf->value("Config/TCPPort").toInt();

    qDebug()<<"当前路径:"<<currentDir;
    qDebug()<<"ADB端口："+QString::number(adbPort);
    qDebug()<<"是不是首次启动："+QString::number(isFirstRun);
}

void MainMenu::initObj(){
    //初始化TCP服务,作为服务器无需关心ip地址，端口从配置文件中读取
    mTcp = new MyTcp(tcpPort);

    //初始化adb对象
    //发布的时候改成下面的！
    //adbc = new AdbCommand("D:/PortableSoftware/platform-tools");
    adbc = new AdbCommand();

    //发布时记得改过来！
    //scrc = new AdbCommand("D:/PortableSoftware/scrcpy-win64-v1.17");
    //progc = new AdbCommand("D:/PortableSoftware");
    progc = new AdbCommand();
}

void MainMenu::initWindow(){
    conD = new ConnectDev(this);
    st = new Settings(this);

    //rcf需要获得信息后才能new

}

void MainMenu::initDev(){
    //运行kill-server避免出现offline的情况
    QStringList qsl;
    qsl<<"kill-server";
    //adbc->runCommand(qsl);
}



void MainMenu::initNetwork(){
    //连接收到文件、文本或ip地址的信号
    connect(mTcp,&MyTcp::recIpAddr,this,&MainMenu::recIpAddr);
    connect(mTcp,&MyTcp::recFile,this,&MainMenu::recFilePath);
    connect(mTcp,&MyTcp::recText,this,&MainMenu::recText);

    //开启tcp服务
    if(mTcp->listen()){
        qDebug()<<"监听成功";
    }else{
        QMessageBox::information(this,"错误","端口冲突，程序可能已在运行或端口被占用");
        exit(-1);
    }
}

void MainMenu::setUIShadow(){
    UIShadow* mShadow = new UIShadow();
    //mShadow->setShadow(ui->btn_settings);
    mShadow->setShadow(ui->btn_minimize);
    mShadow->setShadow(ui->btn_close);
    //mShadow->setShadow(ui->btn_about);
    //mShadow->setShadow(ui->btn_update);
    //mShadow->setShadow(ui->label_devConnected);
    //mShadow->setShadow(ui->btn_help);
    mShadow->setShadow(ui->btn_minimize);
    //mShadow->setShadow(ui->btn_switchdev);
    mShadow->setBigShadow(ui->label_background);
    //mShadow->setShadow(ui->btn_scrcpy);
    //mShadow->setShadow(ui->btn_scrcpy);
    mShadow->setShadow(ui->label);
    //mShadow->setBigShadow(ui->MainMenu);
}

/*************************************初始化函数结束*********************************************/
//init functions end



/*************************************槽函数开始*********************************************/
//slots begin

//托盘图标点击动作
/* 参数是Qt的保留字，表示对托盘图标的操作，该槽函数功能只实现了单击功能，
 * 可以实现其他功能比如双击、中击，具体可查文档或者Qt自带demo(关键字tray) */
void MainMenu::trayIconAction( QSystemTrayIcon::ActivationReason reason ){
    //qDebug()<<"点击";
    if (reason == QSystemTrayIcon::Trigger){
        qDebug()<<"单击";
        this->show();
    }
}

void MainMenu::recIpAddr(QString ipAddr){
    devIP = ipAddr.split("\n")[0];                              //解析手机发来的IP
    qDebug()<<"收到信号：收到IP地址"<<devIP;
    QStringList actAdb;
    actAdb<<"-s"<<devS<<"tcpip" << QString::number(adbPort);    //adb端口转发命令
    devS = devIP+":"+QString::number(adbPort);
    adbc->runCommand(actAdb);
    QStringList connAdb;
    connAdb<<"connect"<<devIP+":"+QString::number(adbPort);     //adb连接命令
    adbc->runCommand(connAdb);
    ui->label_devname->setText("已连接到："+devName);     //刷新界面
}

void MainMenu::recFilePath(QString path){
    oriPath = path.split("\n")[0];                              //解析手机发来的文件路径
    qDebug()<<"收到信号：收到文件路径" + oriPath;

    //解决adb pull中文的bug
    QString fileName = oriPath.split("/")[oriPath.split("/").count()-1];
    qDebug()<<"文件名："<<fileName;
    QStringList pullCommand;
    //adb的离谱bug
    pullCommand<<"-s"<<devS<<"pull"<<""""+oriPath+""""<<""""+currentDir+"/FileReceive/"+fileName+"""";
    qDebug()<<""""+currentDir+"/FileReceive/"+fileName+"""";
    //接收文件的窗口
    rcf = new ReceiveFile("file:"+currentDir+"/FileReceive", "来自" + devS + "的文件：\n" + path, pullCommand, this);
    rcf->exec();
}

void MainMenu::recText(QString text){
    qDebug()<<"收到信号：收到文本" + text;
    rct = new ReceiveText(text, this);
    rct->exec();
}

//点击最小化按钮
void MainMenu::on_btn_minimize_clicked()
{
    this->hide();
}
//点击关闭按钮
void MainMenu::on_btn_close_clicked()
{
    this->close();
}

void MainMenu::on_btn_scrcpy_clicked()
{
    qDebug()<<devS;
    QStringList args;
    args<<"-s"<<devS;

    progc->runOtherCommand("scrcpy.exe",args);
}

void MainMenu::on_btn_settings_clicked()
{
    st->exec();
}

void MainMenu::on_btn_switchdev_clicked()
{
    conD->exec();
    qDebug()<<devS;
}

void MainMenu::on_btn_wechat_clicked()
{
    qDebug()<<devS;

    QStringList adbArgs;
    adbArgs << "-s" << devS << "shell"
            << "am" << "start" << "-n" << "com.tencent.mm/.ui.LauncherUI";
    adbc->runCommand(adbArgs);
    QStringList args;
    args<<"-s"<<devS;
    progc->runOtherCommand("scrcpy.exe",args);
}

void MainMenu::on_btn_tim_clicked()
{
    qDebug()<<devS;

    QStringList adbArgs;
    adbArgs << "-s" << devS << "shell"
            << "am" << "start" << "-n"
            << "com.tencent.tim/com.tencent.mobileqq.activity.SplashActivity";
    adbc->runCommand(adbArgs);

    QStringList args;
    args<<"-s"<<devS;

    progc->runOtherCommand("scrcpy.exe",args);
}

void MainMenu::on_btn_qq_clicked()
{
    qDebug()<<devS;

    QStringList adbArgs;
    adbArgs << "-s" << devS << "shell"
            << "am" << "start" << "-n"
            << "com.tencent.tim/com.tencent.mobileqq.activity.SplashActivity";
    adbc->runCommand(adbArgs);


    QStringList args;
    args<<"-s"<<devS;

    progc->runOtherCommand("scrcpy.exe",args);
}

/*************************************槽函数结束*********************************************/
//slots end








void MainMenu::on_pushButton_clicked()
{
    rcf = new ReceiveFile("file:"+currentDir+"/FileReceive", "来自" + devS + "的文件：\n" , QStringList(), this);
    rcf->exec();
    rct = new ReceiveText("Hello,world!", this);
    rct->exec();
}

void MainMenu::on_btn_allfile_clicked()
{
    QStringList args;
    args << devS << "/sdcard/";
    progc->runOtherCommand("files.exe",args);
}

void MainMenu::on_btn_wechat_file_clicked()
{
    QStringList args;
    args << devS << "/sdcard/Android/data/com.tencent.mm/MicroMsg/Download/";
    progc->runOtherCommand("files.exe",args);
}

void MainMenu::on_btn_tim_file_clicked()
{
    QStringList args;
    args << devS << "/sdcard/Android/data/com.tencent.tim/Tencent/Timfile_recv/";
    progc->runOtherCommand("files.exe",args);
}

void MainMenu::on_btn_qq_file_clicked()
{
    QStringList args;
    args << devS << "/sdcard/Android/data/com.tencent.mobileqq/Tencent/QQfile_recv/";
    progc->runOtherCommand("files.exe",args);
}
