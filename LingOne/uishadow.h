#ifndef UISHADOW_H
#define UISHADOW_H
#include <QGraphicsDropShadowEffect>

#include <QObject>
#include <QWidget>

class UIShadow : public QObject
{
public:
    UIShadow();
    void setShadow(QWidget*);
    void setBigShadow(QWidget*);
};

#endif // UISHADOW_H
