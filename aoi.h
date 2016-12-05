#ifndef AOI_H
#define AOI_H


#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>

class AOI : public QGraphicsItem
{
public:
    AOI(int);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:


private:

};





#endif // AOI_H
