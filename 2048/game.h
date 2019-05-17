#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPicture>
#include <QDebug>
#include <QTimer>
#include <gtest/gtest.h>

class Game
{

public:
    Game(int width, int height);

    enum Move{
        right,
        bottom,
        left,
        top,
        none
    };

    QList<QVector<QVector<qint8>>> move(Move direction);

    int get_score(){return score;}

    QString return_value_cell(int i){return (i==0)?QString():QString::number(values_elements[i-1]);}



signals:
    void check_game_over(int score);
    void update_score(int score);

public slots:

private:
    QVector<QVector<qint8>> elements;//zero == null
    int score=0;
    QVector<int> values_elements={2,4,8,16,32,64,128,256,512,1024,2048,4096};

    bool check_game_over() const;
    void end_game();
    void add_new_element();
    QPoint random_free_cell() const;

    static bool move_down(QVector<QVector<qint8>> &matrix);

    static QVector<QVector<qint8>> rotate_by_clock_arrow(const QVector<QVector<qint8>>& matrix);

    static QVector<QVector<qint8>> rotate_forward(QVector<QVector<qint8> > matrix, const Move& direction);
    static QVector<QVector<qint8>> rotate_back( QVector<QVector<qint8>> matrix, const Move& direction);



    FRIEND_TEST(Game, rotate_matrix);
    FRIEND_TEST(Game, move_down1);
    FRIEND_TEST(Game, move_down2);

};

#endif // WIDGET_H
