#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "game.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(int width, int height, QWidget *parent );

    void move(Game::Move move_to);
signals:

public slots:

private:
    Game *game;
    QTimer timer;
    QList<QVector<QVector<qint8>>> list_board;

    void end_game();
    void paintEvent(QPaintEvent*);
};

#endif // GAMEWIDGET_H
