#include "uavitem.h"
#include "aoi.h"
#include <QTimer>
#include <QGraphicsScene>

#include <QGraphicsView>
#include <QList>
#include "threat.h"
#include "quad_sim.h"
#include <QDebug>

//double PI =3.14;

//int t0 = 1, t1 = 1,t2 = 1,t3 = 1;
//int move0 = 0, move1 = 0, move2 = 0,move3 = 0;
//int tar[20][4]={};
//double targets0[4][8] = {};
//double targets1[4][8] = {};
//double targets2[4][8] = {};
//double targets3[4][8] = {};


//UavItem::UavItem(int a, int x[][4])
//{
//    //random start rotation
//    //angle = 45;
//    //setRotation(angle);



////    //random start position
////    QList<QGraphicsItem *> all_items = collidingItems();
////    for (int i = 0, n = all_items.size(); i < n; ++i)
////    {
////            if (typeid(*(all_items[i])) == typeid(UavItem))
////            {

////                       int x_dist = all_items[i]->pos().rx();
////                       int y_dist = all_items[i]->pos().ry();
////                       tar[i][0] = i;
////                       tar[i][1] = x_dist;
////                       tar[i][2] = y_dist;
////                       tar[i][3] = sqrt(pow(tar[i][1],2) + pow(tar[i][2],2));
////                       qDebug() << tar[i][0] <<tar[i][1] <<tar[i][2];


////                // remove them both
//////                scene()->removeItem(colliding_items[i]);
//////                scene()->removeItem(this);
//////                // delete them both
//////                delete colliding_items[i];
//////                delete this;
////                return;
////            }
////        }




//    int StartX = 0;
//    int StartY = 0;

//    V = 1;

//    if(a==0)
//    {
//        StartX = 0;
//        StartY = 0;
//    }
//    else if(a==1)
//    {
//        StartX = 0;
//        StartY = 7;
//    }
//    else if(a==2)
//    {
//        StartX = 7;
//        StartY = 0;
//    }
//    else
//    {
//        StartX = 7;
//        StartY = 7;
//    }
//    target(a,x);
//    setPos(mapToParent(StartX,StartY));

//    QTimer * timer = new QTimer(this);
//    /*connect(timer,SIGNAL(timeout()),this,SLOT(advance()));*/
//  connect(timer, SIGNAL(timeout()), this, SLOT(move()));

//    timer->start(50);


//}

//QRectF UavItem::boundingRect() const
//{
//    return QRect(0,0,7,7);
//}

//void UavItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    QRectF rec = boundingRect();
//    QBrush Brush(Qt::blue);

//    //basic Collision detection
//    if(this->type == 0)
//    {
//       Brush.setColor(Qt::yellow);
//    }
//    else if(this->type == 1)
//    {
//        Brush.setColor(Qt::cyan);
//    }
//    else if(this->type == 2)
//    {
//        Brush.setColor(Qt::magenta);
//    }
//    else
//    {
//        Brush.setColor(Qt::blue);
//    }

////    if(scene()->collidingItems(this).isEmpty())
////    {
////        //no collision
////        Brush.setColor(Qt::green);
////    }
////    else
////    {
////        //collision!!!!
////        Brush.setColor(Qt::red);

////        //Set the position

////    }

//    painter->fillRect(rec,Brush);
//    painter->drawRect(rec);

//}

////void UavItem::advance(int phase)
////{
////    if(!phase) return;

////    QPointF location = this->pos();

////    setPos(mapToParent((SpeedY),(SpeedX)));
////}

//void UavItem::move()
//{

////    QList<QGraphicsItem *> all_items = collidingItems();
////    for(int i = 0, n = all_items.size(); i < n; ++i)
////    {
////        if (typeid(*(all_items[i])) == typeid(AOI)){
////            // remove them both
////            scene()->removeItem(all_items[i]);
//////            scene()->removeItem(this);
////            // delete them both
////            delete all_items[i];
//////            delete this;
////            return;
////        }
////    }

////    QList<AOI *> aoi_list;
////    for (int i = 0, n = aoi_list.size(); i < n; ++i)
////    {
////    qDebug() << aoi_list.size();
////    }
//   if(type==0)
//   {
//        if(move0==0)
//        {

//                SpeedX = cos(targets0[t0-1][7]);
//                SpeedY = sin(targets0[t0-1][7]);
//                setPos(x()+SpeedX,y()+SpeedY);
//                qDebug() << move1;
//                move0 = 1;
//                qDebug() << move1;

//          }
//        else
//        {
//            if((pos().x() >= targets0[t0-1][1])  && (pos().y() >= targets0[t0-1][2]))
//            {
//              setPos(x()+0,y()+0);
//              move0 = 0;
//              t0 = t0 + 1;
//            }
//            else
//            {
//                SpeedX = cos(targets0[t0-1][7]);
//                SpeedY = sin(targets0[t0-1][7]);
//                setPos(x()+SpeedX,y()+SpeedY);
//            }
//          }
//   }
//   else if(type==1)
//   {
//       if(move1==0)
//       {

//               SpeedX = cos(targets1[t1-1][7]);
//               SpeedY = sin(targets1[t1-1][7]);
//               setPos(x()+SpeedX,y()+SpeedY);
//               qDebug() << move1;
//               move1 = 1;
//               qDebug() << move1;

//         }
//       else
//       {
//           if((pos().x() >= targets1[t1-1][1])  && (pos().y() >= targets1[t1-1][2]))
//           {
//             setPos(x()+0,y()+0);
//             move1 = 0;
//             t1 = t1 + 1;
//           }
//           else
//           {
//               SpeedX = cos(targets1[t1-1][7]);
//               SpeedY = sin(targets1[t1-1][7]);
//               setPos(x()+SpeedX,y()+SpeedY);
//           }
//         }
//   }

//   else if(type==2)
//   {
//       if(move2==0)
//       {

//               SpeedX = cos(targets2[t2-1][7]);
//               SpeedY = sin(targets2[t2-1][7]);
//               setPos(x()+SpeedX,y()+SpeedY);
//               qDebug() << move1;
//               move2 = 1;
//               qDebug() << move1;

//         }
//       else
//       {
//           if((pos().x() >= targets2[t2-1][1])  && (pos().y() >= targets2[t2-1][2]))
//           {
//             setPos(x()+0,y()+0);
//             move2 = 0;
//             t2 = t2 + 1;
//           }
//           else
//           {
//               SpeedX = cos(targets2[t2-1][7]);
//               SpeedY = sin(targets2[t2-1][7]);
//               setPos(x()+SpeedX,y()+SpeedY);
//           }
//         }
//   }
//   else
//   {
//       if(move3==0)
//       {

//               SpeedX = cos(targets3[t3-1][7]);
//               SpeedY = sin(targets3[t3-1][7]);
//               setPos(x()+SpeedX,y()+SpeedY);
//               qDebug() << move1;
//               move3 = 1;
//               qDebug() << move1;

//         }
//       else
//       {
//           if((pos().x() >= targets3[t3-1][1])  && (pos().y() >= targets3[t3-1][2]))
//           {
//             setPos(x()+0,y()+0);
//             move3 = 0;
//             t3 = t3 + 1;
//           }
//           else
//           {
//               SpeedX = cos(targets3[t3-1][7]);
//               SpeedY = sin(targets3[t3-1][7]);
//               setPos(x()+SpeedX,y()+SpeedY);
//           }
//         }
//   }
//}

//void UavItem::target(int a,int x[][4])
//{
//    //    QList<QGraphicsItem *> all_items = collidingItems();
//    //    for (int i = 0, n = colliding_items.size(); i < n; ++i){
//    //        if (typeid(*(colliding_items[i])) == typeid(Threat)){
//    //            // remove them both
//    //            scene()->removeItem(colliding_items[i]);
//    //            scene()->removeItem(this);
//    //            // delete them both
//    //            delete colliding_items[i];
//    //            delete this;
//    //            return;
//    //        }
//    //    }

//    //    QList<AOI *> aoi_list;
//    //    for (int i = 0, n = aoi_list.size(); i < n; ++i)
//    //    {
//    //    qDebug() << aoi_list.size();
//    //    }

//    if( a==0)
//    {

//        double tarX = 0, tarY = 0;
//        type = 0;
//        for(int i=0;i<5;i++)
//        {
//          for(int j=0;j<4;j++)
//          {
//            targets0[i][j] = x[4*i][j];
//            //qDebug() << targets[i][j];
//          }
//          targets0[i][4] = targets0[i][1] - tarX;
//          targets0[i][5] = targets0[i][2] - tarY;
//          targets0[i][6]= abs(targets0[i][5])/abs(targets0[i][4]);
//          if(targets0[i][4]>0)
//          {
//              if(targets0[i][5]>=0)
//              {
//                targets0[i][7] = atan(targets0[i][6]);
//              }
//              else
//              {
//                targets0[i][7] = -atan(targets0[i][6]);
//              }
//          }

//          else if(targets0[i][4]<0)
//          {
//              if(targets0[i][5]>=0)
//              {
//                targets0[i][7] = PI - atan(targets0[i][6]);
//              }
//              else
//              {
//                targets0[i][7] = PI + atan(targets0[i][6]);
//              }

//          }


//          else
//          {
//            if(targets0[i][5]>0)
//            {
//              targets0[i][7] = PI/2;
//            }
//            else if(targets0[i][5]<0)
//            {
//              targets0[i][7] = -PI/2;
//            }
//            else
//            {
//               targets0[i][7] = 0;
//            }
//          }

//          tarX = targets0[i][1];
//          tarY = targets0[i][2];

//          qDebug() << targets0[i][0] << targets0[i][1] << targets0[i][2] << targets0[i][3] << targets0[i][4] << targets0[i][5] << targets0[i][6] << targets0[i][7];
//          }
//    }

//    else if(a==1)
//    {

//        double tarX = 0, tarY = 7;
//        type = 1;
//        for(int i=0;i<5;i++)
//        {
//          for(int j=0;j<4;j++)
//          {
//            targets1[i][j] = x[(4*i)+1][j];
//            //qDebug() << targets[i][j];
//          }
//          targets1[i][4] = targets1[i][1] - tarX;
//          targets1[i][5] = targets1[i][2] - tarY;
//          targets1[i][6]= abs(targets1[i][5])/abs(targets1[i][4]);
//          if(targets1[i][4]>0)
//          {
//              if(targets1[i][5]>=0)
//              {
//                targets1[i][7] = atan(targets1[i][6]);
//              }
//              else
//              {
//                targets1[i][7] = -atan(targets1[i][6]);
//              }
//          }

//          else if(targets1[i][4]<0)
//          {
//              if(targets1[i][5]>=0)
//              {
//                targets1[i][7] = PI - atan(targets1[i][6]);
//              }
//              else
//              {
//                targets1[i][7] = PI + atan(targets1[i][6]);
//              }

//          }


//          else
//          {
//            if(targets1[i][5]>0)
//            {
//              targets1[i][7] = PI/2;
//            }
//            else if(targets1[i][5]<0)
//            {
//              targets1[i][7] = -PI/2;
//            }
//            else
//            {
//               targets1[i][7] = 0;
//            }
//          }

//          tarX = targets1[i][1];
//          tarY = targets1[i][2];

//        qDebug() << targets1[i][0] << targets1[i][1] << targets1[i][2] << targets1[i][3] << targets1[i][4] << targets1[i][5] << targets1[i][6] << targets1[i][7];
//          }
//    }
//    else if(a==2)
//    {

//        double tarX = 7, tarY = 0;
//        type = 2;
//        for(int i=0;i<5;i++)
//        {
//          for(int j=0;j<4;j++)
//          {
//            targets2[i][j] = x[(4*i)+2][j];
//            //qDebug() << targets[i][j];
//          }
//          targets2[i][4] = targets2[i][1] - tarX;
//          targets2[i][5] = targets2[i][2] - tarY;
//          targets2[i][6]= abs(targets2[i][5])/abs(targets2[i][4]);
//          if(targets2[i][4]>0)
//          {
//              if(targets2[i][5]>=0)
//              {
//                targets2[i][7] = atan(targets2[i][6]);
//              }
//              else
//              {
//                targets2[i][7] = -atan(targets2[i][6]);
//              }
//          }

//          else if(targets2[i][4]<0)
//          {
//              if(targets2[i][5]>=0)
//              {
//                targets2[i][7] = PI - atan(targets2[i][6]);
//              }
//              else
//              {
//                targets2[i][7] = PI + atan(targets2[i][6]);
//              }

//          }


//          else
//          {
//            if(targets2[i][5]>0)
//            {
//              targets2[i][7] = PI/2;
//            }
//            else if(targets2[i][5]<0)
//            {
//              targets2[i][7] = -PI/2;
//            }
//            else
//            {
//               targets2[i][7] = 0;
//            }
//          }

//          tarX = targets2[i][1];
//          tarY = targets2[i][2];

//         qDebug() << targets2[i][0] << targets2[i][1] << targets2[i][2] << targets2[i][3] << targets2[i][4] << targets2[i][5] << targets2[i][6] << targets2[i][7];
//          }
//    }
//    else
//    {

//        double tarX = 7, tarY = 7;
//        type = 3;
//        for(int i=0;i<5;i++)
//        {
//          for(int j=0;j<4;j++)
//          {
//            targets3[i][j] = x[(4*i)+3][j];
//            //qDebug() << targets[i][j];
//          }
//          targets3[i][4] = targets3[i][1] - tarX;
//          targets3[i][5] = targets3[i][2] - tarY;
//          targets3[i][6]= abs(targets3[i][5])/abs(targets3[i][4]);
//          if(targets3[i][4]>0)
//          {
//              if(targets3[i][5]>=0)
//              {
//                targets3[i][7] = atan(targets3[i][6]);
//              }
//              else
//              {
//                targets3[i][7] = -atan(targets3[i][6]);
//              }
//          }

//          else if(targets3[i][4]<0)
//          {
//              if(targets3[i][5]>=0)
//              {
//                targets3[i][7] = PI - atan(targets3[i][6]);
//              }
//              else
//              {
//                targets3[i][7] = PI + atan(targets3[i][6]);
//              }

//          }


//          else
//          {
//            if(targets3[i][5]>0)
//            {
//              targets3[i][7] = PI/2;
//            }
//            else if(targets3[i][5]<0)
//            {
//              targets3[i][7] = -PI/2;
//            }
//            else
//            {
//               targets3[i][7] = 0;
//            }
//          }

//          tarX = targets3[i][1];
//          tarY = targets3[i][2];

//          qDebug() << targets3[i][0] << targets3[i][1] << targets3[i][2] << targets3[i][3] << targets3[i][4] << targets3[i][5] << targets3[i][6] << targets3[i][7];
//          }

//    }

//}

////void UavItem::on_pushButton_simstart_clicked()
////{

////    qDebug() << "aoi_list.size()""";
////}



