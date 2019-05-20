#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    gw = new GameWidget(8, 5, this);
    ui->gameLayout->addWidget(gw);
}

GameWindow::~GameWindow()
{
    delete ui;
}
