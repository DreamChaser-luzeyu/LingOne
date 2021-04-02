#ifndef ADBCOMMAND_H
#define ADBCOMMAND_H
#include "QString"
#include "QDir"
#include "QProcess"

//调试时不能执行程序所在路径下的adb.exe，我也不知道为啥

class AdbCommand
{
    QString adbDir;
public:
    AdbCommand();
    AdbCommand(QString);

    QString runCommand(QStringList);
    static QString runCommand(QStringList, int);
    QString runOtherCommand(QString, QStringList);
};

#endif // ADBCOMMAND_H
