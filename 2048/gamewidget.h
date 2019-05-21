#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "game.h"
#include <QIcon>

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(int count_width, int count_height, QWidget *parent );

    void move(Game::Move move_to);
    void change_images(QPicture big_image);
signals:

public slots:

private:
    Game *game;
    QTimer timer;
    QList<QVector<QVector<qint8>>> list_board;
    int count_width, count_height;

    QPoint startPos;
    void mousePressEvent(QMouseEvent * );
    void mouseReleaseEvent(QMouseEvent *);

    void paintEvent(QPaintEvent*);
    QColor return_color_cell(int i);
    QColor return_color_text(int i);

    QVector<QIcon> pictures;

    void end_game();
};

#endif // GAMEWIDGET_H
