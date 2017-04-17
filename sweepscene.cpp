#include "sweepscene.h"
#include "data.h"
#include "sweepitem.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QMessageBox>
#include <sweepview.h>

SweepScene::SweepScene(QObject *parent)
    :QGraphicsScene(parent)
{
    _timer = new QTimer(this);
    _text = new QGraphicsSimpleTextItem;
    initScene();
    connect(_timer, SIGNAL(timeout()), this, SLOT(startTime()));
}

SweepScene::~SweepScene()
{
}

void SweepScene::initScene()
{
    _row = Data::dis()->getRow();
    _column = Data::dis()->getColumn();
    _cellwidth = Data::dis()->getCellWidth();
    for(int i=0; i<_row; i++)
    {
        QList<SweepItem*> list;
        for(int j=0; j<_column; j++)
        {
            _pixmap = new SweepItem(i,j);
            _pixmap->setPos(i*_cellwidth,j*_cellwidth);
            list.append(_pixmap);
            this->addItem(_pixmap);
        }
        _pixmapList.append(list);
    }
//    _pixmap->startTime();
    _timer->start(1000);
}




void SweepScene::pixmapListClear()
{
    _pixmapList.clear();
}

void SweepScene::sweep(int x, int y)
{
    //判断x,y两个的坐标不超过界限
    if(x < 0 || y < 0 || x >= Data::dis()->getRow()
            || y >= Data::dis()->getColumn())
    {
        return;
    }

    if(_pixmapList[x][y]->getItemStatus()!=swept)
    {
        _pixmapList[x][y]->dataSweep();
        _pixmapList[x][y]->setItemStatus(swept);

        //如果为零，周围八全部展开
        if(Data::dis()->getMatrix()[x][y]==0)
        {
            sweep(x - 1, y - 1);
            sweep(x - 1, y);
            sweep(x - 1, y + 1);

            sweep(x, y - 1);
            sweep(x, y + 1);

            sweep(x + 1, y - 1);
            sweep(x + 1, y);
            sweep(x + 1, y + 1);
        }

        //如果是雷，则结束游戏。
        else if(Data::dis()->getMatrix()[x][y]==-1) 
        {
            _timer->stop();
            Data::dis()->setStatus(G_gameOver);
            this->addPixmap(QPixmap(":/pic/GameOver.png")\
                            .scaled(Data::dis()->getColumn()*Data::dis()->getCellWidth()\
                                  ,Data::dis()->getRow()*Data::dis()->getCellWidth()\
                                    ,Qt::IgnoreAspectRatio\
                                    ,Qt::SmoothTransformation));

            for(int i=0; i<_row; i++)
            {
                for(int j=0; j<_column; j++)
                {
                    if(Data::dis()->getMatrix()[i][j]==-1)
                    {
                        _pixmapList[i][j]->setPixmap(QPixmap(":/pic/-1.png").scaled(Data::dis()->getCellWidth(),Data::dis()->getCellWidth()));
                        _pixmapList[x][y]->setPixmap(QPixmap(":/pic/explode.png").scaled(Data::dis()->getCellWidth(),Data::dis()->getCellWidth()));
                    }
                }
            }
        }

        //如果赢了
        if(sweepnum()==\
   (Data::dis()->getRow()*Data::dis()->getColumn()-Data::dis()->getMines()))
        {
            _timer->stop();
            Data::dis()->setStatus(G_win);
            this->addPixmap(QPixmap(":/pic/win.png")\
                                  .scaled(Data::dis()->getColumn()*Data::dis()->getCellWidth()\
                                          ,Data::dis()->getRow()*Data::dis()->getCellWidth()\
                                           ,Qt::IgnoreAspectRatio\
                                           ,Qt::SmoothTransformation));

            SweepView* n =new SweepView;
            n->viewWin();
        }

    }

}

//返回扫过的除雷外的数
int SweepScene::sweepnum()
{
    int num = 0;
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(_pixmapList[i][j]->getItemStatus()==swept)
            {
                num ++;
            }
        }
    }
    return num;
}

//鼠标点击时间开始
void SweepScene::startTime()
{  
    _pixmap->setTextItem(_text);
    int time = _timer->interval();
    _pixmap->getTextItem()->setText(QString::asprintf("%02d:%02d:%02d", time/3600, time/60%60, time%60));
    time++;
}

void SweepScene::updateTime()
{
//    _pixmap->getTextItem()->setText(QString::asprintf("%02d:%02d:%02d",));
}







