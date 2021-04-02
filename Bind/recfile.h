#ifndef RECFILE_H
#define RECFILE_H

#include <QDialog>

namespace Ui {
class RecFile;
}

class RecFile : public QDialog
{
    Q_OBJECT

public:
    explicit RecFile(QString url,QStringList cmd,QWidget *parent = nullptr, QString content = "");
    ~RecFile();

private slots:
    void on_btn_acceptFile_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::RecFile *ui;
    QStringList cmd;
    QString url;
};

#endif // RECFILE_H
