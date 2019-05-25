#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    gw = new GameWidget(4, 4, this);
    ui->gameLayout->addWidget(gw);
    new_game(count_width,count_height);
    connect(gw, SIGNAL(change_score(int)), this, SLOT(change_score(int)));
    connect(gw, SIGNAL(end_game(int)), this, SLOT(end_game(int)));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::change_score(int score)
{
    ui->Score->setText("Score: "+QString::number(score));
}

void GameWindow::end_game(int score)
{
    QMessageBox::information(this, "You lose", "Start new game");
    QFile f1(score_FileName);
    f1.open(QFile::ReadOnly);
    QTextStream txt(&f1);
    int HightScore;
    txt>>HightScore;
    f1.close();
    if (score>HightScore){
        f1.open(QFile::WriteOnly|QFile::Truncate);
        QTextStream txt(&f1);
        txt<<score;
        f1.close();
    }
    new_game(count_width, count_height);
}


void GameWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Left) gw->move(Game::Move::left);
    if(e->key()==Qt::Key_Right) gw->move(Game::Move::right);
    if(e->key()==Qt::Key_Up) gw->move(Game::Move::top);
    if(e->key()==Qt::Key_Down) gw->move(Game::Move::bottom);
}

QString GameWindow::score_fileName(int width, int height)
{
    return "score_"+QString::number(width)+"_"+QString::number(height)+".txt";
}

void GameWindow::new_game(int width, int height)
{
    count_width=width; count_height=height;
    //todo

    score_FileName=score_fileName(width, height);
    QFile f1(score_FileName);
    if (!f1.open(QFile::ReadOnly)){
        ui->HightScore->setText("Hight score: 0");
        return;
    }
    QTextStream txt(&f1);
    int HightScore;
    txt>>HightScore;
    ui->HightScore->setText("Hight score: "+QString::number(HightScore));
    f1.close();
}



void GameWindow::on_actionNew_game_triggered()
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"New game", "Do you really want to start new game?",
                                      QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes){
            //todo
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


//---------STYLES----------

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
    gw->change_images(QImage(":/resource/skins/Roman_numeralsforMy2048.jpg"));

}


