#include "widget.h"
extern QString filePath;
#include <QApplication>
#include <QTextCodec>

int main(int argc, char* argv[])
{
    //filePath = "D:/Demo.jpg";
    //qDebug() << "argc:" << argc;
    QTextCodec* qtc = QTextCodec::codecForName("UTF-8");
//    for(int i=1; i<argc; i++){
//        filePath += qtc->toUnicode(argv[i]);
//    }

    filePath = qtc->toUnicode(argv[1]);
    //filePath = QString(argv[1]);
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
