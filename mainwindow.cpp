#include "mainwindow.h"
#include "QGraphicsView"
#include "sweepscene.h"
#include <QMenu>
#include <QMenuBar>
#include "data.h"
#include "sweepview.h"
#include <QDebug>
#include <QMouseEvent>
#include <QInputDialog>
#include <QLineEdit>
#include <QDateTime>

#include <QGraphicsSimpleTextItem>
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    initMenu();
    initGraphics();
}

void MainWindow::initMenu()
{
    QMenu *gameMenu = this->menuBar()->addMenu("游戏(&G)");
    gameMenu->addAction("开始(&S)",this,SLOT(startSlot())\
                        ,QKeySequence("Ctrl+b"));
    QMenu *difficultyMenu = gameMenu->addMenu("难度");

    QAction* common = difficultyMenu->addAction("普通");
    common->setCheckable(true);
    common->setChecked(true);

    QAction* mid = difficultyMenu->addAction("中等");
    mid->setCheckable(true);

    QAction* hard = difficultyMenu->addAction("难");
    hard->setCheckable(true);

    gameMenu->addAction("退出(&E)",this,SLOT(close()));

    QActionGroup *group = new QActionGroup(this);
    group->addAction(common);
    group->addAction(mid);
    group->addAction(hard);
}


void MainWindow::startSlot()
{
    Data::dis()->setStatus(G_runnig);
    initGraphics();
}

void MainWindow::initGraphics()
{
    SweepView * view = new SweepView(this);
    SweepScene * _scene = new SweepScene(view);

    view->setScene(_scene);
    view->setSizeIncrement(Data::dis()->getRow()*Data::dis()->getCellWidth()\
                           ,Data::dis()->getColumn()*Data::dis()->getCellWidth());
    this->setCentralWidget(view);
}



MainWindow::~MainWindow()
{
    Data::realease();
}


