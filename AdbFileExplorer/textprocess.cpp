#include "textprocess.h"

TextProcess::TextProcess(QObject *parent) : QObject(parent)
{

}

QString TextProcess::qByteArrayToQString(QByteArray array){
    QTextCodec* qtc = QTextCodec::codecForName("UTF-8");
    return qtc->toUnicode(array);
}
