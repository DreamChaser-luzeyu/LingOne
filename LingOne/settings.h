#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>
#include <QFile>
#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>
#include <QMouseEvent>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    //无边框移动
    bool m_bPressed = true;
    QPoint m_point;

    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_btn_save_clicked();
    void on_btn_close_clicked();
    void on_btn_add_clicked();
    void on_btn_remove_clicked();

    void on_btn_close_2_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
