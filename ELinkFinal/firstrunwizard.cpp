#include "firstrunwizard.h"
#include "ui_firstrunwizard.h"
#include "widget.h"
extern int adbPort;//adb端口号
extern bool isFirstRun;//是不是首次运行
extern bool needConfirm;
extern int tcpPort;//tcp端口号

FirstRunWizard::FirstRunWizard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirstRunWizard)
{
    ui->setupUi(this);
    mConf = new QSettings("Config.ini",QSettings::IniFormat);
    ui->le_adbport->setText(mConf->value("Config/ADBPort").toString());
    ui->le_tcpport->setText(mConf->value("Config/TCPPort").toString());


}

FirstRunWizard::~FirstRunWizard()
{
    delete ui;
}

void FirstRunWizard::on_btn_save_clicked()
{
    //写配置文件
    mConf->setValue("Config/ADBPort",ui->le_adbport->text());
    needConfirm = mConf->value("Config/needConfirm").toInt();
    isFirstRun = mConf->value("Config/isFirstRun").toInt();
    adbPort = mConf->value("Config/ADBPort").toInt();
    tcpPort = mConf->value("Config/TCPPort").toInt();
}

//完成按钮
void FirstRunWizard::on_btn_close_clicked()
{
    needConfirm = mConf->value("Config/needConfirm").toInt();
    isFirstRun = mConf->value("Config/isFirstRun").toInt();
    adbPort = mConf->value("Config/ADBPort").toInt();
    tcpPort = mConf->value("Config/TCPPort").toInt();
    this->hide();
}
