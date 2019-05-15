#include "game.h"



Game::Game(int width, int height )
{
    values_elements.push_back(*values_elements.end()*2);//for future

    elements.clear();
    elements.fill(QVector<qint8>(width, 0), height);

    add_new_element();add_new_element();

}

bool Game::check_game_over() const
{
    int height=elements.size();
    int width=elements[0].size();
    for (int i = 0; i < height; ++i)
        for (int j=0;j<width;j++)
            if (elements.at(i).at(j)==0)
                return false;

    for(int i = 0; i < height-1; i++){
        for(int j = 0; j < width-1; j++){
            if(elements[i][j] == elements[i+1][j] || elements[i][j] == elements[i][j+1])
                return false;
        }
    }
    for(int i = 0; i < height-1; i++){
        if(elements[i][3] == elements[i+1][3])
            return false;
    }
    for(int j = 0; j < width; j++){
        if(elements[3][j] == elements[3][j+1])
            return false;
    }


    return true;
}

void Game::end_game()
{
    //todo
}

void Game::add_new_element()
{
    QPoint pos=random_free_cell();
    if (pos.x()==-1) {exit(-1);}
    elements[pos.y()][pos.x()]=qrand()%2+1;
}

QPoint Game::random_free_cell() const
{
    int height=elements.size();
    int width=elements[0].size();
    QVector<QPoint> free_pos;
    for (int i = 0; i < height; ++i)
        for (int j=0;j<width;j++)
            if (elements.at(i).at(j)==0)
                free_pos.push_back(QPoint(j,i));
    if (free_pos.size()==0) {qDebug()<<"bug; isnt free cells"; return QPoint(-1,-1);}

    return free_pos[qrand()%free_pos.size()];
}

QVector<QVector<qint8> > Game::rotate_by_clock_arrow(const QVector<QVector<qint8> > &matrix)
{
    QVector<QVector<qint8>> new_matrix;
    new_matrix.clear();
    int width=matrix.size();
    int height=matrix[0].size();
    new_matrix.fill(QVector<qint8>(width, 0), height);

    for (int i=0;i<height;i++)
        for (int j=0;j<width;j++) {
            new_matrix[i][j]=matrix[width-1-j][i];
        }

    return new_matrix;
}

//from direction to bottom
QVector<QVector<qint8> > Game::rotate_forward(QVector<QVector<qint8> > matrix, const Game::Move &direction)
{
    if (direction==Move::right)
    {
        matrix=rotate_by_clock_arrow(matrix);
    }

    if (direction==Move::top)
    {
        matrix=rotate_by_clock_arrow(matrix);
        matrix=rotate_by_clock_arrow(matrix);
    }

    if (direction==Move::left)
    {
        matrix=rotate_by_clock_arrow(matrix);
        matrix=rotate_by_clock_arrow(matrix);
        matrix=rotate_by_clock_arrow(matrix);
    }
    return matrix;
}

//from bottom to direction
QVector<QVector<qint8> > Game::rotate_back(QVector<QVector<qint8> > matrix, const Game::Move &direction)
{
    if (direction==Move::right)
    {
        matrix=rotate_by_clock_arrow(matrix);
        matrix=rotate_by_clock_arrow(matrix);
        matrix=rotate_by_clock_arrow(matrix);
    }

    if (direction==Move::top)
    {
        matrix=rotate_by_clock_arrow(matrix);
        matrix=rotate_by_clock_arrow(matrix);
    }

    if (direction==Move::left)
    {
        matrix=rotate_by_clock_arrow(matrix);
    }
    return matrix;
}


bool Game::move_down(QVector<QVector<qint8> > &matrix)
{
    bool was_changes=false;
    int height=matrix.size();
    int width=matrix[0].size();
    for (int i=0;i<width;i++)//for all column
    {
        for (int j=height-1;j>0;j--)
        {
            if (matrix[j][i]==0 && matrix[j-1][i]!=0)
            {
                std::swap(matrix[j][i], matrix[j-1][i]);
                was_changes=true;
            }
            else if (matrix[j][i]!=0 && matrix[j][i]==matrix[j-1][i])
            {
                matrix[j][i]++;
                matrix[j-1][i]=0;
                was_changes=true;
            }
        }
    }

    return was_changes;
}

QList<QVector<QVector<qint8>>> Game::move(Move direction)
{
    QList<QVector<QVector<qint8>>> list_board;
    elements=rotate_forward(elements,direction);

    bool was_changes=false;
    do{
        was_changes=false;

    }while (was_changes==true);
    //todo move to bottom


    elements=rotate_back(elements, direction);


    add_new_element();

    if (check_game_over()){end_game(); return QList<QVector<QVector<qint8>>>();}

    return list_board;
}
