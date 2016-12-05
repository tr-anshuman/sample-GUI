#ifndef QUAD_SIM_H
#define QUAD_SIM_H



#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsItem>
#include <QGraphicsScene>


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
    void on_pushButton_simstop_clicked();
    void on_pushButton_simpause_clicked();
    void generate_uav(int x[][4]);
    void generate_aoi(int a[][4]);
    void sort(int aoi_sorted[][4],int aoi[][4]);
    void movement0();
    void movement1();
    void movement2();
    void movement3();
    void target(int, int x[][4]);
    void mousePressEvent(QMouseEvent*);


private slots:
    void on_uav1_engage_clicked();

    void on_uav1_confirm_clicked();

    void on_uav1_deny_clicked();

    void on_uav1_retire_clicked();

    void on_uav2_confirm_clicked();

    void on_uav2_engage_clicked();

    void on_uav2_deny_clicked();

    void on_uav2_retire_clicked();

    void on_uav3_confirm_clicked();

    void on_uav3_engage_clicked();

    void on_uav3_deny_clicked();

    void on_uav3_retire_clicked();

    void on_uav4_confirm_clicked();

    void on_uav4_engage_clicked();

    void on_uav4_retire_clicked();

    void on_uav4_deny_clicked();


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
