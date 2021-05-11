#include "settings.h"
#include "ui_settings.h"
#include "uishadow.h"

extern int adbPort;//adb端口号
extern bool isFirstRun;//是不是首次运行
extern int tcpPort;//tcp端口号
extern QString currentDir;

extern QSettings* mConf;

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());//无边框和窗口阴影
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    mConf = new QSettings("Config.ini",QSettings::IniFormat);
    ui->le_adbport->setText(mConf->value("Config/ADBPort").toString());
    ui->le_tcpport->setText(mConf->value("Config/TCPPort").toString());



    UIShadow* mShadow = new UIShadow();
    mShadow->setBigShadow(ui->label_background);
    mShadow->setShadow(ui->label);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());
}

void Settings::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void Settings::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

void Settings::on_btn_close_2_clicked()
{
    this->close();
}


void Settings::on_btn_save_clicked()
{
    mConf->setValue("Config/ADBPort",ui->le_adbport->text());
    //needConfirm = mConf->value("Config/needConfirm").toInt();
    isFirstRun = mConf->value("Config/isFirstRun").toInt();
    adbPort = mConf->value("Config/ADBPort").toInt();
    tcpPort = mConf->value("Config/TCPPort").toInt();
}

void Settings::on_btn_close_clicked()
{
    //needConfirm = mConf->value("Config/needConfirm").toInt();
    isFirstRun = mConf->value("Config/isFirstRun").toInt();
    adbPort = mConf->value("Config/ADBPort").toInt();
    tcpPort = mConf->value("Config/TCPPort").toInt();
    this->hide();
}

void Settings::on_btn_add_clicked()
{
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
    out << "@=\"" << currentDir << "\\\\BindSendToPhone.exe " << "\\\"%1\\\"\"";
    out.flush();
    file.close();
    currentDir.replace("\\\\","/");
    QDesktopServices::openUrl(QUrl(currentDir+"/add.reg", QUrl::TolerantMode));
}

void Settings::on_btn_remove_clicked()
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

