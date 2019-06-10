#include "gamewidget.h"
#include <QPainter>
#include <QMouseEvent>
GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    QPalette palette;
    setPalette(palette);
    setAutoFillBackground(true);

    QFile fout("file.txt");
    bool correct_read=false;
    if (fout.open(QFile::ReadOnly))
    {
        qDebug()<<0;
        correct_read=true;
        QTextStream out(&fout);
        int score;
        QVector<QVector<qint8>> elements;
        out>>count_width>>count_height>>score;
        elements.fill(QVector<qint8>(count_width, 0), count_height);
        int c;

        qDebug()<<count_width<<count_height;
        for (int i=0;i<count_width;i++)
            for(int j=0;j<count_height;j++){
                if (out.atEnd())correct_read=false;
                out>>c; elements[i][j]=static_cast<qint8>(c); //todo delete c
            }

        if (correct_read)
            game=new Game(score, elements);
    }
    if (!correct_read)
    {
        game=new Game(4,4);
        count_width=4;
        count_height=4;
    }
    connect(game, SIGNAL(change_score(int)), this, SLOT(change_score(int)));
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

void GameWidget::save_game()
{
     QFile fin("file.txt");
     fin.open(QFile::WriteOnly|QFile::Truncate);
     QTextStream in(&fin);
     in<<count_width<<' '<<count_height<<' '<<game->get_score();
     for (int i=0;i<count_width;i++)
         for(int j=0;j<count_height;j++)
                in<<' '<<list_board.last()[i][j];
     fin.close();
}

void GameWidget::mousePressEvent(QMouseEvent * e)
{
    startPos = e->pos();
}

void GameWidget::mouseReleaseEvent(QMouseEvent * e)
{
    QPoint endPos = e->pos();
    if (endPos==startPos)return;
    int dX = (endPos.x() - startPos.x());
    int dY = (endPos.y() - startPos.y());
    if(abs(dX) > abs(dY)){
        if(dX > 0)
            move (Game::Move::right);
        else
           move(Game::Move::left);
    }else{
        if(dY > 0)
            move(Game::Move::bottom);
        else
            move(Game::Move::top);
    }
}

void GameWidget::move(Game::Move move_to)
{
    list_board=game->move(move_to);


    timer.start(50);


}

void GameWidget::change_images(QImage big_image)
{
    const QSize image_size(150, 150);
    images.clear();
    //todo
    int count_images=big_image.width()/image_size.width();
    for (int i=0;i<count_images;i++) {
        QImage new_image;
        new_image=big_image.copy(i*image_size.width(), 0, image_size.width(), image_size.height());
        images.push_back(new_image);
    }

    this->update();
}

void GameWidget::clear_images()
{
    images.clear();
    this->update();
}

void GameWidget::new_game(int width, int height)
{
    delete game;
    count_width=width;
    count_height=height;
    game=new Game(width,height);
    connect(game, SIGNAL(change_score(int)), this, SLOT(change_score(int)));
    move(Game::Move::none);
    update();update();update();
}




QColor GameWidget::return_color_cell(int i)
{
    switch (i) {
    case 0: return QColor(204,192,179);

    case 1: return QColor(238,228,218);

    case 2: return QColor(237,224,200);

    case 3: return QColor(242,177,121);

    case 4: return QColor(245,150,100);

    case 5: return QColor(245,125,95);

    case 6: return QColor(245,95,60);

    case 7: return QColor(237,207,114);

    case 8: return QColor(237,204,97);

    case 9: return QColor(237,204,97);

    case 10: return QColor(237,204,97);

    default: return QColor(238,228,218);
    }
}

QColor GameWidget::return_color_text(int i)
{
    switch (i) {
    case 1:
    case 2: return QColor(119,110,101);

    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10: return QColor(255,255,255);

    default: return QColor(238,228,218);
    }
}


void GameWidget::paintEvent(QPaintEvent *)
{
    if(list_board.isEmpty())return;
    int buf=qMin(width(), height())/50;
    //todo
    double height=(1.0*this->height())/count_height-buf;
    double width=(1.0*this->width())/count_width-buf;

    QPainter painter(this);

    for (int i=0;i<count_height;i++)
        for (int j=0;j<count_width;j++) {

            QRect rect(static_cast<int>(buf+(buf+width)*j) , static_cast<int>(buf+(buf+height)*i),
                       static_cast<int>(width), static_cast<int>(height));
            if (images.size()>list_board.first()[i][j]) {
                painter.drawImage(rect, images[list_board.first()[i][j]]);
            }
            else {
                QString text= game->return_value_cell(list_board.first()[i][j]);

                painter.setBrush(return_color_cell(list_board.first()[i][j])); painter.setPen(painter.brush().color());
                painter.drawRoundedRect(rect, 10, 10);
                if (!text.isEmpty()) {
                    int fontSize=static_cast<int>(qMin(width/text.size(), height*0.8));

                    painter.setFont(QFont("Arial", fontSize));
                    painter.setPen(return_color_text(list_board.first()[i][j]));

                    painter.drawText(rect, Qt::AlignCenter|Qt::NoTextInteraction,text);
                }
            }


        }


    if (list_board.size()==1){
        qDebug()<<"i m here 1";
        timer.stop();
        if (game->check_game_over()){
            qDebug()<<"i m here 2";
            emit (endGame(game->get_score()));
        }
        qDebug()<<"end be here 1";
        return;
    }
    list_board.removeFirst();

}


void GameWidget::change_score(int score)
{
    emit (changeScore(score));
}
