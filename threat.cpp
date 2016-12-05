#include "threat.h"

Threat::Threat(int a)
{
    //random start rotation
    //angle = 45;
    //setRotation(angle);

    int SpeedX = 0;
    int SpeedY = 0;

    //random start position
    int StartX = 0;
    int StartY = 0;

    if( a<4)
    {
        StartX = (qrand() % 500);
        StartY = (qrand() % 320);

    }
    else if( a<7)
    {
        StartX = 500 + (qrand() % 500);
        StartY = (qrand() % 320);

    }
    else if( a<10)
    {
        StartX = (qrand() % 500);
        StartY = 320 + (qrand() % 320);

    }
    else
    {
        StartX = 500 + (qrand() % 500);
        StartY = 320 + (qrand() % 320);

    }

    setPos(mapToParent(StartX,StartY));


}

QRectF Threat::boundingRect() const
{
    return QRect(0,0,20,20);
}

void Threat::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush Brush(Qt::yellow);

    //basic Collision detection


    painter->fillRect(rec,Brush);
    painter->drawEllipse(rec);

}
