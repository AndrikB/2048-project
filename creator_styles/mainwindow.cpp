#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_next_clicked()
{
    QPair<QHBoxLayout, QPair<QPushButton, QLabel>> *element =new  QPair<QHBoxLayout, QPair<QPushButton, QLabel>>;
    element->second.first.setText("change photo");element->first.addWidget(&element->second.first);
    element->first.addWidget( &element->second.second);
    layouts.push_back(element);
    connect(&element->second.first, SIGNAL(clicked()), this, SLOT(change_image()));
    //todo connect
    ui->elements->addLayout(&element->first);
}

void MainWindow::change_image()
{
    QPushButton* clickedBtn = static_cast<QPushButton*>(sender());
    QListIterator<QPair<QHBoxLayout, QPair<QPushButton, QLabel>> *> it(layouts);
    while (&it.peekNext()->second.first!=clickedBtn) {
        it.next();
    }
    QString FileName =QFileDialog::getOpenFileName(this, tr("Open File"), QString(),"*.jpg");
    QImage img(FileName);
    img=img.scaled(QSize(150,150));
    it.peekNext()->second.second.setPixmap(QPixmap::fromImage(img));

}
