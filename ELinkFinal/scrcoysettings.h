#ifndef SCRCOYSETTINGS_H
#define SCRCOYSETTINGS_H

#include <QWidget>

namespace Ui {
class ScrcoySettings;
}

class ScrcoySettings : public QWidget
{
    Q_OBJECT

public:
    explicit ScrcoySettings(QWidget *parent = nullptr);
    ~ScrcoySettings();

private:
    Ui::ScrcoySettings *ui;
};

#endif // SCRCOYSETTINGS_H
