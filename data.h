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
    QList<QList<int>> _matrix; //����
    int _row;                  //��
    int _column;               //��
    int _cellWidth;            //������
    GameStatus _gameStatus;    //��Ϸ״̬
    int _mines;                //����
};

#endif // DATA_H
