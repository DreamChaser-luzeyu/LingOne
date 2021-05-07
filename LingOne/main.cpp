#include "mainmenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu w;
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    w.show();
    return a.exec();
}
