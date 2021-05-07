#include "widget.h"

#include <QApplication>
#include <QTextCodec>
extern QString devS;
extern QString currentDir;
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QTextCodec* qtc = QTextCodec::codecForName("UTF-8");
    devS = qtc->toUnicode(argv[1]);
    currentDir = qtc->toUnicode(argv[2]);
    qDebug() << "devS:" << devS;
    qDebug() << "currentDir:" << currentDir;


    Widget w;
    w.show();
    return a.exec();
}
