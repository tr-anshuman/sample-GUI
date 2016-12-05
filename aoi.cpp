#include "aoi.h"

AOI::AOI(int a)
{


    int aoi_id = a;
    int SpeedY = 0;

    //random start position
    int StartX = 0;
    int StartY = 0;

    if( a<5)
    {
        StartX = (qrand() % 500);
        StartY = (qrand() % 320);

    }
    else if( a<9)
    {
        StartX = 500 + (qrand() % 500);
        StartY = (qrand() % 320);

    }
    else if( a<13)
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

QRectF AOI::boundingRect() const
{
    return QRect(0,0,10,10);
}

void AOI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush Brush(Qt::green);

    //basic Collision detection


    painter->fillRect(rec,Brush);
    painter->drawRect(rec);


}
