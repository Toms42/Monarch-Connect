#include "xyvis.h"
#include <QPainter>

XYvis::XYvis(QWidget *parent) : QWidget(parent)
{
    x = 0;
    y = 0;
    setAutoFillBackground(true);
}

void XYvis::paintEvent(QPaintEvent * /* event */)
{
    QRect box(0,0,100,100);
    QLine horiz(0,50,100,50);
    QLine vertical(50,0,50,100);
    QPoint target(x*50+50,y*50+50);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QColor(0,100,100,255));
    painter.drawRect(box);
    painter.drawLine(horiz);
    painter.drawLine(vertical);
    painter.setPen(QColor(0,240,240,255));
    painter.drawEllipse(target,10,10);

}

void XYvis::setCoords(float x, float y)
{
    XYvis::x = x;
    XYvis::y = y;
    update();
}

QSize XYvis::sizeHint() const
{
    return QSize(100,100);
}
QSize XYvis::minimumSizeHint() const
{
    return QSize(100, 100);
}
