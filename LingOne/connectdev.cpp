#include "connectdev.h"
#include "ui_connectdev.h"

//全局变量
QStringList deviceLstF;
extern QString devS;
extern QString devName;
QStringList phyIpLst;   //PC的物理网卡地址列表
QString ipAddr;         //使用的IP地址

//全局对象
extern AdbCommand* adbc;

ConnectDev::ConnectDev(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDev)
{

    ui->setupUi(this);
    getPhysicalIP();
    initIndex();
    initObj();
    refreshListView();                  //刷新设备列表
    ui->label_ip->setText(ipAddr);      //刷新IP地址标签
    ui->btn_select->setVisible(false);  //默认隐藏选中按钮
    setUIShadow();

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());//无边框和窗口阴影
    this->setAttribute(Qt::WA_TranslucentBackground, true);
}

ConnectDev::~ConnectDev()
{
    delete ui;
}

void ConnectDev::on_btn_help_clicked()
{
    qDebug()<<"OK";
}

void ConnectDev::initIndex(){
    ipIndex = 0;
    if(phyIpLst.size() == 0){
        QMessageBox::warning(this,"错误","未发现网卡或未连接网络");          //没找着网卡直接报错退出
        this->close();
    }
    else if(phyIpLst.size() == 1){
        ui->btn_switch->setVisible(false);                          //只有一个物理网卡就隐藏切换按钮
        ui->label_ip->setVisible(false);
    }
    ipAddr = phyIpLst[ipIndex];
}

void ConnectDev::initObj(){
    //初始化adb对象
    //发布的时候改成下面的！
    //adbc = new AdbCommand("D:/PortableSoftware/platform-tools");
    //adbc = new AdbCommand();
}

void ConnectDev::setUIShadow(){
    UIShadow* mShadow = new UIShadow();
    mShadow->setShadow(ui->btn_refresh);
    mShadow->setShadow(ui->btn_switch);
    mShadow->setShadow(ui->btn_select);
    mShadow->setShadow(ui->btn_close);
    //mShadow->setShadow(ui->btn_help);
    mShadow->setShadow(ui->label);
    mShadow->setBigShadow(ui->label_background);
    //mShadow->setBigShadow(ui->label);
    //mShadow->setBigShadow(ui->MainMenu);
}


//刷新列表的槽函数
void ConnectDev::on_btn_refresh_clicked()
{
    refreshListView();
}

//切换网卡按钮的槽函数
void ConnectDev::on_btn_switch_clicked()
{
    int n = phyIpLst.size();
    //qDebug()<<"数量："<<n;
    ipIndex++;
    if(ipIndex == n){ipIndex = 0;}
    //qDebug()<<"标号："<<ipIndex;
    ipAddr = phyIpLst[ipIndex];
    ui->label_ip->setText(ipAddr);
}

//"选中"按钮槽函数
void ConnectDev::on_btn_select_clicked()
{
    QStringList sendIpArgs;
    sendIpArgs<<"-s"<<devS<<"shell"
              <<"am"<<"start"<<"-a"<<"android.intent.action.MAIN "
              <<"-n"<<"cn.dreamchaser.bindlinkfinal01/cn.dreamchaser.bindlinkfinal01.MainActivity"
              <<"--es"<<"PcIpAddr"<<"\""+ipAddr+"\"";
    adbc->runCommand(sendIpArgs);

    //qDebug()<<devS;
    //std::cout<<devS.toStdString();
    this->close();
}

//选中设备的槽函数
void ConnectDev::on_listView_clicked(const QModelIndex &index)
{
    devIndex = index.row();
    devS = deviceLstF[devIndex].split("\t")[0];
    devName = index.data().toString();
    qDebug() << devName;
    ui->btn_select->setVisible(true);
}




void ConnectDev::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());
}

void ConnectDev::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void ConnectDev::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

void ConnectDev::on_btn_close_clicked()
{
    this->close();
}


/*************************************槽函数结束*********************************************/
//slots end

/*************************************功能函数*********************************************/
//functions

void ConnectDev::getPhysicalIP()
{
    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface interfaceItem, interfaceList)
    {
        if(interfaceItem.flags().testFlag(QNetworkInterface::IsUp)
                &&interfaceItem.flags().testFlag(QNetworkInterface::IsRunning)
                &&interfaceItem.flags().testFlag(QNetworkInterface::CanBroadcast)
                &&interfaceItem.flags().testFlag(QNetworkInterface::CanMulticast)
                &&!interfaceItem.flags().testFlag(QNetworkInterface::IsLoopBack)
                &&!interfaceItem.humanReadableName().contains("VMware")
                &&!interfaceItem.humanReadableName().contains("Virtual")
                &&!interfaceItem.humanReadableName().contains("TAP"))                           //排除虚拟网卡、localhost和回环地址
        {
            QList<QNetworkAddressEntry> addressEntryList=interfaceItem.addressEntries();
            foreach(QNetworkAddressEntry addressEntryItem, addressEntryList)
            {
                if(addressEntryItem.ip().protocol()==QAbstractSocket::IPv4Protocol)
                {
                    //qDebug()<<"------------------------------------------------------------";
                    //qDebug()<<"Adapter Name:"<<interfaceItem.name();
                    //qDebug()<<"Adapter Address:"<<interfaceItem.hardwareAddress();
                    //qDebug()<<"IP Address:"<<addressEntryItem.ip().toString();
                    //qDebug()<<"IP Mask:"<<addressEntryItem.netmask().toString();
                    phyIpLst.append(addressEntryItem.ip().toString());
                }
            }
        }
    }
}

void ConnectDev::refreshListView(){
    QStringList devLstName;
    QStringList qsl;
    qsl<<"devices";
    QString result = adbc->runCommand(qsl);                         //result里面是用换行符分隔的设备列表
    //把输出进行分割处理
    QStringList deviceLst = result.split("\n",Qt::SkipEmptyParts);  //把它们分割到deviceLst里面
    //计算设备的数量
    int amount = deviceLst.count();
    //保存去除多余东西后的设备列表
    deviceLstF.clear();
    devLstName.clear();
    for(int i=1; i<amount; i++){
        if(deviceLst[i]!="\r"){
            //ui->textEdit->append(deviceLst[i]);

            deviceLstF.append(deviceLst[i]);
            QStringList getNameCmd;
            getNameCmd << "-s" << deviceLst[i].split("\t")[0] << "shell"
                       << "getprop" << "ro.product.model";
            devLstName.append(adbc->runCommand(getNameCmd).split("\r")[0]);
            qDebug()<<adbc->runCommand(getNameCmd);
            qDebug()<<deviceLst[i];
        }
    }
    //在listview里面加入设备
    QStringListModel* devLstModel = new QStringListModel();
    //清空列表
    //ui->listView->model()->removeRows(0,ui->listView->model()->rowCount());
    devLstModel->setStringList(devLstName);
    ui->listView->setModel(devLstModel);
}

