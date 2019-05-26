#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPainter>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->save_as->setDisabled(true);
    ui->delete_last_image->setDisabled(true);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_next_clicked()
{
    ui->save_as->setDisabled(false);
    ui->delete_last_image->setDisabled(false);
    QPair<QHBoxLayout, QPair<QPushButton, QLabel>> *element =new  QPair<QHBoxLayout, QPair<QPushButton, QLabel>>;
    int number;
    if (layouts.size()==0)number=0;
    else number=static_cast<int>(pow(2,layouts.size()));
    element->second.first.setText("change photo "+QString::number(number));element->first.addWidget(&element->second.first);
    element->first.addWidget( &element->second.second);
    layouts.push_back(element);
    connect(&element->second.first, SIGNAL(clicked()), this, SLOT(change_image()));
    element->second.second.setPixmap(QPixmap(150,150));
    ui->elementsLayout->addLayout(&element->first);

}

void MainWindow::change_image()
{
    QPushButton* clickedBtn = static_cast<QPushButton*>(sender());
    QListIterator<QPair<QHBoxLayout, QPair<QPushButton, QLabel>> *> it(layouts);
    while (&it.peekNext()->second.first!=clickedBtn) {
        it.next();
    }
    QString FileName =QFileDialog::getOpenFileName(this, tr("Open File"), QString(),"*.jpg");
    if (FileName.isEmpty())return;
    QImage img(FileName);
    img=img.scaled(QSize(150,150));
    it.peekNext()->second.second.setPixmap(QPixmap::fromImage(img));

}

void MainWindow::on_delete_last_image_clicked()
{
    QPair<QHBoxLayout, QPair<QPushButton, QLabel>> * el=layouts.last();
    layouts.removeLast();
    delete el;
    if (layouts.size()==0) {
        ui->save_as->setDisabled(true);
        ui->delete_last_image->setDisabled(true);
    }

}

void MainWindow::on_save_as_clicked()
{
    QString FileName =QFileDialog::getSaveFileName(this, tr("Save as"), QDir::current().path(),tr("*forMy2048.jpg"));
    if (FileName.isEmpty())return;
    if (FileName.right(13)!="forMy2048.jpg") FileName+="forMy2048.jpg";
    qDebug()<<FileName;

    QImage bigImage(layouts.size()*150, 150, QImage::Format::Format_RGBA8888);
    QPainter painter(&bigImage);
    for (int i = 0; i < layouts.size();i++) {
        QImage lbl=layouts[i]->second.second.pixmap()->toImage();
        QRect rect(i*150,0,150,150);
        painter.drawImage(rect, lbl);
    }
    bigImage.save(FileName);
}









