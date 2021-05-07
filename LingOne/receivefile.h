#ifndef RECEIVEFILE_H
#define RECEIVEFILE_H

#include <QDialog>
#include <QDesktopServices>
#include <QElapsedTimer>
#include <QMouseEvent>


namespace Ui {
class ReceiveFile;
}

class ReceiveFile : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiveFile(QString path, QString devName, QStringList cmd, QWidget *parent = nullptr);
    ~ReceiveFile();

    bool m_bPressed = true;
    QPoint m_point;
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_btn_acceptFile_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::ReceiveFile *ui;
    QString dstFilePath;
    QString textMsg;
    QStringList cmd;
};

#endif // RECEIVEFILE_H
