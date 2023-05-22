#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pc_Label->setText("Hallo");
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_Console_Field_blockCountChanged(int newBlockCount)
{

}

