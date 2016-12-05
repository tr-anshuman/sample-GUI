#ifndef QUAD_SIM_H
#define QUAD_SIM_H



#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsPixmapItem>
#include <QPixmap>


namespace Ui {
class quad_sim;
}

class quad_sim : public QWidget
{
    Q_OBJECT

public:
    explicit quad_sim(QWidget *parent = 0);
    ~quad_sim();


public slots:

    void on_pushButton_simstart_clicked();
    void generate_uav(int x[][4]);
    void generate_aoi(int a[][4]);
    void sort(int aoi_sorted[][4],int aoi[][4]);

private slots:
    void on_uav1_engage_clicked();

private:
    Ui::quad_sim *ui;
    QGraphicsScene *scene;
    QGraphicsScene *scene2;
    QTimer *timer;


    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *uav0;
    QGraphicsRectItem *uav1;
    QGraphicsRectItem *uav2;
    QGraphicsRectItem *uav3;

    qreal uav_flag1;


};

#endif // QUAD_SIM_H
