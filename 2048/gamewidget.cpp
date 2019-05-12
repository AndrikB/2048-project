#include "gamewidget.h"
#include <QDebug>

gameWidget::gameWidget(int width, int heigth, QWidget *parent) : QWidget(parent)
{
    elements.clear();
    elements.fill(QVector<int>(width, 0), heigth);

}
