#include "guibasket.h"
#include "QPainter"

GUIBasket::GUIBasket(QWidget * parent) : QWidget(parent){

}

void GUIBasket::setPercent(int bluePrecnet, int redPercent){
    this->bluePercent = bluePrecnet;
    this->redPercent = redPercent;
    update();
}

void GUIBasket::paintEvent(QPaintEvent *){
    QPainter painter(this);

    int width = this->width();
    int height = this->height() / 3;

    int blueWidth = (width * bluePercent) / 100;
    int redWidth = (width * redPercent) / 100;

    painter.setBrush(Qt::blue);
    painter.drawRect(0, 0, blueWidth, height);

    painter.setBrush(Qt::red);
    painter.drawRect(blueWidth, 0, redWidth, height);
}
