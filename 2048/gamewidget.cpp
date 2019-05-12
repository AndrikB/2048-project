#include "gamewidget.h"
#include <QDebug>

gameWidget::gameWidget(int width, int height, QWidget *parent) : QWidget(parent)
{
    //elements.clear();
    elements.fill(QVector<qint8>(width, 0), height);

    add_new_element();add_new_element();

}

bool gameWidget::game_over() const
{
    int heigth=elements.size();
    int width=elements[0].size();
    for (int i = 0; i < heigth; ++i)
        for (int j=0;j<width;j++)
            if (elements.at(i).at(j)==0)
                return false;

    for(int i = 0; i < heigth-1; i++){
        for(int j = 0; j < width-1; j++){
            if(elements[i][j] == elements[i+1][j] || elements[i][j] == elements[i][j+1])
                return false;
        }
    }
    for(int i = 0; i < heigth-1; i++){
        if(elements[i][3] == elements[i+1][3])
            return false;
    }
    for(int j = 0; j < width; j++){
        if(elements[3][j] == elements[3][j+1])
            return false;
    }


    return true;
}

void gameWidget::end_game()
{
    //todo
}

void gameWidget::add_new_element()
{
    QPoint pos=random_free_cell();
    if (pos.x()==-1) return;
    elements[pos.y()][pos.x()]=qrand()%2+1;
}

QPoint gameWidget::random_free_cell() const
{
    int heigth=elements.size();
    int width=elements[0].size();
    QVector<QPoint> free_pos;
    for (int i = 0; i < heigth; ++i)
        for (int j=0;j<width;j++)
            if (elements.at(i).at(j)==0)
                free_pos.push_back(QPoint(j,i));
    if (free_pos.size()==0) {qDebug()<<"bug; isnt free cells"; return QPoint(-1,-1);}

    return free_pos[qrand()%free_pos.size()];
}

void gameWidget::move(gameWidget::Move direction)
{
    //todo

    add_new_element();

    if (game_over()){end_game(); return;}

    this->update();//todo update

}
