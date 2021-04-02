#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QHostAddress>
#include "firstrunwizard.h"
#include <QKeyEvent>

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

    void on_btn_settings_clicked();

private:
    Ui::MainMenu *ui;
    FirstRunWizard* frw;
    void keyPressEvent(QKeyEvent* event);
};

#endif // MAINMENU_H
