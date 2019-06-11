#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "gamewidget.h"
#include "settingswindow.h"

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
    void change_score(int score);

    void end_game(int score);

    void on_actionNew_game_triggered();

    void on_actionExit_triggered();

    void on_actionCustom_triggered();

    void on_actionStandart_triggered();

    void on_actionRoman_numbers_triggered();

    void new_game(int width, int height);

    void on_actionCar_triggered();

    void on_actionPink_triggered();

    void on_actionGreen_triggered();

    void on_actionBlue_triggered();

private:
    void keyPressEvent(QKeyEvent*);
    void closeEvent(QCloseEvent*e);
    QString score_fileName(int width, int height);
    QString score_FileName;
    Ui::GameWindow *ui;
    GameWidget *gw;
    SettingsWindow* window;
    int count_width=4, count_height=4;
};

#endif // GAMEWINDOW_H
