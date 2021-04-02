#include "firstrunwizard.h"
#include "ui_firstrunwizard.h"
#include "widget.h"
#include <QMessageBox>
#include <QTextCodec>
#include <QDesktopServices>
#include <QSettings>

extern int adbPort;//adb端口号
extern bool isFirstRun;//是不是首次运行
extern bool needConfirm;
extern int tcpPort;//tcp端口号
extern QString currentDir;


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

void FirstRunWizard::on_btn_add_clicked(){
    qDebug()<<currentDir;
    QString sFilePath = currentDir+"/add.reg";
    qDebug()<<sFilePath;
    QFile file(sFilePath);
    //方式：Append为追加，WriteOnly，ReadOnly
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QMessageBox::critical(this, "提示", "无法创建文件");
        //return -1;
    }
    QTextStream out(&file);
    //out<<"要写入内容"<<"\n";
    out << "Windows Registry Editor Version 5.00" << "\n";
    out << "\n";
    out << "[HKEY_CLASSES_ROOT\\*\\shell\\BindSendToPhone\\command]" << "\n";
    currentDir.replace("/","\\\\");
    out << "@=\"" << currentDir << "\\\\BindSendToPhone.exe" << " %1\"";
    out.flush();
    file.close();
    currentDir.replace("\\\\","/");
    QDesktopServices::openUrl(QUrl(currentDir+"/add.reg", QUrl::TolerantMode));
}

void FirstRunWizard::on_btn_remove_clicked()
{
    qDebug()<<currentDir;
    QString sFilePath = currentDir+"/rem.reg";
    qDebug()<<sFilePath;
    QFile file(sFilePath);
    //方式：Append为追加，WriteOnly，ReadOnly
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QMessageBox::critical(this, "提示", "无法创建文件");
    }
    QTextStream out(&file);
    //out<<"要写入内容"<<"\n";
    out << "Windows Registry Editor Version 5.00" << "\n";
    out << "\n";
    out << "[-HKEY_CLASSES_ROOT\\*\\shell\\BindSendToPhone]" << "\n";
    out.flush();
    file.close();
    QDesktopServices::openUrl(QUrl(currentDir+"/rem.reg", QUrl::TolerantMode));
}
