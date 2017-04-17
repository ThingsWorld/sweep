#include "sweepitem.h"
#include <QGraphicsPixmapItem>
#include "sweepitem.h"
#include "data.h"
#include <QDebug>
#include <QString>
#include <QGraphicsSceneMouseEvent>
#include <sweepscene.h>
#include <sweepview.h>
#include <QMessageBox>
#include <unistd.h>

#define PIXMAP_FILE(_filename) {\
    QPixmap * pixmap = new QPixmap(_filename);\
    _pixmapList.append(pixmap);\
}


SweepItem::SweepItem(int x, int y)
{
    _row = Data::dis()->getRow();
    _column = Data::dis()->getColumn();
    _cellwidth = Data::dis()->getCellWidth();
    _itemMatrix = Data::dis()->getMatrix();

    _x = x;
    _y = y;
    initItem();
    this->setPixmap(QPixmap(*_pixmapList[18]).scaled(_cellwidth,_cellwidth));
}

SweepItem::~SweepItem()
{
}

void SweepItem::initItem()
{

    PIXMAP_FILE(":/pic/0.png");
    PIXMAP_FILE(":/pic/0_press.png");

    PIXMAP_FILE(":/pic/1.png");
    PIXMAP_FILE(":/pic/1_press.png");


    PIXMAP_FILE(":/pic/2.png");
    PIXMAP_FILE(":/pic/2_press.png");

    PIXMAP_FILE(":/pic/3.png");
    PIXMAP_FILE(":/pic/3_press.png");

    PIXMAP_FILE(":/pic/4.png");
    PIXMAP_FILE(":/pic/4_press.png");

    PIXMAP_FILE(":/pic/5.png");
    PIXMAP_FILE(":/pic/5_press.png");

    PIXMAP_FILE(":/pic/6.png");
    PIXMAP_FILE(":/pic/6_press.png");

    PIXMAP_FILE(":/pic/7.png");
    PIXMAP_FILE(":/pic/7_press.png");

    PIXMAP_FILE(":/pic/8.png");
    PIXMAP_FILE(":/pic/8_press.png");


    PIXMAP_FILE(":/pic/normal.png");

    PIXMAP_FILE(":/pic/normal_press.png");

    PIXMAP_FILE(":/pic/-1.png");

    PIXMAP_FILE(":/pic/explode.png");
    PIXMAP_FILE(":/pic/flag.png");

    PIXMAP_FILE(":/pic/GameOver.png");

}


//ÇÐ»»Í¼Æ¬
int SweepItem::sweep()
{
    return _itemMatrix[_x][_y];
}

void SweepItem::dataSweep()
{
    switch (_itemMatrix[_x][_y])
    {
    case 0:
        this->setPixmap((*_pixmapList[1]).scaled(_cellwidth,_cellwidth));
        this->setItemStatus(swept);
        break;
    case 1:
        this->setPixmap((*_pixmapList[3]).scaled(_cellwidth,_cellwidth));
        this->setItemStatus(swept);
        break;
    case 2:
        this->setPixmap((*_pixmapList[5]).scaled(_cellwidth,_cellwidth));
        this->setItemStatus(swept);
        break;
    case 3:
        this->setPixmap((*_pixmapList[7]).scaled(_cellwidth,_cellwidth));
        this->setItemStatus(swept);
        break;
    case 4:
        this->setPixmap((*_pixmapList[9]).scaled(_cellwidth,_cellwidth));
        this->setItemStatus(swept);
        break;
    case 5:
        this->setPixmap((*_pixmapList[11]).scaled(_cellwidth,_cellwidth));
        this->setItemStatus(swept);
        break;
    case 6:
        this->setPixmap((*_pixmapList[13]).scaled(_cellwidth,_cellwidth));
        this->setItemStatus(swept);
        break;
    case 7:
        this->setPixmap((*_pixmapList[15]).scaled(_cellwidth,_cellwidth));
        this->setItemStatus(swept);
        break;
    case 8:
        this->setPixmap((*_pixmapList[17]).scaled(_cellwidth,_cellwidth));
        this->setItemStatus(swept);
        break;
    case -1:
        this->setPixmap((*_pixmapList[20]).scaled(_cellwidth,_cellwidth));
        this->setItemStatus(swept);
        break;
    default:
        break;
    }
}

void SweepItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    ((SweepScene *)scene())->startTime();
}

void SweepItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(Data::dis()->getStatus()==G_runnig)
    {
        if(event->button()==Qt::RightButton\
                &&getItemStatus()!=swept)
        {
            this->setPixmap((*_pixmapList[22]).scaled(_cellwidth,_cellwidth));
            if(this->getItemStatus()!=flag)
            {
                this->setItemStatus(flag);

            }
            else if(this->getItemStatus()==flag)
            {
                this->setPixmap(QPixmap(*_pixmapList[18]).scaled(_cellwidth,_cellwidth));
                this->setItemStatus(init);
            }
        }
        else if(event->button()==Qt::LeftButton\
            &&getItemStatus()!=flag\
            &&this->getItemStatus()!=swept)
        {
            ((SweepScene *)scene())->sweep(_x,_y);
            this->setItemStatus(swept);
        }
    }
}

void SweepItem::startTime()
{
    _textItem = new QGraphicsSimpleTextItem;
    _textMenisNum = new QGraphicsSimpleTextItem;
    _textItem = ((SweepScene *)scene())->addSimpleText("00:00",QFont("system",20));
    _textItem->setPos(Data::dis()->getCellWidth()\
                   ,Data::dis()->getCellWidth()*Data::dis()->getRow());
    _textItem->setBrush(Qt::red);

    _textMenisNum = ((SweepScene *)scene())->addSimpleText("5",QFont("system",20));
    _textMenisNum->setPos(Data::dis()->getCellWidth()*(Data::dis()->getColumn()-1)\
                   ,Data::dis()->getCellWidth()*Data::dis()->getRow());
    _textMenisNum->setBrush(Qt::red);
}




