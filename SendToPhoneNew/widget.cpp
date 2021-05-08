#include "widget.h"
#include "ui_widget.h"
#include "uishadow.h"
#include "adbcommand.h"
#include <QStringListModel>
#include <QListWidgetItem>
#include <QDebug>
#include <QSettings>

QStringList deviceLstF;
QString devS;
int devIndex;
AdbCommand* adbc;
QString filePath;
QString adbPath;
QSettings* mConf;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->btn_select->setVisible(false);

    qDebug()<<filePath;
    //adbc = new AdbCommand("D:/PortableSoftware/platform-tools");
    adbc = new AdbCommand(QApplication::applicationDirPath());
    refreshListView();

    //ui->label_2->setText(QApplication::applicationDirPath());

    //ui->textEdit->setText(filePath);
    //qDebug()<<"???";
    //qDebug()<<"FilePath:"<<filePath<<"\n\n";





}

Widget::~Widget()
{
    delete ui;
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

void Widget::on_btn_refresh_clicked()
{
    refreshListView();
}

void Widget::on_listView_clicked(const QModelIndex &index)
{
    devIndex = index.row();
    devS = deviceLstF[devIndex].split("\t")[0];
    qDebug()<<devS;
    ui->btn_select->setVisible(true);
}

void Widget::on_btn_select_clicked()
{
    QStringList mkdircmd;
    mkdircmd << "-s" << devS << "shell" << "mkdir" << "/sdcard/BindFileReceive";
    adbc->runCommand(mkdircmd);
    QStringList pushcmd;
    pushcmd << "-s" << devS << "push" << filePath << "/sdcard/BindFileReceive";
    adbc->runCommand(pushcmd);

    this->close();
}
