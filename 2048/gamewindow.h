#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "gamewidget.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void on_actionNew_game_triggered();

    void on_actionExit_triggered();

    void on_actionCustom_triggered();

    void on_actionStandart_triggered();

    void on_actionRoman_numbers_triggered();

private:
    Ui::GameWindow *ui;
    GameWidget *gw;
};

#endif // GAMEWINDOW_H
