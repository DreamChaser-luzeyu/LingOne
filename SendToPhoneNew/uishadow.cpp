#include "uishadow.h"

UIShadow::UIShadow()
{

}

void UIShadow::setShadow(QWidget *widget){
    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect();
    //渲染的像素点
    shadow->setBlurRadius(30);
    //渲染的颜色
    shadow->setColor(Qt::gray);
    //渲染相对于组件的偏移
    shadow->setOffset(0);
    widget->setGraphicsEffect(shadow);
}
