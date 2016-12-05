#ifndef UAVITEM_H
#define UAVITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class UavItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    UavItem(int, int x[][4]);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public slots:
    void move();
    void target(int, int x[][4]);
//    void on_pushButton_simstart_clicked();
protected:
//    void advance(int phase);

public:
    qreal type;
    double SpeedX, SpeedY;
    qreal damage, battery;
    qreal rem_time;

    double V;

};

#endif // UAVITEM_H
