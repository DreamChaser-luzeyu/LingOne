#ifndef ADBCOMMAND_H
#define ADBCOMMAND_H
#include "QString"
#include "QDir"
#include "QProcess"
#include "QObject"
#include <QTextCodec>


class AdbCommand : public QObject
{
    QString adbDir;
public:
    AdbCommand();
    AdbCommand(QString);

    QString runCommand(QStringList);
    QString runOtherCommand(QString, QStringList);
    QString runOtherCommandModal(QString,QStringList);

};

#endif // ADBCOMMAND_H
