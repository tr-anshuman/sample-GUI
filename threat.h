#ifndef THREAT_H
#define THREAT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Threat : public QGraphicsItem
{
public:
    Threat(int);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:


private:

};


#endif // THREAT_H
