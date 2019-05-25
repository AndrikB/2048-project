#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_next_clicked();

    void change_image( );

    void on_delete_last_image_clicked();

    void on_save_as_clicked();

private:
    QList<QPair<QHBoxLayout, QPair<QPushButton, QLabel>>*> layouts;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
