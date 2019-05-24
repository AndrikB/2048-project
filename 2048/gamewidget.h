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
    void change_images(QImage big_image);
    void clear_images();
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

    QVector<QImage> images;

    void end_game();
};

#endif // GAMEWIDGET_H
