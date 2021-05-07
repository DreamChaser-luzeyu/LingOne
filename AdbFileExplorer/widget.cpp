#include "widget.h"
#include "ui_widget.h"
#include "adbcommand.h"

AdbCommand* adbc;
QString devS;
QStringList fileLst;
QString currentDir = "/sdcard/";
QString currentPCDir;
bool searchMode = false;



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //adbc = new AdbCommand("D:/PortableSoftware/platform-tools");
    adbc = new AdbCommand();
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setGridSize(QSize(75, 75));


    currentPCDir = QDir::currentPath();


    QStringList commands;
    commands << "-s" << devS;
    commands << "shell" << "ls -F " + currentDir;
    fileLst.clear();
    fileLst = adbc->runCommand(commands).split("\r\n");

    refresh();


}

void Widget::refresh(){
    ui->lineEdit_path->setText(currentDir);
    qDebug()<<currentDir;
    ui->listWidget->clear();
    for(int i=0; i<fileLst.size(); i++){
        QString itemName = fileLst[i];
        QListWidgetItem* qlwi = new QListWidgetItem(itemName);
        if(itemName.split("/").size() > 1){
            //qlwi -> setIcon(QIcon(":/folder.png"));
            qlwi -> setIcon(icoFolder);
        }
        else if(itemName.split(".").size() > 1){
            QString type = itemName.split(".")[itemName.split(".").size()-1];
            if(type == "pdf"){
                qlwi -> setIcon(QIcon(":/pdf.png"));
            }
            else if(type == "doc" || type == "docx" || type == "ppt" || type == "pptx" || type == "xls" || type == "xlsx"){
                qlwi -> setIcon(QIcon(":/office.png"));
            }
            else if(type == "jpg" || type == "png" || type == "bmp"){
                qlwi -> setIcon(QIcon(":/picture.png"));
            }
            else{
                qlwi -> setIcon(QIcon(":/other.png"));
            }
        }
        else{
            qlwi -> setIcon(QIcon(":/other.png"));
        }
        qlwi->setData(Qt::UserRole, QVariant(currentDir + fileLst[i]));
        ui->listWidget->addItem(qlwi);
    }
}

void Widget::refreshResult(){

    qDebug()<<currentDir;
    ui->listWidget->clear();
    for(int i=0; i<fileLst.size(); i++){
        QString itemName;
        if(fileLst[i].split("/").size()>1){
            itemName = fileLst[i].split("/")[fileLst[i].split("/").size()-1];
        }
        QListWidgetItem* qlwi = new QListWidgetItem(itemName);
        if(itemName.split("/").size() > 1){
            //qlwi -> setIcon(QIcon(":/folder.png"));
            qlwi -> setIcon(icoFolder);
        }
        else if(itemName.split(".").size() > 1){
            QString type = itemName.split(".")[itemName.split(".").size()-1];
            if(type == "pdf"){
                qlwi -> setIcon(QIcon(":/pdf.png"));
            }
            else if(type == "doc" || type == "docx" || type == "ppt" || type == "pptx" || type == "xls" || type == "xlsx"){
                qlwi -> setIcon(QIcon(":/office.png"));
            }
            else if(type == "jpg" || type == "png" || type == "bmp"){
                qlwi -> setIcon(QIcon(":/picture.png"));
            }
            else{
                qlwi -> setIcon(QIcon(":/other.png"));
            }
        }
        else{
            qlwi -> setIcon(QIcon(":/other.png"));
        }

        qlwi->setData(Qt::UserRole, QVariant(fileLst[i]));
        ui->listWidget->addItem(qlwi);
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(item->text().split("/").size() >= 2){
        currentDir += item->text();
        QStringList commands;
        commands << "-s" << devS;
        commands << "shell" << "ls -F " + currentDir;
        fileLst.clear();
        fileLst = adbc->runCommand(commands).split("\r\n");
        qDebug() << currentDir;
        refresh();
    }
    else{
        qDebug() << item->data(Qt::UserRole).toString();
        QString filePath = item->data(Qt::UserRole).toString();
        QString fileName = filePath.split("/")[filePath.split("/").size()-1];
        QStringList args;
        args << "-s"<<devS<<"pull"<<""""+filePath+""""<<""""+currentPCDir+"/FileReceive/"+fileName+"""";
        adbc->runCommand(args);
        QDesktopServices::openUrl(QUrl("file:"+currentPCDir+"/FileReceive", QUrl::TolerantMode));
    }

}

void Widget::on_btn_toparentfolder_clicked()
{
    currentDir += "../";
    QStringList commands;
    commands << "-s" << devS;
    commands << "shell" << "ls -F " + currentDir;
    fileLst.clear();
    fileLst = adbc->runCommand(commands).split("\r\n");
    refresh();
}

void Widget::on_btn_lstmode_clicked()
{
    ui->listWidget->setViewMode(QListView::ListMode);
}

void Widget::on_btn_search_clicked()
{
    if(ui->lineEdit_filename->text() == ""){
        QMessageBox::information(this, "Info", "请输入文件名");
    }
    else{
        ui->btn_exit_search->setEnabled(true);
        ui->btn_cd->setEnabled(false);
        searchMode = true;
        QStringList commands;
        commands << "-s" << devS;
        commands << "shell" << "find " + currentDir + " -maxdepth 7 " + " -name " + "'" + ui->lineEdit_filename->text() + "'";
        fileLst.clear();
        fileLst = adbc->runCommand(commands).split("\r\n");
        refreshResult();
    }
}

void Widget::on_btn_exit_search_clicked()
{
    ui->btn_cd->setEnabled(true);
    searchMode = false;
    ui->btn_exit_search->setEnabled(false);
    QStringList commands;
    commands << "-s" << devS;
    commands << "shell" << "ls -F " + currentDir;
    fileLst.clear();
    fileLst = adbc->runCommand(commands).split("\r\n");
    refresh();
}

void Widget::on_btn_cd_clicked()
{
    currentDir = ui->lineEdit_path->text();
    QStringList commands;
    commands << "-s" << devS;
    commands << "shell" << "ls -F " + currentDir;
    fileLst.clear();
    fileLst = adbc->runCommand(commands).split("\r\n");

    refresh();
}
