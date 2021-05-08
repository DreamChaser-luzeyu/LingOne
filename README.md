
# 高级语言程序设计 大作业 实验报告

### 2012138 陆泽宇 

## 一. 作业题目

基于Qt的Android与PC端快速文件传输、文件管理、多屏协作工具。应学校要求，故将实验报告上交于仓库。[Android端地址](https://github.com/DreamChaser-luzeyu/LingOne-Android)

## 二.开发软件

Qt Creator， Android Studio

## 三.课题要求

### 1.面向对象

### 2.图形化用户界面

## 四. 主要流程

### 1.整体流程

定义类AdbCommand，成员方法为：

```cpp
QString runCommand(QStringList);
QString runOtherCommand(QString, QStringList);
QString runOtherCommandModal(QString,QStringList);
```

定义类MyTcp，成员方法为：

```cpp
void connectToHost();
QString getReceiveData();
void writeData(QByteArray);
bool listen();
```

声明信号：

```cpp
signals:
    void recFile(QString path);
    void recHandShake();
    void recIpAddr(QString ipAddr);
    void recText(QString text);
```

### 2.实现方法

通过TCPSocket与手机通信，传输文本

通过调用系统终端执行adb pull与adb push命令来在Android与PC端之间传输文件

通过adb shell am start -n命令来打开手机上的应用程序

通过Genymotion的Scrcpy项目来实现在PC上控制Android设备

## 五.收获

### 1.Qt

掌握了Qt的一些概念，如信号和槽等，熟悉了GUI程序中的常用Widget。

### 2.TCPSocket

通过Qt与Java实现了TCP通信，为日后的网络相关知识打下基础。

### 3.Android

了解了Java语言，掌握了ADB（Android Debug Bridge）的部分命令，了解并实践了Android应用程序从开发到上线的全过程

### 4.软件工程

真正实践了较大型应用程序的开发，了解了软件开发的主要流程，尝试使用了版本控制工具Git
