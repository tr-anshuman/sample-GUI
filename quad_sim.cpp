#include "quad_sim.h"
#include "ui_quad_sim.h"
#include "aoi.h"
#include "threat.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsTransform>
#include <QDebug>
 #include <QMouseEvent>

int uav_flag[4] = {0,0,0,0};
int aoi[20][4] = {};
int aoi_sorted[20][4] ={};
int aoi_sorted1[20][4] ={};

double PI =3.14;

int t0 = 1, t1 = 1,t2 = 1,t3 = 1;
int move0 = 1, move1 = 1, move2 = 1,move3 = 1;
int replan_click = 0;
double alt_x0 =0, alt_y0 =0, alt_x1 =0, alt_y1 =0, alt_x2 =0, alt_y2 =0, alt_x3 =0, alt_y3 =0;
double altp_x0 =0, altp_y0 =0,altp_x1 =0, altp_y1 =0,altp_x2 =0, altp_y2 =0,altp_x3 =0, altp_y3 =0;
double theta_alt0 =0,theta_alt1 =0,theta_alt2 =0,theta_alt3 =0;
int tar[20][4]={};
double targets0[5][8] = {};
double targets1[5][8] = {};
double targets2[5][8] = {};
double targets3[5][8] = {};

double event_times0[20][4] ={};
double event_times1[20][4] ={};
double event_times2[20][4] ={};
double event_times3[20][4] ={};

double operator_score[20][2] ={};

double simulation_time = 0;
double uav0_time = 0,uav1_time = 0,uav2_time = 0,uav3_time = 0;
double uav0_batt =100, uav1_batt =100, uav2_batt =100, uav3_batt =100;
double uav0_dam = 0, uav1_dam = 0, uav2_dam = 0, uav3_dam = 0;

quad_sim::quad_sim(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::quad_sim)
{
    ui->setupUi(this);
    uav_flag1 = 0;


    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QString map_Path("C:/Study/Thesis Project/QtProjects/GCS_example/map1.png");
    QImage map_Image(map_Path);
    scene->setSceneRect(map_Image.rect());
    scene->setBackgroundBrush(map_Image);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);


    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF BottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    QPen blackPen(Qt::black);

    scene->addLine(TopLine,blackPen);
    scene->addLine(LeftLine,blackPen);
    scene->addLine(RightLine,blackPen);
    scene->addLine(BottomLine,blackPen);



    //QPixmap pix2("C:/Study/Thesis Project/QtProjects/GCS_example/black.png");
    scene2 = new QGraphicsScene(this);
    ui->graphicsView_2->setScene(scene2);
//    scene2->addPixmap(pix2.scaled(1000,1000,Qt::KeepAspectRatio));

    QString feed_Path("C:/Study/Thesis Project/QtProjects/GCS_example/black.png");
    QImage feed_Image(feed_Path);
    scene2->setSceneRect(feed_Image.rect());
    scene2->setBackgroundBrush(feed_Image);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);

    QPixmap pixmap("C:/Study/Thesis Project/QtProjects/GCS_example/uav.png");
    ui->uav1_pic->setPixmap(pixmap.scaled(200,200,Qt::KeepAspectRatio));
    ui->uav2_pic->setPixmap(pixmap.scaled(200,200,Qt::KeepAspectRatio));
    ui->uav3_pic->setPixmap(pixmap.scaled(200,200,Qt::KeepAspectRatio));
    ui->uav4_pic->setPixmap(pixmap.scaled(200,200,Qt::KeepAspectRatio));


    for(int i = 0; i < 16; i++)
    {
        Threat *item1 = new Threat(i);
        scene->addItem(item1);
    }


}

quad_sim::~quad_sim()
{
    delete ui;
}


void quad_sim::on_pushButton_simstart_clicked()
{
    generate_aoi(aoi);
    sort(aoi_sorted, aoi);
    generate_uav(aoi_sorted);
    uav_flag1 = 1;
    qDebug() << uav_flag1;

    ui->uav0->setStyleSheet("QLabel { background-color : yellow}");
    ui->uav1->setStyleSheet("QLabel { background-color : magenta}");
    ui->uav2->setStyleSheet("QLabel { background-color : cyan}");
    ui->uav3->setStyleSheet("QLabel { background-color : blue}");



    QTimer *timer3;
    timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this,SLOT(movement3()));
    timer3->start(100);

    QTimer *timer0;
    timer0 = new QTimer(this);
    connect(timer0, SIGNAL(timeout()), this,SLOT(movement0()));
    timer0->start(100);

    QTimer *timer1;
    timer1= new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this,SLOT(movement1()));
    timer1->start(100);

    QTimer *timer2;
    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this,SLOT(movement2()));
    timer2->start(100);



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

    QBrush blueBrush(Qt::blue);
    QBrush cyanBrush(Qt::cyan);
    QBrush magentaBrush(Qt::magenta);
    QBrush yellowBrush(Qt::yellow);
    QPen blackPen(Qt::black);


    uav0 = scene->addRect(0,0,7,7,blackPen,yellowBrush);
    target(0,x);
    uav1 = scene->addRect(0,7,7,7,blackPen,magentaBrush);
    target(1,x);
    uav2 = scene->addRect(7,0,7,7,blackPen,cyanBrush);
    target(2,x);
    uav3 = scene->addRect(7,7,7,7,blackPen,blueBrush);
    target(3,x);
}

void quad_sim::sort(int aoi_sorted[][4],int aoi[][4])
{
            int aoi_dist[20];

            for (int i=0; i<20; i++)
            {
                aoi_dist[i] = aoi[i][3];

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
                        aoi_sorted1[i][j] = aoi[aoi_dist_sort[19-i]][j];
                    }
                    qDebug() << aoi_sorted[i][0] << aoi_sorted[i][1] << aoi_sorted[i][2] << aoi_sorted[i][3];
                }

}



void quad_sim::target(int a, int x[][4])
{
    if( a==0)
    {

        double tarX = 0, tarY = 0;
        for(int i=0;i<5;i++)
        {
          for(int j=0;j<4;j++)
          {
            targets0[i][j] = x[4*i][j];

          }
          targets0[i][4] = targets0[i][1] - tarX;
          targets0[i][5] = targets0[i][2] - tarY;
          targets0[i][6]= abs(targets0[i][5])/abs(targets0[i][4]);
          if(targets0[i][4]>0)
          {
              if(targets0[i][5]>=0)
              {
                targets0[i][7] = atan(targets0[i][6]);
              }
              else
              {
                targets0[i][7] = -atan(targets0[i][6]);
              }
          }

          else if(targets0[i][4]<0)
          {
              if(targets0[i][5]>=0)
              {
                targets0[i][7] = PI - atan(targets0[i][6]);
              }
              else
              {
                targets0[i][7] = PI + atan(targets0[i][6]);
              }

          }


          else
          {
            if(targets0[i][5]>0)
            {
              targets0[i][7] = PI/2;
            }
            else if(targets0[i][5]<0)
            {
              targets0[i][7] = -PI/2;
            }
            else
            {
               targets0[i][7] = 0;
            }
          }

          tarX = targets0[i][1];
          tarY = targets0[i][2];

         // qDebug() << targets0[i][0] << targets0[i][1] << targets0[i][2] << targets0[i][3] << targets0[i][4] << targets0[i][5] << targets0[i][6] << targets0[i][7];
          }

    }

    else if(a==1)
    {

        double tarX = 0, tarY = 7;
        for(int i=0;i<5;i++)
        {
          for(int j=0;j<4;j++)
          {
            targets1[i][j] = x[(4*i)+1][j];

          }
          targets1[i][4] = targets1[i][1] - tarX;
          targets1[i][5] = targets1[i][2] - tarY;
          targets1[i][6]= abs(targets1[i][5])/abs(targets1[i][4]);
          if(targets1[i][4]>0)
          {
              if(targets1[i][5]>=0)
              {
                targets1[i][7] = atan(targets1[i][6]);
              }
              else
              {
                targets1[i][7] = -atan(targets1[i][6]);
              }
          }

          else if(targets1[i][4]<0)
          {
              if(targets1[i][5]>=0)
              {
                targets1[i][7] = PI - atan(targets1[i][6]);
              }
              else
              {
                targets1[i][7] = PI + atan(targets1[i][6]);
              }

          }


          else
          {
            if(targets1[i][5]>0)
            {
              targets1[i][7] = PI/2;
            }
            else if(targets1[i][5]<0)
            {
              targets1[i][7] = -PI/2;
            }
            else
            {
               targets1[i][7] = 0;
            }
          }

          tarX = targets1[i][1];
          tarY = targets1[i][2];

        qDebug() << targets1[i][0] << targets1[i][1] << targets1[i][2] << targets1[i][3] << targets1[i][4] << targets1[i][5] << targets1[i][6] << targets1[i][7];
          }
    }
    else if(a==2)
    {

        double tarX = 7, tarY = 0;
        for(int i=0;i<5;i++)
        {
          for(int j=0;j<4;j++)
          {
            targets2[i][j] = x[(4*i)+2][j];
          }
          targets2[i][4] = targets2[i][1] - tarX;
          targets2[i][5] = targets2[i][2] - tarY;
          targets2[i][6]= abs(targets2[i][5])/abs(targets2[i][4]);
          if(targets2[i][4]>0)
          {
              if(targets2[i][5]>=0)
              {
                targets2[i][7] = atan(targets2[i][6]);
              }
              else
              {
                targets2[i][7] = -atan(targets2[i][6]);
              }
          }

          else if(targets2[i][4]<0)
          {
              if(targets2[i][5]>=0)
              {
                targets2[i][7] = PI - atan(targets2[i][6]);
              }
              else
              {
                targets2[i][7] = PI + atan(targets2[i][6]);
              }

          }


          else
          {
            if(targets2[i][5]>0)
            {
              targets2[i][7] = PI/2;
            }
            else if(targets2[i][5]<0)
            {
              targets2[i][7] = -PI/2;
            }
            else
            {
               targets2[i][7] = 0;
            }
          }

          tarX = targets2[i][1];
          tarY = targets2[i][2];

         qDebug() << targets2[i][0] << targets2[i][1] << targets2[i][2] << targets2[i][3] << targets2[i][4] << targets2[i][5] << targets2[i][6] << targets2[i][7];
          }
    }
    else
    {

        double tarX = 7, tarY = 7;
        for(int i=0;i<5;i++)
        {
          for(int j=0;j<4;j++)
          {
            targets3[i][j] = x[(4*i)+3][j];
          }
          targets3[i][4] = targets3[i][1] - tarX;
          targets3[i][5] = targets3[i][2] - tarY;
          targets3[i][6]= abs(targets3[i][5])/abs(targets3[i][4]);
          if(targets3[i][4]>0)
          {
              if(targets3[i][5]>=0)
              {
                targets3[i][7] = atan(targets3[i][6]);
              }
              else
              {
                targets3[i][7] = -atan(targets3[i][6]);
              }
          }

          else if(targets3[i][4]<0)
          {
              if(targets3[i][5]>=0)
              {
                targets3[i][7] = PI - atan(targets3[i][6]);
              }
              else
              {
                targets3[i][7] = PI + atan(targets3[i][6]);
              }

          }


          else
          {
            if(targets3[i][5]>0)
            {
              targets3[i][7] = PI/2;
            }
            else if(targets3[i][5]<0)
            {
              targets3[i][7] = -PI/2;
            }
            else
            {
               targets3[i][7] = 0;
            }
          }

          tarX = targets3[i][1];
          tarY = targets3[i][2];

          qDebug() << targets3[i][0] << targets3[i][1] << targets3[i][2] << targets3[i][3] << targets3[i][4] << targets3[i][5] << targets3[i][6] << targets3[i][7];
          }

    }

}

void quad_sim::movement0()
{
    simulation_time = simulation_time +(0.1/3);
    ui->progressBar->setValue(simulation_time);
    ui->uav0_time->setValue(uav0_time);
    ui->uav0_time1->setValue(uav0_time);
    uav0_batt = uav0_batt - (.1/6);
    ui->uav0_batt->setValue(uav0_batt);
    ui->uav0_dam->setValue(uav0_dam);
    double tar_x0 = targets0[t0 - 1][1];
    double tar_y0 = targets0[t0 - 1][2];
    if(move0==0)
         {

                 double curr_x0 =uav0->pos().rx();
                 double curr_y0 =uav0->pos().ry();
                 ui->uav0_stat->setText("Idle");
                 ui->uav0_stat->setStyleSheet("QLabel { background-color : red}");


                 uav0->setPos(curr_x0+0,curr_y0+0);
                 uav0_time = 0;


           }
         else
         {
             ui->uav0_stat->setText("Busy");
             ui->uav0_stat->setStyleSheet("QLabel { background-color : green}");
             if(abs(alt_x0)>0 || abs(alt_y0)>0)
             {
                 if(alt_x0==0)
                 {
                     if(alt_y0>0)
                     {
                         theta_alt0 = PI/2;
                     }
                     else
                     {
                         theta_alt0 = -PI/2;
                     }
                 }
                 else if(alt_y0==0)
                 {
                     if(alt_x0>0)
                     {
                         theta_alt0 = 0;
                     }
                     else
                     {
                         theta_alt0 = PI;
                     }
                 }
                 else
                 {
                     if(alt_x0>0)
                     {
                         if(alt_y0>0)
                         {
                             theta_alt0 = atan(abs(alt_y0/alt_x0));
                             qDebug()<< 1;
                         }
                         else
                         {
                             theta_alt0 = -atan(abs(alt_y0/alt_x0));
                         }
                     }
                     else
                     {
                         if(alt_y0>0)
                         {
                             theta_alt0 = PI - atan(abs(alt_y0/alt_x0));
                         }
                         else
                         {
                             theta_alt0 = PI + atan(abs(alt_y0/alt_x0));
                         }
                     }


                 }

                 double Speed_alt_X0 = cos(theta_alt0);
                 double Speed_alt_Y0 = sin(theta_alt0);

                 qDebug()<< alt_y0<< alt_x0<< theta_alt0;
                 double curr_x0 =uav0->pos().rx();
                 double curr_y0 =uav0->pos().ry();


                 if(curr_x0<=altp_x0 || curr_y0<=altp_y0)
                 {
                   uav0->setPos(curr_x0+Speed_alt_X0,curr_y0+Speed_alt_Y0);
                 }
                else
                 {
                     targets0[t0 - 1][4] = targets0[t0 - 1][1] - curr_x0;
                     targets0[t0 - 1][5] = targets0[t0 - 1][2] - curr_y0;
                     targets0[t0 - 1][6]= abs(targets0[t0 - 1][5])/abs(targets0[t0 - 1][4]);
                     if(targets0[t0 - 1][4]>0)
                     {
                         if(targets0[t0 - 1][5]>=0)
                         {
                           targets0[t0 - 1][7] = atan(targets0[t0 - 1][6]);
                         }
                         else
                         {
                           targets0[t0 - 1][7] = -atan(targets0[t0 - 1][6]);
                         }
                     }

                     else if(targets0[t0 - 1][4]<0)
                     {
                         if(targets0[t0 - 1][5]>=0)
                         {
                           targets0[t0 - 1][7] = PI - atan(targets0[t0 - 1][6]);
                         }
                         else
                         {
                           targets0[t0 - 1][7] = PI + atan(targets0[t0 - 1][6]);
                         }

                     }


                     else
                     {
                       if(targets0[t0 - 1][5]>0)
                       {
                         targets0[t0 - 1][7] = PI/2;
                       }
                       else if(targets0[t0 - 1][5]<0)
                       {
                         targets0[t0 - 1][7] = -PI/2;
                       }
                       else
                       {
                          targets0[t0 - 1][7] = 0;
                       }
                     }


                    alt_x0 =0;
                    alt_y0 =0;
                    altp_x0 =0;
                    altp_y0 =0;
                 }

             }
             else
             {
             double curr_x0 =uav0->pos().rx();
             double curr_y0 =uav0->pos().ry();

             double curr_d0 =sqrt(pow(curr_x0,2) + pow(curr_y0,2));
             if((curr_d0 >= targets0[t0 - 1][3]))
             {
               uav0->setPos(curr_x0+0,curr_y0+0);
               move0 = 0;
               t0 = t0 + 1;
             }
             else
             {
                 double SpeedX0 = cos(targets0[t0 - 1][7]);
                 double SpeedY0 = sin(targets0[t0 - 1][7]);

                 uav0->setPos(curr_x0+SpeedX0,curr_y0+SpeedY0);
                 if(t0==1)
                 {
                     uav0_time = 100-(((targets0[t0 - 1][3] - curr_d0)/(targets0[t0 - 1][3]))*100);
                 }
                 else
                 {
                     double rem_dist0 = sqrt(pow(targets0[t0 - 1][1] - curr_x0,2) + pow(targets0[t0 - 1][2] - curr_y0,2));
                     double tot_dist0 = sqrt(pow(targets0[t0 - 1][1] - targets0[t0 - 2][1],2) + pow(targets0[t0 - 1][2] - targets0[t0 - 2][2],2));
                     uav0_time = 100-((rem_dist0/tot_dist0)*100);
                 }

             }

             }
           }

}
void quad_sim::movement1()
{

    ui->uav1_time->setValue(uav1_time);
    ui->uav1_time1->setValue(uav1_time);
    uav1_batt = uav1_batt - (.1/6);
    ui->uav1_batt->setValue(uav1_batt);
    ui->uav1_dam->setValue(uav1_dam);

         if(move1==0)
         {
             ui->uav1_stat->setText("Idle");
             ui->uav1_stat->setStyleSheet("QLabel { background-color : red}");
                 double curr_x1 =uav1->pos().rx();
                 double curr_y1 =uav1->pos().ry();
                 uav1_time =0;

                 uav1->setPos(curr_x1+0,curr_y1+0);


           }
         else
         {
             ui->uav1_stat->setText("Busy");
             ui->uav1_stat->setStyleSheet("QLabel { background-color : green}");
             if(abs(alt_x1)>0 || abs(alt_y1)>0)
             {
                 if(alt_x1==0)
                 {
                     if(alt_y1>0)
                     {
                         theta_alt1 = PI/2;
                     }
                     else
                     {
                         theta_alt1 = -PI/2;
                     }
                 }
                 else if(alt_y1==0)
                 {
                     if(alt_x1>0)
                     {
                         theta_alt1 = 0;
                     }
                     else
                     {
                         theta_alt1 = PI;
                     }
                 }
                 else
                 {
                     if(alt_x1>0)
                     {
                         if(alt_y1>0)
                         {
                             theta_alt1 = atan(abs(alt_y1/alt_x1));
                         }
                         else
                         {
                             theta_alt1 = -atan(abs(alt_y1/alt_x1));
                         }
                     }
                     else
                     {
                         if(alt_y1>0)
                         {
                             theta_alt1 = PI - atan(abs(alt_y1/alt_x1));
                         }
                         else
                         {
                             theta_alt1 = PI + atan(abs(alt_y1/alt_x1));
                         }
                     }


                 }

                 double Speed_alt_X1 = cos(theta_alt1);
                 double Speed_alt_Y1 = sin(theta_alt1);
                 double curr_x1 =uav1->pos().rx();
                 double curr_y1 =uav1->pos().ry();


                 if(curr_x1<=altp_x1 || curr_y1<=altp_y1)
                 {
                   uav1->setPos(curr_x1+Speed_alt_X1,curr_y1+Speed_alt_Y1);
                 }
                else
                 {
                     targets1[t1 - 1][4] = targets1[t1 - 1][1] - curr_x1;
                     targets1[t1 - 1][5] = targets1[t1 - 1][2] - curr_y1;
                     targets1[t1 - 1][6]= abs(targets1[t1 - 1][5])/abs(targets1[t1 - 1][4]);
                     if(targets1[t1 - 1][4]>0)
                     {
                         if(targets1[t1 - 1][5]>=0)
                         {
                           targets1[t1 - 1][7] = atan(targets1[t1 - 1][6]);
                         }
                         else
                         {
                           targets1[t1 - 1][7] = -atan(targets1[t1 - 1][6]);
                         }
                     }

                     else if(targets1[t1 - 1][4]<0)
                     {
                         if(targets1[t1 - 1][5]>=0)
                         {
                           targets1[t1 - 1][7] = PI - atan(targets1[t1 - 1][6]);
                         }
                         else
                         {
                           targets1[t1 - 1][7] = PI + atan(targets1[t1 - 1][6]);
                         }

                     }


                     else
                     {
                       if(targets1[t1 - 1][5]>0)
                       {
                         targets1[t1 - 1][7] = PI/2;
                       }
                       else if(targets1[t1 - 1][5]<0)
                       {
                         targets1[t1 - 1][7] = -PI/2;
                       }
                       else
                       {
                          targets1[t1 - 1][7] = 0;
                       }
                     }


                    alt_x1 =0;
                    alt_y1 =0;
                    altp_x1 =0;
                    altp_y1 =0;
                 }

             }
             else
             {
             double curr_x1 =uav1->pos().rx();
             double curr_y1 =uav1->pos().ry();
             double curr_d1 =sqrt(pow(curr_x1,2) + pow(curr_y1,2));
             if((curr_d1 >= targets1[t1 - 1][3]))
             {
               uav1->setPos(curr_x1+0,curr_y1+0);
               move1 = 0;
               t1 = t1 + 1;
             }
             else
             {
                 double SpeedX1 = cos(targets1[t1 - 1][7]);
                 double SpeedY1 = sin(targets1[t1 - 1][7]);
                 uav1->setPos(curr_x1+SpeedX1,curr_y1+SpeedY1);
                 if(t1==1)
                 {
                     uav1_time = 100-(((targets1[t1 - 1][3] - curr_d1)/(targets1[t1 - 1][3]))*100);
                 }
                 else
                 {
                     double rem_dist1 = sqrt(pow(targets1[t1 - 1][1] - curr_x1,2) + pow(targets1[t1 - 1][2] - curr_y1,2));
                     double tot_dist1 = sqrt(pow(targets1[t1 - 1][1] - targets1[t1 - 2][1],2) + pow(targets1[t1 - 1][2] - targets1[t1 - 2][2],2));
                     uav1_time = 100-((rem_dist1/tot_dist1)*100);
                 }


             }
           }
}
}
void quad_sim::movement2()
{
    ui->uav2_time->setValue(uav2_time);
    ui->uav2_time1->setValue(uav2_time);
    uav2_batt = uav2_batt - (.1/6);
    ui->uav2_batt->setValue(uav2_batt);
    ui->uav2_dam->setValue(uav2_dam);
         if(move2==0)
         {
             ui->uav2_stat->setText("Idle");
             ui->uav2_stat->setStyleSheet("QLabel { background-color : red}");
                 double curr_x2 =uav2->pos().rx();
                 double curr_y2 =uav2->pos().ry();
                 uav2_time =0;

                 uav2->setPos(curr_x2+0,curr_y2+0);


           }
         else
         {
             ui->uav2_stat->setText("Busy");
             ui->uav2_stat->setStyleSheet("QLabel { background-color : green}");
             if(abs(alt_x2)>0 || abs(alt_y2)>0)
             {
                 if(alt_x2==0)
                 {
                     if(alt_y2>0)
                     {
                         theta_alt2 = PI/2;
                     }
                     else
                     {
                         theta_alt2 = -PI/2;
                     }
                 }
                 else if(alt_y2==0)
                 {
                     if(alt_x2>0)
                     {
                         theta_alt2 = 0;
                     }
                     else
                     {
                         theta_alt2 = PI;
                     }
                 }
                 else
                 {
                     if(alt_x2>0)
                     {
                         if(alt_y2>0)
                         {
                             theta_alt2 = atan(abs(alt_y2/alt_x2));
                         }
                         else
                         {
                             theta_alt2 = -atan(abs(alt_y2/alt_x2));
                         }
                     }
                     else
                     {
                         if(alt_y2>0)
                         {
                             theta_alt2 = PI - atan(abs(alt_y2/alt_x2));
                         }
                         else
                         {
                             theta_alt2 = PI + atan(abs(alt_y2/alt_x2));
                         }
                     }


                 }

                 double Speed_alt_X2 = cos(theta_alt2);
                 double Speed_alt_Y2 = sin(theta_alt2);
                 double curr_x2 =uav2->pos().rx();
                 double curr_y2 =uav2->pos().ry();


                 if(curr_x2<=altp_x2 || curr_y2<=altp_y2)
                 {
                   uav2->setPos(curr_x2+Speed_alt_X2,curr_y2+Speed_alt_Y2);
                 }
                else
                 {
                     targets2[t2 - 1][4] = targets2[t2 - 1][1] - curr_x2;
                     targets2[t2 - 1][5] = targets2[t2 - 1][2] - curr_y2;
                     targets2[t2 - 1][6]= abs(targets2[t2 - 1][5])/abs(targets2[t2 - 1][4]);
                     if(targets2[t2 - 1][4]>0)
                     {
                         if(targets2[t2 - 1][5]>=0)
                         {
                           targets2[t2 - 1][7] = atan(targets2[t2 - 1][6]);
                         }
                         else
                         {
                           targets2[t2 - 1][7] = -atan(targets2[t2 - 1][6]);
                         }
                     }

                     else if(targets2[t2 - 1][4]<0)
                     {
                         if(targets2[t2 - 1][5]>=0)
                         {
                           targets2[t2 - 1][7] = PI - atan(targets2[t2 - 1][6]);
                         }
                         else
                         {
                           targets2[t2 - 1][7] = PI + atan(targets2[t2 - 1][6]);
                         }

                     }


                     else
                     {
                       if(targets2[t2 - 1][5]>0)
                       {
                         targets2[t2 - 1][7] = PI/2;
                       }
                       else if(targets2[t2 - 1][5]<0)
                       {
                         targets2[t2 - 1][7] = -PI/2;
                       }
                       else
                       {
                          targets2[t2 - 1][7] = 0;
                       }
                     }


                    alt_x2 =0;
                    alt_y2 =0;
                    altp_x2 =0;
                    altp_y2 =0;
                 }

             }
             else
             {
             double curr_x2 =uav2->pos().rx();
             double curr_y2 =uav2->pos().ry();
             double curr_d2 =sqrt(pow(curr_x2,2) + pow(curr_y2,2));
             if((curr_d2 >= targets2[t2 - 1][3]))
             {
               uav2->setPos(curr_x2+0,curr_y2+0);
               move2 = 0;
               t2 = t2 + 1;
             }
             else
             {
                 double SpeedX2 = cos(targets2[t2 - 1][7]);
                 double SpeedY2 = sin(targets2[t2 - 1][7]);
                 uav2->setPos(curr_x2+SpeedX2,curr_y2+SpeedY2);
                 if(t2==1)
                 {
                     uav2_time = 100-(((targets2[t2 - 1][3] - curr_d2)/(targets2[t2 - 1][3]))*100);
                 }
                 else
                 {
                     double rem_dist2 = sqrt(pow(targets2[t2 - 1][1] - curr_x2,2) + pow(targets2[t2 - 1][2] - curr_y2,2));
                     double tot_dist2 = sqrt(pow(targets2[t2 - 1][1] - targets2[t2 - 2][1],2) + pow(targets2[t2 - 1][2] - targets2[t2 - 2][2],2));
                     uav2_time = 100-((rem_dist2/tot_dist2)*100);
                 }


             }
           }
}
}
void quad_sim::movement3()
{
    ui->uav3_time->setValue(uav3_time);
    ui->uav3_time1->setValue(uav3_time);
    uav3_batt = uav3_batt - (.1/6);
    ui->uav3_batt->setValue(uav3_batt);
    ui->uav3_dam->setValue(uav3_dam);
         if(move3==0)
         {
             ui->uav3_stat->setText("Idle");
             ui->uav3_stat->setStyleSheet("QLabel { background-color : red}");
                 double curr_x3 =uav3->pos().rx();
                 double curr_y3 =uav3->pos().ry();
                 uav3_time =0;

                 uav3->setPos(curr_x3+0,curr_y3+0);


           }
         else
         {
             ui->uav3_stat->setText("Busy");
             ui->uav3_stat->setStyleSheet("QLabel { background-color : green}");
             if(abs(alt_x3)>0 || abs(alt_y3)>0)
             {
                 if(alt_x3==0)
                 {
                     if(alt_y3>0)
                     {
                         theta_alt3 = PI/2;
                     }
                     else
                     {
                         theta_alt3 = -PI/2;
                     }
                 }
                 else if(alt_y3==0)
                 {
                     if(alt_x3>0)
                     {
                         theta_alt3 = 0;
                     }
                     else
                     {
                         theta_alt3 = PI;
                     }
                 }
                 else
                 {
                     if(alt_x3>0)
                     {
                         if(alt_y3>0)
                         {
                             theta_alt3 = atan(abs(alt_y3/alt_x3));
                         }
                         else
                         {
                             theta_alt3 = -atan(abs(alt_y3/alt_x3));
                         }
                     }
                     else
                     {
                         if(alt_y3>0)
                         {
                             theta_alt3 = PI - atan(abs(alt_y3/alt_x3));
                         }
                         else
                         {
                             theta_alt3 = PI + atan(abs(alt_y3/alt_x3));
                         }
                     }


                 }

                 double Speed_alt_X3 = cos(theta_alt3);
                 double Speed_alt_Y3 = sin(theta_alt3);
                 double curr_x3 =uav3->pos().rx();
                 double curr_y3 =uav3->pos().ry();


                 if(curr_x3<=altp_x3 || curr_y3<=altp_y3)
                 {
                   uav3->setPos(curr_x3+Speed_alt_X3,curr_y3+Speed_alt_Y3);
                 }
                else
                 {
                     targets3[t3 - 1][4] = targets3[t3 - 1][1] - curr_x3;
                     targets3[t3 - 1][5] = targets3[t3 - 1][2] - curr_y3;
                     targets3[t3 - 1][6]= abs(targets3[t3 - 1][5])/abs(targets3[t3 - 1][4]);
                     if(targets3[t3 - 1][4]>0)
                     {
                         if(targets3[t3 - 1][5]>=0)
                         {
                           targets3[t3 - 1][7] = atan(targets3[t3 - 1][6]);
                         }
                         else
                         {
                           targets3[t3 - 1][7] = -atan(targets3[t3 - 1][6]);
                         }
                     }

                     else if(targets3[t3 - 1][4]<0)
                     {
                         if(targets3[t3 - 1][5]>=0)
                         {
                           targets3[t3 - 1][7] = PI - atan(targets3[t3 - 1][6]);
                         }
                         else
                         {
                           targets3[t3 - 1][7] = PI + atan(targets3[t3 - 1][6]);
                         }

                     }


                     else
                     {
                       if(targets3[t3 - 1][5]>0)
                       {
                         targets3[t3 - 1][7] = PI/2;
                       }
                       else if(targets3[t3 - 1][5]<0)
                       {
                         targets3[t3 - 1][7] = -PI/2;
                       }
                       else
                       {
                          targets3[t3 - 1][7] = 0;
                       }
                     }


                    alt_x3 =0;
                    alt_y3 =0;
                    altp_x3 =0;
                    altp_y3 =0;
                 }

             }
             else
             {
             double curr_x3 =uav3->pos().rx();
             double curr_y3 =uav3->pos().ry();
             double curr_d3 =sqrt(pow(curr_x3,2) + pow(curr_y3,2));
             if((curr_d3 >= targets3[t3 - 1][3]))
             {
               uav3->setPos(curr_x3+0,curr_y3+0);
               move3 = 0;
               t3 = t3 + 1;
             }
             else
             {
                 double SpeedX3 = cos(targets3[t3 - 1][7]);
                 double SpeedY3 = sin(targets3[t3 - 1][7]);
                 uav3->setPos(curr_x3+SpeedX3,curr_y3+SpeedY3);
                 if(t3==1)
                 {
                     uav3_time = 100-(((targets3[t3 - 1][3] - curr_d3)/(targets3[t3 - 1][3]))*100);
                 }
                 else
                 {
                     double rem_dist3 = sqrt(pow(targets3[t3 - 1][1] - curr_x3,2) + pow(targets3[t3 - 1][2] - curr_y3,2));
                     double tot_dist3 = sqrt(pow(targets3[t3 - 1][1] - targets3[t3 - 2][1],2) + pow(targets3[t3 - 1][2] - targets3[t3 - 2][2],2));
                     uav3_time = 100-((rem_dist3/tot_dist3)*100);
                 }


             }
           }
}
}

void quad_sim::on_uav1_engage_clicked()
{
    if(t0==2)
    {
        QPixmap pix3("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/1.png");
        scene2->addPixmap(pix3.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else if(t0==3)
    {
        QPixmap pix3("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/5.png");
        scene2->addPixmap(pix3.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else if(t0==4)
    {
        QPixmap pix3("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/9.png");
        scene2->addPixmap(pix3.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else if(t0==5)
    {
        QPixmap pix3("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/13.png");
        scene2->addPixmap(pix3.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else
    {
        QPixmap pix3("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/17.png");
        scene2->addPixmap(pix3.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }




}

void quad_sim::on_uav1_confirm_clicked()
{
   move0 = 1;

   QPixmap pix31("C:/Study/Thesis Project/QtProjects/GCS_example/black.png");
   scene2->addPixmap(pix31.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
}

void quad_sim::on_uav1_deny_clicked()
{
    move0 = 1;

    QPixmap pix31("C:/Study/Thesis Project/QtProjects/GCS_example/black.png");
    scene2->addPixmap(pix31.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
}

void quad_sim::on_uav1_retire_clicked()
{
   move0 = 0;
}


void quad_sim::on_uav2_engage_clicked()
{
    if(t1==2)
    {
        QPixmap pix4("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/2.png");
        scene2->addPixmap(pix4.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else if(t1==3)
    {
        QPixmap pix4("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/6.png");
        scene2->addPixmap(pix4.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else if(t1==4)
    {
        QPixmap pix4("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/10.png");
        scene2->addPixmap(pix4.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else if(t1==5)
    {
        QPixmap pix4("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/14.png");
        scene2->addPixmap(pix4.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else
    {
        QPixmap pix4("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/18.png");
        scene2->addPixmap(pix4.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }


}


void quad_sim::on_uav2_confirm_clicked()
{
    move1 = 1;

    QPixmap pix41("C:/Study/Thesis Project/QtProjects/GCS_example/black.png");
    scene2->addPixmap(pix41.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
}

void quad_sim::on_uav2_deny_clicked()
{
    move1 = 1;

    QPixmap pix41("C:/Study/Thesis Project/QtProjects/GCS_example/black.png");
    scene2->addPixmap(pix41.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
}


void quad_sim::on_uav2_retire_clicked()
{

    move1 = 0;
}

void quad_sim::on_uav3_engage_clicked()
{
    if(t2==2)
    {
        QPixmap pix5("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/3.png");
        scene2->addPixmap(pix5.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else if(t2==3)
    {
        QPixmap pix5("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/7.png");
        scene2->addPixmap(pix5.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else if(t2==4)
    {
        QPixmap pix5("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/11.png");
        scene2->addPixmap(pix5.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else if(t2==5)
    {
        QPixmap pix5("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/15.png");
        scene2->addPixmap(pix5.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else
    {
        QPixmap pix5("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/19.png");
        scene2->addPixmap(pix5.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }


}

void quad_sim::on_uav3_confirm_clicked()
{
    move2 = 1;

    QPixmap pix51("C:/Study/Thesis Project/QtProjects/GCS_example/black.png");
    scene2->addPixmap(pix51.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
}

void quad_sim::on_uav3_deny_clicked()
{
    move2 = 1;

    QPixmap pix51("C:/Study/Thesis Project/QtProjects/GCS_example/black.png");
    scene2->addPixmap(pix51.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
}

void quad_sim::on_uav3_retire_clicked()
{

    move2 = 0;
}


void quad_sim::on_uav4_engage_clicked()
{
    if(t3==2)
    {
        QPixmap pix6("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/4.png");
        scene2->addPixmap(pix6.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else if(t3==3)
    {
        QPixmap pix6("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/8.png");
        scene2->addPixmap(pix6.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else if(t3==4)
    {
        QPixmap pix6("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/12.png");
        scene2->addPixmap(pix6.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else if(t3==5)
    {
        QPixmap pix6("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/16.png");
        scene2->addPixmap(pix6.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }
    else
    {
        QPixmap pix6("C:/Study/Thesis Project/QtProjects/mod/GCS_example4/aoi/20.png");
        scene2->addPixmap(pix6.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
    }


}

void quad_sim::on_uav4_confirm_clicked()
{
    move3 = 1;

    QPixmap pix61("C:/Study/Thesis Project/QtProjects/GCS_example/black.png");
    scene2->addPixmap(pix61.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
}

void quad_sim::on_uav4_deny_clicked()
{
    move3 = 1;

    QPixmap pix61("C:/Study/Thesis Project/QtProjects/GCS_example/black.png");
    scene2->addPixmap(pix61.scaled((QSize((int)scene2->width(), (int)scene2->height()))));
}

void quad_sim::on_uav4_retire_clicked()
{

    move3 = 0;
}

void quad_sim::on_pushButton_simstop_clicked()
{
   move0 = 0;
   move1 = 0;
   move2 = 0;
   move3 = 0;
   qApp->quit();
}

void quad_sim::on_pushButton_simpause_clicked()
{
    move0 = 0;
    move1 = 0;
    move2 = 0;
    move3 = 0;
}


void quad_sim::mousePressEvent(QMouseEvent *event)

{
    // get scene coords from the view coord
    QPointF scenePt = ui->graphicsView->mapToScene(event->pos());
    if(replan_click==0)
    {
        QPointF localPt0 = uav0->mapFromScene(scenePt);
        QPointF localPt1 = uav1->mapFromScene(scenePt);
        QPointF localPt2 = uav2->mapFromScene(scenePt);
        QPointF localPt3 = uav3->mapFromScene(scenePt);
        qDebug()<< localPt0;
        qDebug()<< localPt1;
        qDebug()<< localPt2;
        qDebug()<< localPt3;

        if((abs(localPt0.rx())<=30) && (abs(localPt0.ry())<=30))
        {
            replan_click=1;
        }
        else if((abs(localPt1.rx())<=30) && (abs(localPt1.ry())<=30))
        {
            replan_click=2;
        }
        else if((abs(localPt2.rx())<=30) && (abs(localPt2.ry())<=30))
        {
            replan_click=3;
        }
        else if((abs(localPt3.rx())<=30) && (abs(localPt3.ry())<=30))
        {
            replan_click=4;
        }
        else
        {
            replan_click=0;
        }


    }
    else
    {
        if(replan_click==1)
        {
            QPointF localPt0 = uav0->mapFromScene(scenePt);
            alt_x0 = localPt0.rx();
            altp_x0 = localPt0.rx() + uav0->pos().rx();
            alt_y0 = localPt0.ry();
            altp_y0 = localPt0.ry() + uav0->pos().ry();
            replan_click=0;
        }
        else if(replan_click==2)
        {
            QPointF localPt1 = uav1->mapFromScene(scenePt);
            alt_x1 = localPt1.rx();
            alt_y1 = localPt1.ry();
            altp_x1 = localPt1.rx() + uav1->pos().rx();
            altp_y1 = localPt1.ry() + uav1->pos().ry();
            replan_click=0;
        }
        else if(replan_click==3)
        {
            QPointF localPt2 = uav2->mapFromScene(scenePt);
            alt_x2 = localPt2.rx();
            alt_y2 = localPt2.ry();
            altp_x2 = localPt2.rx() + uav2->pos().rx();
            altp_y2 = localPt2.ry() + uav2->pos().ry();
            replan_click=0;
        }
        else if(replan_click==4)
        {
            QPointF localPt3 = uav3->mapFromScene(scenePt);
            alt_x3 = localPt3.rx();
            alt_y3 = localPt3.ry();
            altp_x3 = localPt3.rx() + uav3->pos().rx();
            altp_y3 = localPt3.ry() + uav3->pos().ry();
            replan_click=0;
        }
        else
        {
            replan_click=0;
        }
    }

}
