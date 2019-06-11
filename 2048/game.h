#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPicture>
#include <QDebug>
#include <QTimer>
#include <gtest/gtest.h>
#include <QObject>

class Game:public QObject
{

    Q_OBJECT
public:
    Game(int width, int height);
    Game(int score, QVector<QVector<qint8>> elements);

    enum Move{
        right,
        bottom,
        left,
        top,
        none
    };

    QList<QVector<QVector<qint8>>> move(Move direction);

    int get_score(){return score;}

    bool check_game_over() const;

    QString return_value_cell(int i);



signals:
    void change_score(int score);

public slots:

private:
    QVector<QVector<qint8>> elements;//zero == null
    QVector<QVector<bool>> elements_was_changes;
    int score=0;
    QVector<int> values_elements={2,4,8,16,32,64,128,256,512,1024,2048,4096};

    void end_game();
    void add_new_element();
    QPoint random_free_cell() const;

    bool move_down();

    static QVector<QVector<qint8>> rotate_by_clock_arrow(const QVector<QVector<qint8>>& matrix);

    static QVector<QVector<qint8>> rotate_forward(QVector<QVector<qint8> > matrix, const Move& direction);
    static QVector<QVector<qint8>> rotate_back( QVector<QVector<qint8>> matrix, const Move& direction);



    FRIEND_TEST(Game, rotate_matrix);
    FRIEND_TEST(Game, move_down1);
    FRIEND_TEST(Game, move_down2);

};

#endif // WIDGET_H
