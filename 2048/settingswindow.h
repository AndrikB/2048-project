#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(int width, int height, QWidget *parent = nullptr);
    ~SettingsWindow();

signals:
    void set(int, int);

private slots:
    void on_startBTN_clicked();

    void on_cancelBTN_clicked();

private:
    Ui::SettingsWindow *ui;
    void closeEvent(QCloseEvent*e);
};

#endif // SETTINGSWINDOW_H
