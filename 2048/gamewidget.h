#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class gameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit gameWidget(int width, int heigth, QWidget *parent);

    enum Move{
        right,
        bottom,
        left,
        top
    };

signals:
    void game_over(int score);
    void update_score(int score);

public slots:

private:
    QVector<QVector<qint8>> elements;//zero == null
    int score=0;

    bool game_over() const;
    void end_game();
    void add_new_element();
    QPoint random_free_cell() const;
    void move(Move direction);

};

#endif // WIDGET_H
