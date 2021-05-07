#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QFileIconProvider>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QFileIconProvider icon_provider;
    QIcon icoFolder = icon_provider.icon(QFileIconProvider::Folder);


private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_btn_toparentfolder_clicked();
    void on_btn_lstmode_clicked();
    void on_btn_search_clicked();

    void on_btn_exit_search_clicked();

    void on_btn_cd_clicked();

private:
    Ui::Widget *ui;
    void refresh();
    void refreshResult();
};
#endif // WIDGET_H
