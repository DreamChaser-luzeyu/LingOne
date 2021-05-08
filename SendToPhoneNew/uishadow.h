#ifndef UISHADOW_H
#define UISHADOW_H
#include "QGraphicsDropShadowEffect"
#include "widget.h"
#include "ui_widget.h"
#include <QObject>

class UIShadow : public QObject
{
public:
    UIShadow();
    void setShadow(QWidget*);
};

#endif // UISHADOW_H
