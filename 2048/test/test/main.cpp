#include <gtest/gtest.h>
#include <game.h>

#include <QApplication>

TEST(Game, rotate_matrix){
    int height=5;
    int width=10;
    QVector<QVector<qint8>> matrix;matrix.fill(QVector<qint8>(width, 0), height);
    for (qint8 i=0;i<height;i++)
        for (qint8 j = 0; j < width; ++j) {
            matrix[i][j]=i*10+j;
        }
    EXPECT_EQ(matrix, Game::rotate_back(Game::rotate_forward(matrix, Game::Move::top), Game::Move::top));
    EXPECT_EQ(matrix, Game::rotate_back(Game::rotate_forward(matrix, Game::Move::bottom), Game::Move::bottom));
    EXPECT_EQ(matrix, Game::rotate_back(Game::rotate_forward(matrix, Game::Move::left), Game::Move::left));
    EXPECT_EQ(matrix, Game::rotate_back(Game::rotate_forward(matrix, Game::Move::right), Game::Move::right));

}

TEST(Game, move_down){
    int height=2;
    int width=4;
    QVector<QVector<qint8>> matrix{ {0,0,1,1}, {0,1,0,1}};
    QVector<QVector<qint8>> matrix_copy(matrix);
    Game::move_down(matrix_copy);
    qDebug()<<endl;
    qDebug()<<matrix<<endl<<matrix_copy;
    for (int i=0;i<width;i++) {
        EXPECT_EQ(matrix_copy[0][i],0);
        if (i==0) EXPECT_EQ(matrix_copy[1][i], 0);
        else if (i==3) EXPECT_EQ(matrix_copy[1][i], 2);
        else  EXPECT_EQ(matrix_copy[1][i], 1);
    }

}

int main(int argc,char*argv[])
{
    QApplication a(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
