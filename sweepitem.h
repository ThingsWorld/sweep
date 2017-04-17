#ifndef SWEEPITEM_H
#define SWEEPITEM_H

#include <QGraphicsItem>
#include "data.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QMouseEvent>
#include <QGraphicsSimpleTextItem>

typedef enum
{
    init,
    swept,
    flag,
    iswin
}Status;


class SweepItem:public QGraphicsPixmapItem
{
public:
    SweepItem(int x=0,int y=0);
    ~SweepItem();
    void initItem();
    int sweep();
    void dataSweep();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    inline void setItemStatus(Status s){_itemStatus = s;}
    inline Status getItemStatus(){return _itemStatus;}
    void startTime();

    inline void setTextItem(QGraphicsSimpleTextItem *textItem){ _textItem = textItem;}
    inline QGraphicsSimpleTextItem *getTextItem(){return _textItem;}
protected:
    QList<QPixmap*> _pixmapList;
    int _x;
    int _y;
    int _row;
    int _column;
    int _cellwidth;
    QString _filename;
    QList<QList<int>> _itemMatrix;
    Status _itemStatus;
    QGraphicsSimpleTextItem * _textItem;
    QGraphicsSimpleTextItem * _textMenisNum;
};

#endif // SWEEPITEM_H
