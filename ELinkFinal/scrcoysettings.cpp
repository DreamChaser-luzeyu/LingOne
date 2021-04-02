#include "scrcoysettings.h"
#include "ui_scrcoysettings.h"

ScrcoySettings::ScrcoySettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScrcoySettings)
{
    ui->setupUi(this);
}

ScrcoySettings::~ScrcoySettings()
{
    delete ui;
}
