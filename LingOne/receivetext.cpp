#include "receivetext.h"
#include "ui_receivetext.h"

ReceiveText::ReceiveText(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiveText)
{
    ui->setupUi(this);
    this->text = text;
    ui->textEdit->setText(text);
}

ReceiveText::~ReceiveText()
{
    delete ui;
}

void ReceiveText::on_btn_openlink_https_clicked()
{
    QStringList link = text.split("https://");
    //qDebug()<<"有几个:";
    //qDebug()<<link.count();
    if(link.count()>1){
        //qDebug()<<"打开链接";
        QDesktopServices::openUrl(QUrl("https://"+link[1].toLatin1()));
        this->hide();
    }
}

void ReceiveText::on_btn_openlink_http_clicked()
{
    QStringList link = text.split("http://");
    if(link.count()>1){
        //qDebug()<<"打开链接";
        QDesktopServices::openUrl(QUrl("http://"+link[1].toLatin1()));
        this->hide();
    }
}

void ReceiveText::on_btn_cancel_clicked()
{
    this->close();
}

void ReceiveText::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());
}

void ReceiveText::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void ReceiveText::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}
