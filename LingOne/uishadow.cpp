#include "uishadow.h"

UIShadow::UIShadow()
{

}

void UIShadow::setShadow(QWidget* widget){
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
    //渲染的像素点
    shadow->setBlurRadius(5);
    //渲染的颜色
    shadow->setColor(Qt::gray);
    //渲染相对于组件的偏移
    shadow->setOffset(-0.01);
    widget->setGraphicsEffect(shadow);
}

void UIShadow::setBigShadow(QWidget* widget){
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
    //渲染的像素点
    shadow->setBlurRadius(20);
    //渲染的颜色
    shadow->setColor(Qt::gray);
    //渲染相对于组件的偏移
    shadow->setOffset(0);
    widget->setGraphicsEffect(shadow);
}
