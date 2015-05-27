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




void MainWindow::on_action_2_triggered()
{
    QString path = QFileDialog::getSaveFileName(this,tr("Save"),".",tr("Project File(*.2333)"));
}

void MainWindow::on_action_3_triggered()
{
    QString path = QFileDialog::getSaveFileName(this,tr("Save"),".",tr("Image Files(*.jpg *.png)"));
}

void MainWindow::on_action_4_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open"), ".", tr("Image Files(*.jpg *.png)"));
}

void MainWindow::on_action_triggered()
{
    
}
