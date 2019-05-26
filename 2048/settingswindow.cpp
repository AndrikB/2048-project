#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(int width, int height, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    ui->count_height_spinBox->setValue(height);
    ui->count_width_spinBox->setValue(width);
    parent->setDisabled(true);
    this->setDisabled(false);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_startBTN_clicked()
{
    emit(set(ui->count_width_spinBox->value(), ui->count_height_spinBox->value()));
    parentWidget()->setDisabled(false);
    this->close();
    deleteLater();
}

void SettingsWindow::on_cancelBTN_clicked()
{
    this->close();
}

void SettingsWindow::closeEvent(QCloseEvent *)
{
    parentWidget()->setDisabled(false);
    deleteLater();
}
