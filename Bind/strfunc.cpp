#include "strfunc.h"

StrFunc::StrFunc(QObject *parent) : QObject(parent)
{

}


QStringList StrFunc::splitBySpace(QString str){
    return str.split("\n");
}
