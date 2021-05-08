#ifndef ADBCOMMAND_H
#define ADBCOMMAND_H
#include "QString"
#include "QDir"
#include "QProcess"
#include "QObject"


class AdbCommand : public QObject
{
    QString adbDir;
public:
    AdbCommand();
    AdbCommand(QString);

    QString runCommand(QStringList);
    static QString runCommand(QStringList, int);
    QString runOtherCommand(QString, QStringList);
    //QString runCommandS();
};

#endif // ADBCOMMAND_H
