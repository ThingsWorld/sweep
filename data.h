#ifndef DATA_H
#define DATA_H
#include <QList>

typedef enum
{
    G_runnig,
    G_gameOver,
    G_win
}GameStatus;


class Data
{
public:
    Data(int row=10,int column=10,int cellwith=50,int mines=5);
    static Data * dis();
    static void realease();

    void  deployMines();
    void  init();
    void  addMine(int x, int y);


    inline int getRow(){return _row;}
    inline void setRow(int r){_row = r;}

    inline int getColumn(){return _column;}
    inline void setColumn(int c){_column = c;}

    inline int getCellWidth(){return _cellWidth;}
    inline void setCellWidth(int ce){_cellWidth = ce;}

    inline int getMines(){return _mines;}
    inline void setMines(int m){_mines = m;}

    inline GameStatus getStatus(){return _gameStatus;}
    inline void setStatus(GameStatus game){_gameStatus = game;}

    inline QList<QList<int>> getMatrix(){return _matrix;}
protected:
    static Data * _data;
    QList<QList<int>> _matrix; //矩阵
    int _row;                  //行
    int _column;               //列
    int _cellWidth;            //方块宽度
    GameStatus _gameStatus;    //游戏状态
    int _mines;                //布雷
};

#endif // DATA_H
