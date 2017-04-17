#include "data.h"
#include <QPoint>
#include <QList>
#include <time.h>
#include <QDebug>
Data *Data::_data = nullptr;


Data::Data(int row, int column, int cellwith, int mines)
    :_row(row),
     _column(column),
     _cellWidth(cellwith),
     _mines(mines)
{
    init();
    deployMines();
}

void Data::init()
{
    _gameStatus = G_runnig;

    for(int i = 0; i < _row; i++)
    {
        QList<int> rowlist;
        for(int j = 0; j < _column; j++)
        {
            rowlist.append(0);
        }
        _matrix.append(rowlist);
    }
}


//雷的数据
void Data::deployMines()
{
    srand(time(NULL));
    QList<QPoint> list;
    for(int i = 0; i < _row; i++)
    {
        for(int j = 0; j < _column; j++)
        {
            list.append(QPoint(i, j));
        }
    }

    int index;
    int row, column;
    for(int i = 0; i < _mines; i++)
    {
        index = rand() % list.length();
        row = list[index].x();
        column = list[index].y();
        _matrix[row][column] = -1;

        addMine(row - 1, column -1);
        addMine(row - 1, column);
        addMine(row - 1, column + 1);
        addMine(row, column -1);
        addMine(row, column + 1);
        addMine(row + 1, column - 1);
        addMine(row + 1, column);
        addMine(row + 1, column + 1);

        list.removeAt(index);
    }
}

void Data::addMine(int x, int y)
{
    //判断x,y两个的坐标不超过界限
    if(x < 0 || y < 0 || x >= _row || y >= _column)
    {
        return;
    }

    //-1表示雷
    if(_matrix[x][y] != -1)
    {
        _matrix[x][y] += 1;
    }
}


Data *Data::dis()
{
    if(_data==nullptr)
    {
        _data = new Data;
    }
    return _data;
}

void Data::realease()
{
    if(_data!=nullptr)
    {
        delete _data;
        _data = nullptr;
    }
}
