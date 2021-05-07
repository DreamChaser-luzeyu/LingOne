#include "receivefile.h"
#include "ui_receivefile.h"
#include "adbcommand.h"

#include "uishadow.h"

extern AdbCommand* adbc;

ReceiveFile::ReceiveFile(QString dstFilePath, QString textMsg, QStringList cmd, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiveFile)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());//无边框和窗口阴影
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->dstFilePath = dstFilePath;
    this->textMsg = textMsg;
    this->cmd = cmd;
    ui->textEdit->setText(this->textMsg);

    UIShadow* mShadow = new UIShadow();
    mShadow->setShadow(ui->btn_acceptFile);
    mShadow->setShadow(ui->btn_cancel);
    mShadow->setShadow(ui->label);
    mShadow->setBigShadow(ui->label_background);



}

ReceiveFile::~ReceiveFile()
{
    delete ui;
}

void ReceiveFile::on_btn_acceptFile_clicked()
{
    QElapsedTimer t;
    t.start();
    while(t.elapsed()<500);
    //AdbCommand* adbc = new AdbCommand();//调试时无法正常收到文件，正常现象
    adbc->runCommand(this->cmd);
    //qDebug() << dstFilePath;
    QDesktopServices::openUrl(QUrl(dstFilePath, QUrl::TolerantMode));
    this->close();
}

void ReceiveFile::on_btn_cancel_clicked()
{
    this->close();
}

void ReceiveFile::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());
}

void ReceiveFile::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void ReceiveFile::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}
