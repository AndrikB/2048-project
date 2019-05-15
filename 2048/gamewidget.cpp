#include "gamewidget.h"

GameWidget::GameWidget(int width, int height, QWidget *parent) : QWidget(parent)
{
    game=new Game(width,height);
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

void GameWidget::move(Game::Move move_to)
{
    list_board=game->move(move_to);

    if (list_board.isEmpty()) {
        end_game();
    }

    timer.start(10);//todo change for best visualization


}

void GameWidget::end_game()
{
    //todo
}

void GameWidget::paintEvent(QPaintEvent *)
{
    //todo


    list_board.removeFirst();
    if (list_board.isEmpty()){
        timer.stop();
        return;
    }
}
