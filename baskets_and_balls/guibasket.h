#ifndef GUIBASKET_H
#define GUIBASKET_H
#include "QWidget"

class GUIBasket : public QWidget
{
private:
    int bluePercent;
    int redPercent;
public:
    GUIBasket(QWidget * parent = nullptr);

    void setPercent(int bluePercent, int redPercent);

    void paintEvent(QPaintEvent * event);
};

#endif // GUIBASKET_H
