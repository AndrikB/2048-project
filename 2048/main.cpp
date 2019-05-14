#include "mainwindow.h"
#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QVector<QVector<qint8>> matrix;matrix.fill(QVector<qint8>(10, 0), 5);
    for (int i=0;i<5;i++)
        for (int j = 0; j < 10; ++j) {
            matrix[i][j]=i*10+j;
        }

    qDebug()<<matrix;
    matrix=Game::rotate_by_clock_arrow(matrix);
    qDebug()<<matrix;
    matrix=Game::rotate_by_clock_arrow(matrix);
    qDebug()<<matrix;
    matrix=Game::rotate_by_clock_arrow(matrix);
    qDebug()<<matrix;
    matrix=Game::rotate_by_clock_arrow(matrix);
    qDebug()<<matrix;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
