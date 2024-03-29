#include "game.h"



Game::Game(int width, int height )
{
    values_elements.push_back(*values_elements.end()*2);//for future

    elements.clear();
    elements.fill(QVector<qint8>(width, 0), height);

    add_new_element();add_new_element();

}

Game::Game(int score, QVector<QVector<qint8>> elements)
{
    this->score=score;
    this->elements=elements;
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
        if(elements[i][width-1] == elements[i+1][width-1])
            return false;
    }
    for(int j = 0; j < width-1; j++){
        if(elements[height-1][j] == elements[height-1][j+1])
            return false;
    }


    return true;
}

void Game::end_game()
{
    qDebug()<<"lose";
    //todo
}

void Game::add_new_element()
{
    QPoint pos=random_free_cell();
    if (pos.x()==-1) {exit(-1);}
    elements[pos.y()][pos.x()]=(qrand()%10+1)/10+1;
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


bool Game::move_down()
{
    bool was_changes=false;
    int height=elements.size();
    int width=elements[0].size();
    for (int i=0;i<width;i++)//for all column
    {
        for (int j=height-1;j>0;j--)
        {
            if (elements[j][i]==0 && elements[j-1][i]!=0)
            {
                std::swap(elements[j][i], elements[j-1][i]);
                std::swap(elements_was_changes[j][i], elements_was_changes[j-1][i]);
                was_changes=true;
            }
            else if (elements[j][i]!=0 && elements[j][i]==elements[j-1][i]&&!elements_was_changes[j][i]&&! elements_was_changes[j-1][i])
            {

                elements[j][i]++;
                elements_was_changes[j][i]=true;
                elements[j-1][i]=0;
                was_changes=true;
                score+=return_value_cell(elements[j][i]).toInt();
            }
        }
    }

    return was_changes;
}

QList<QVector<QVector<qint8>>> Game::move(Move direction)
{
    qDebug()<<"game::move";
    emit change_score(score);
    if (direction==Move::none) return QList<QVector<QVector<qint8>>>{elements};

    QList<QVector<QVector<qint8>>> list_board;

    elements=rotate_forward(elements,direction);

    int height=elements.size();
    int width=elements[0].size();
    elements_was_changes.clear();
    elements_was_changes.fill(QVector<bool>(width, 0), height);

    bool was_changes=false;
    do{
        qDebug()<<rotate_back(elements, direction);
        was_changes=move_down();
        if (was_changes)
            list_board.push_back(rotate_back(elements, direction));
    }while (was_changes);
    qDebug()<<"end move";
    elements=rotate_back(elements, direction);

    if (!list_board.isEmpty())
        add_new_element();
    qDebug()<<"add el";
    list_board.push_back(elements);
    qDebug()<<elements;

    qDebug()<<"end game::move";
    emit (change_score(score));
    return list_board;
}

QString Game::return_value_cell(int i)
{
    if (i==0) return QString();
    while (i>values_elements.size()) values_elements.push_back(values_elements.last()*2);
    return QString::number(values_elements[i-1]);
}
