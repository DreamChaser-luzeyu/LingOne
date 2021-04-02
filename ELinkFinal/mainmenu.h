#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QHostAddress>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    QWidget *parent;
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    //void setData(QString pcName,QHostAddress ipAddr,QStringList devLst);

    void refreshUI();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
