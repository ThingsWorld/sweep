#include "sweepview.h"
#include <QGraphicsView>
#include "sweepscene.h"
#include <QDebug>
#include <QSqlTableModel>
#include <QTableView>
#include <QPropertyAnimation>
#include <QHBoxLayout>
#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <unistd.h>
#include <QSqlQuery>
#include <QInputDialog>
#include <String>
#include <QHeaderView>

#define MESC_TIME  (60*10)
SweepView::SweepView(QWidget *parent)
    :QGraphicsView(parent)
{
    _scene = new SweepScene(this);
}

void SweepView::viewWin()
{
    QMessageBox msgBox;
    msgBox.setText("wow!!你赢了，是否要提交排名！");
    msgBox.setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    switch (ret)
    {
    case QMessageBox::Ok:
        showSql();
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }
}


void SweepView::showSql()
{

    QDialog * widget = new QDialog;
    widget->setStyleSheet("background-image: url(:/pic/background.png);");
    QPushButton * ok_pb = new QPushButton("提交");
    QPushButton * no_pb = new QPushButton("取消");
    _line = new QLineEdit;
    QLabel labelName("名字：");
    QHBoxLayout * hBox = new QHBoxLayout;
    QHBoxLayout *hBoxName = new QHBoxLayout;
    QVBoxLayout * vBox = new QVBoxLayout(widget);


    hBoxName->addWidget(&labelName);
    hBoxName->addWidget(_line);

    hBox->addWidget(ok_pb);
    hBox->addWidget(no_pb);

    vBox->addLayout(hBoxName);
    vBox->addLayout(hBox);


    connect(ok_pb,QPushButton::clicked,this,[&](){
        QString name = _line->text();

        QDialog* dialog = new QDialog;
        dialog->setStyleSheet("background-image: url(:/pic/background.png);");
        QTableView * table = new QTableView;
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        QSqlTableModel * model = new QSqlTableModel(table,db);
        dialog->setWindowIconText("sql");

        dialog->setFixedSize(700,700);
        dialog->setWindowIcon(QIcon(QPixmap(":/pic/background.png")));

        db.setHostName("127.0.0.1");
        db.setUserName("root");
        db.setPassword("root");
        db.setDatabaseName("sweepDB");


        if(!db.open())
        {
            qDebug()<<db.lastError().text()<<endl;
        }
        QSqlQuery query;
        query.prepare("INSERT INTO sweeptable(name,level) "
                      "VALUES(:name,:level)");
        query.bindValue(":name",name);
        query.bindValue(":level",0);
        query.exec();

        model->setTable("sweepTable");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        table->verticalHeader()->hide();
        table->setModel(model);
        QVBoxLayout * vBox = new QVBoxLayout(dialog);
        vBox->addWidget(table);
        dialog->exec();

        widget->close();
        db.close();
    });
    connect(no_pb,QPushButton::clicked,this,[&](){
        widget->close();
    });
    widget->exec();
}



