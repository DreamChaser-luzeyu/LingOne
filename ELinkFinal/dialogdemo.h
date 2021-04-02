#ifndef DIALOGDEMO_H
#define DIALOGDEMO_H

#include <QDialog>

namespace Ui {
class DialogDemo;
}

class DialogDemo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDemo(QWidget *parent = nullptr,QString text = "Default");
    ~DialogDemo();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_openlink_https_clicked();

    void on_btn_openlink_http_clicked();

private:
    Ui::DialogDemo *ui;
    QString text;

};

#endif // DIALOGDEMO_H
