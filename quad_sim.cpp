#include "quad_sim.h"
#include "ui_quad_sim.h"
#include "uavitem.h"
#include "aoi.h"
#include "threat.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>

int uav_flag[4] = {0,0,0,0};
int aoi[20][4] = {};
int aoi_sorted[20][4] ={};

quad_sim::quad_sim(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::quad_sim)
{
    ui->setupUi(this);
    uav_flag1 = 0;

    //QPixmap pix("C:/Study/Thesis Project/QtProjects/GCS_example/Capture.png");
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QString map_Path("C:/Study/Thesis Project/QtProjects/GCS_example/map1.png");
    QImage map_Image(map_Path);
    scene->setSceneRect(map_Image.rect());
    scene->setBackgroundBrush(map_Image);
    //scene->addPixmap(pix.scaled(1020,680,Qt::KeepAspectRatio));
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    //scene->setSceneRect(-1020,-680,1020,680);
    QPen blackPen(Qt::black);

    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF BottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    scene->addLine(TopLine,blackPen);
    scene->addLine(LeftLine,blackPen);
    scene->addLine(RightLine,blackPen);
    scene->addLine(BottomLine,blackPen);



    QPixmap pix2("C:/Study/Thesis Project/QtProjects/GCS_example/black.png");
    scene2 = new QGraphicsScene(this);
    ui->graphicsView_2->setScene(scene2);
    scene2->addPixmap(pix2.scaled(1000,1000,Qt::KeepAspectRatio));

    QPixmap pixmap("C:/Study/Thesis Project/QtProjects/GCS_example/uav.png");
    ui->uav1_pic->setPixmap(pixmap.scaled(200,200,Qt::KeepAspectRatio));
    ui->uav2_pic->setPixmap(pixmap.scaled(200,200,Qt::KeepAspectRatio));
    ui->uav3_pic->setPixmap(pixmap.scaled(200,200,Qt::KeepAspectRatio));
    ui->uav4_pic->setPixmap(pixmap.scaled(200,200,Qt::KeepAspectRatio));



    qDebug() << "AOIs generated";

    for(int i = 0; i < 16; i++)
    {
        Threat *item1 = new Threat(i);
        scene->addItem(item1);
    }

//    int ItemCount = 5;
//    if (uav_flag1 == 1)
//    {
//        for(int i = 1; i < ItemCount; i++)
//        {
//            UavItem *item = new UavItem(i);
//            scene->addItem(item);


//        }
//    }

//    int s = aoi_list->size();
//    qDebug() << s;


//        for (int i = 0, n = aoi_list->size(); i < n; ++i)
//        {

//        //qDebug() << aoi_list->value(i);
//        }
//    qDebug() << aoi[1][1];
//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), scene,SLOT(advance()));
//    timer->start(100);

    QBrush greenBrush(Qt::green);
    QBrush redBrush(Qt::red);








    //ellipse = scene->addEllipse(10,10,50,50,blackPen,redBrush);
    //ellipse->setFlag(QGraphicsItem::ItemIsMovable);


}

quad_sim::~quad_sim()
{
    delete ui;
}



void quad_sim::on_pushButton_simstart_clicked()
{
//    int** aoi = (int**)malloc(20*sizeof(int*));
//    for (int i=0; i<20; i++) aoi[i] = (int*)malloc(4*sizeof(int));
//    int aoi[20][4] = {};
    generate_aoi(aoi);


//    int** aoi_sorted = (int**)malloc(20*sizeof(int*));
//    for (int i=0; i<20; i++) aoi_sorted[i] = (int*)malloc((4)*sizeof(int));
//    int aoi_sorted[20][4] = {};
    sort(aoi_sorted, aoi);
    qDebug() << aoi_sorted[11][0];
    generate_uav(aoi_sorted);
    qDebug() << aoi_sorted[1][0];
    uav_flag1 = 1;
    qDebug() << uav_flag1;
//    for(int i=0; i<20; i++)
//    {
//        qDebug() << aoi_sorted[i][0] << aoi_sorted[i][1] << aoi_sorted[i][2] << aoi_sorted[i][3];
//    }

//    ui->simstart_l->setText(QString::number(uav_flag[0]));
}

void quad_sim::generate_aoi(int a[][4])
{

    for(int i = 0; i < 20; i++)
    {
 //       QList<AOI *>* aoi_list = new QList<AOI *>();
        AOI *item = new AOI(i);
        scene->addItem(item);
 //       aoi_list->push_back(item);
        int x_dist = item->pos().rx();
        int y_dist = item->pos().ry();
        a[i][0] = i;
        a[i][1] = x_dist;
        a[i][2] = y_dist;
        a[i][3] = sqrt(pow(a[i][1],2) + pow(a[i][2],2));

     }
}

void quad_sim::generate_uav(int x[][4])
{
//    int ItemCount = 4;
//    for(int i = 0; i < ItemCount; i++)
//    {
//        UavItem *item = new UavItem(i,x);
//        scene->addItem(item);

// }
    QBrush blueBrush(Qt::blue);
    QBrush cyanBrush(Qt::cyan);
    QBrush yellowBrush(Qt::yellow);
    QBrush magentaBrush(Qt::magenta);
    uav0 = scene->addRect(0,0,7,7,blackPen,blueBrush);
    uav1 = scene->addRect(0,7,7,7,blackPen,cyanBrush);
    uav2 = scene->addRect(7,0,7,7,blackPen,yellowBrush);
    uav3 = scene->addRect(7,7,7,7,blackPen,magentaBrush);

}

void quad_sim::sort(int aoi_sorted[][4],int aoi[][4])
{
            int aoi_dist[20];

            for (int i=0; i<20; i++)
            {
                aoi_dist[i] = aoi[i][3];
               // qDebug() << aoi_dist[i];
            }

            int aoi_dist_sort[20];
            int max = aoi_dist[0];
            int index;
            for (int i=0; i<20; i++)
                {
                  for (int j=0; j<20; j++)
                    {
                        if (aoi_dist[j]>max)
                        {
                            max = aoi_dist[j];
                            index = j;
                        }
                    }
                    aoi_dist[index] = -1;
                    aoi_dist_sort[i] = index;
                    max = aoi_dist[i];
                }

                for (int i=0; i<20; i++)
                {
                    for (int j=0; j<4; j++)
                    {
                        aoi_sorted[i][j] = aoi[aoi_dist_sort[19-i]][j];
                    }
                }

}

void quad_sim::on_uav1_engage_clicked()
{/*
    if(aoi0==1)
    {
        QPixmap pix2("C:/Study/Thesis Project/QtProjects/GCS_example/black.png");
        scene2->addPixmap(pix2.scaled(1000,1000,Qt::KeepAspectRatio));
    }

    el*/


}
