#ifndef RECEIVETEXT_H
#define RECEIVETEXT_H

#include <QDialog>
#include <QDesktopServices>
#include <QMouseEvent>

namespace Ui {
class ReceiveText;
}

class ReceiveText : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiveText(QString text, QWidget *parent = nullptr);
    ~ReceiveText();

    bool m_bPressed = true;
    QPoint m_point;
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_btn_openlink_https_clicked();

    void on_btn_openlink_http_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::ReceiveText *ui;
    QString text;
};

#endif // RECEIVETEXT_H
