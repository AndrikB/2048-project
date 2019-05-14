#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPicture>
#include <QDebug>

class Game
{

public:
    Game(int width, int height);

    enum Move{
        right,
        bottom,
        left,
        top
    };


    static QVector<QVector<qint8>> rotate_by_clock_arrow(const QVector<QVector<qint8>>& matrix);

    //from direction to bottom
    static QVector<QVector<qint8>> rotate_forward(QVector<QVector<qint8> > matrix, const Move& direction);

    //from bottom to direction
    static QVector<QVector<qint8>> rotate_back( QVector<QVector<qint8>> matrix, const Move& direction);



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

    bool move_down(QVector<QVector<qint8>> &matrix);
    QList<QVector<QVector<qint8>>> move(Move direction);




};

#endif // WIDGET_H
