#ifndef FIRSTRUNWIZARD_H
#define FIRSTRUNWIZARD_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class FirstRunWizard;
}

class FirstRunWizard : public QDialog
{
    Q_OBJECT

public:
    explicit FirstRunWizard(QWidget *parent = nullptr);
    ~FirstRunWizard();

private slots:
    void on_btn_save_clicked();

    void on_btn_close_clicked();

    void on_btn_add_clicked();

    void on_btn_remove_clicked();

private:
    Ui::FirstRunWizard *ui;
    QSettings* mConf;
};

#endif // FIRSTRUNWIZARD_H
