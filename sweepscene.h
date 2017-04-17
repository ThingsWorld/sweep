#ifndef SWEEPSCENE_H
#define SWEEPSCENE_H

#include <QGraphicsScene>
#include "sweepitem.h"
#include <QTimer>

class SweepScene : public QGraphicsScene
{
    Q_OBJECT
public:
    SweepScene(QObject *parent = Q_NULLPTR);
    ~SweepScene();
    void sweep(int x,int y);
    void initScene();
    void s_sweep(int x, int y);
    void itemWin();
    void pixmapListClear();
    int  sweepnum();

public slots:
    void updateTime();
    void startTime();
protected:
    SweepItem * _pixmap;
    QList<QList<SweepItem*>> _pixmapList;
    int _row;
    int _column;
    int _cellwidth;
    QTimer * _timer;
    QGraphicsSimpleTextItem * _text;
};

#endif // SWEEPSCENE_H
