#include "widget.h"
extern QString filePath;
#include <QApplication>

int main(int argc, char* argv[])
{
    //filePath = "D:/Demo.jpg";
    filePath = QString(argv[1]);
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
