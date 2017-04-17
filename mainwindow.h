#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

#include "sweepscene.h"
#include <QMouseEvent>
#include "data.h"
#include <QGraphicsSimpleTextItem>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initMenu();
    void initGraphics();
public slots:
    void startSlot();
protected:
    QGraphicsSimpleTextItem * _textItem;
};



#endif // MAINWINDOW_H
