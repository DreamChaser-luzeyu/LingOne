#include "adbcommand.h"
#include "QDebug"


extern QString devS;

AdbCommand::AdbCommand(){
    this->adbDir = QDir::currentPath();
    qDebug()<<adbDir+"/adb.exe";
}


AdbCommand::AdbCommand(QString str)
{
    this->adbDir = str;
    qDebug()<<adbDir+"/adb.exe";
}

QString AdbCommand::runCommand(QStringList args){
    //QProcess *adbProcess = new QProcess();
    QProcess adbProcess;
    adbProcess.start(adbDir+"/adb.exe", args);
    adbProcess.waitForStarted();
    adbProcess.waitForFinished(-1);
    return QString::fromLocal8Bit((adbProcess.readAllStandardOutput()));
}
/*
QString AdbCommand::runCommandS(){
    //QProcess *adbProcess = new QProcess();
    QProcess adbProcess;
    qDebug()<<"AdbCommand:"<<devS;
    adbProcess.start(adbDir+"/adb.exe devices");
    qDebug()<<adbDir+"/adb.exe -s " + devS + " reboot";
    adbProcess.waitForStarted();
    adbProcess.waitForFinished();
    return QString::fromLocal8Bit((adbProcess.readAllStandardOutput()));
}*/



QString AdbCommand::runOtherCommand(QString cmd, QStringList args){
    //QProcess *adbProcess = new QProcess();
    QProcess adbProcess;
    adbProcess.startDetached(adbDir+"/"+cmd, args);
    //adbProcess.waitForStarted();
    //adbProcess.waitForFinished();
    //return QString::fromLocal8Bit((adbProcess.readAllStandardOutput()));
    return "done";
}
