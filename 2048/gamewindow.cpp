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
    gw = new GameWidget(this);
    ui->gameLayout->addWidget(gw);

    connect(gw, SIGNAL(changeScore(int)), this, SLOT(change_score(int)));
    connect(gw, SIGNAL(endGame(int)), this, SLOT(end_game(int)));
    gw->move(Game::none);

    QSize s=gw->getSize();
    count_width=s.width();
    count_height=s.height();

    score_FileName=score_fileName(count_width, count_height);
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

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::change_score(int score)
{
    ui->Score->setText("Score: "+QString::number(score));
    change_hight_score(score);
}

void GameWindow::end_game(int score)
{
    change_score(score);
    QMessageBox::information(this, "You lose", "Start new game");
    change_hight_score(score);
    new_game(count_width, count_height);
}


void GameWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Left) gw->move(Game::Move::left);
    if(e->key()==Qt::Key_Right) gw->move(Game::Move::right);
    if(e->key()==Qt::Key_Up) gw->move(Game::Move::top);
    if(e->key()==Qt::Key_Down) gw->move(Game::Move::bottom);
}

void GameWindow::closeEvent(QCloseEvent *)
{
    gw->save_game();
}

void GameWindow::change_hight_score(int score)
{
    int HightScore=-1;
    QFile f1(score_FileName);
    if (f1.open(QFile::ReadOnly)){
        QTextStream txt(&f1);
        txt>>HightScore;
        f1.close();
    }

    if (score>HightScore){
        f1.open(QFile::WriteOnly|QFile::Truncate);
        QTextStream txt(&f1);
        txt<<score;
        f1.close();
    }

    ui->HightScore->setText("Hight score: "+QString::number(HightScore));
}

QString GameWindow::score_fileName(int width, int height)
{
    return "score_"+QString::number(width)+"_"+QString::number(height)+".txt";
}

void GameWindow::new_game(int width, int height)
{
    count_width=width; count_height=height;

    gw->new_game(count_width,count_height);

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
    window=new SettingsWindow(count_width, count_height, this);
    connect(window, SIGNAL(set(int,int)), this, SLOT(new_game(int, int)));
    window->show();

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



void GameWindow::on_actionCar_triggered()
{
    gw->change_images(QImage(":/resource/skins/mycarforMy2048.jpg"));
}

void GameWindow::on_actionPink_triggered()
{
    gw->change_images(QImage(":/resource/skins/pinkforMy2048.jpg"));
}

void GameWindow::on_actionGreen_triggered()
{
    gw->change_images(QImage(":/resource/skins/greenforMy2048.jpg"));
}

void GameWindow::on_actionBlue_triggered()
{
    gw->change_images(QImage(":/resource/skins/blueforMy2048.jpg"));
}
