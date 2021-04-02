#include "widget.h"
#include "mainmenu.h"
//#include "globalapplication.h"
#include <QApplication>
#include <QSplashScreen>
//Widget w;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //GlobalApplication a(argc, argv);
    //程序加载界面
    QPixmap splScreenPix(":/DreamLink_icon.png");
    QSplashScreen splScr(splScreenPix);
    splScr.show();

    Widget w;
    //MainMenu m(&w);
    //w.show();
    //m.show();
    splScr.finish(&w);
    return a.exec();
}
