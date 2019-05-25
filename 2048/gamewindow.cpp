#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    gw = new GameWidget(4, 4, this);
    ui->gameLayout->addWidget(gw);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_actionNew_game_triggered()
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"New game", "Do you really want to start new game?",
                                      QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes){

        }

}

void GameWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Exit", "Do you really want to leave the game?",
                                      QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes){
            close();
        }
}


void GameWindow::on_actionStandart_triggered()
{
    gw->clear_images();
}


void GameWindow::on_actionCustom_triggered()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Skin"), QDir::current().path(), "*forMy2048.jpg");
    gw->change_images(QImage(fileName));

}


void GameWindow::on_actionRoman_numbers_triggered()
{
    qDebug()<<QImage(":/resource/skins/Roman_numeralsforMy2048.jpg");
    gw->change_images(QImage(":/resource/skins/Roman_numeralsforMy2048.jpg"));

}
