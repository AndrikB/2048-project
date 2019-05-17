#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include "gamewidget.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    GameWidget *gw;

};

#endif // GAMEWINDOW_H
