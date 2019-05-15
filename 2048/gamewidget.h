#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "game.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(int height, int width, QWidget *parent );

    void move(Game::Move move_to);
signals:

public slots:

private:
    Game game;
};

#endif // GAMEWIDGET_H
