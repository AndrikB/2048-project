#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class gameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit gameWidget(int width, int height, QWidget *parent = nullptr);

signals:

public slots:

private:
    QVector<QVector<int>> elements;
};

#endif // WIDGET_H
