#ifndef SWEEPVIEW_H
#define SWEEPVIEW_H

#include "QGraphicsView"
#include <QPropertyAnimation>
#include <QLineEdit>
#include <QGraphicsSimpleTextItem>
#include "sweepscene.h"
#include <QTimer>

class SweepView:public QGraphicsView
{
public:
    SweepView(QWidget *parent = 0);
    void viewWin();
    void showSql();
protected:
    SweepScene * _scene;
    QPropertyAnimation *_animation;
    QLineEdit * _line;
    QGraphicsSimpleTextItem * _textItem;
    QTimer _timer;
};

#endif // SWEEPVIEW_H
