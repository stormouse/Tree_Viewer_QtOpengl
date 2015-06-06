#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QSqlTableModel>
#include<QSqlQuery>
#include<QSqlRecord>
#include"treeviewwidget.h"
#include<QObject>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->openGLWidget->setFocusPolicy();
}

void MainWindow::keyPressEvent(QKeyEvent  *event)
{

   // ui->openGLWidget->setFocusPolicy(Qt::StrongFocus);


   // QMessageBox::information(this, "question", "Yes");
    if(event->key()== Qt::Key_Right)
    {
        // QMessageBox::information(this, "question", "Yes");
        qDebug() << "right";
    }
    else if(event->key() == Qt::Key_Left)
    {
        qDebug() << "left";
    }
    else if(event->key() == Qt::Key_Down)
    {
        qDebug() << "down";
    }
    else if(event->key() == Qt::Key_Up)
    {
        qDebug() << "up";
    }



}


//创建数据库连接
void MainWindow::connectDB()
{
//获取是否存在有数据库连接
   QSqlDatabase db = QSqlDatabase::database("test", false);
   if(db.isValid())//存在连接直接退出
       {
           return;
       }
      //创建一连接名为"test"的数据库连接
   db = QSqlDatabase::addDatabase("QODBC", "test");
   db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=G:\\test.mdb");
   if(!db.open()){
       qDebug() << "Error:";
   }
}
//查询数据库数据
void MainWindow::queryDB()
{
    //获取连接名库"test"的连接
    QSqlDatabase db = QSqlDatabase::database("test", false);
    QSqlTableModel *model = new QSqlTableModel(0,db);
    model->setTable("tree");
    model->select();
    ui->tableView->setModel(model);
   /*QSqlTableModel model;

        model.setTable("tree");
       // model.setFilter("age > 20 and age < 25");
        model.select();
        if (model.select()) {
            for (int i = 0; i < model.rowCount(); ++i) {
                QSqlRecord record = model.record(i);
                QString name = record.value("Name").toString();
                //int age = record.value("age").toInt();
                qDebug() << name;
                qDebug() << "dgdfg";
            }
        }*/




    /*QSqlQuery query(db);
    if(query.exec("select * from tree")){
        while(query.next()){
            qDebug() << query.value(0).toString() << " " << query.value(1).toString()
                        << query.value(2).toString() << " " << query.value(3).toString();
        }
    }*/
     /*QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
        model->setQuery(QString("select * from tree;"));
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("year"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("name"));
        ui->tableView->setModel(model);*/
     //QSplitter *splitter = new QSplitter;


               // ui->listView->setModel(model);
                    //ui->treeView->setModel(model);
            //ui->tableView->setModel(model);
            //model->setSort(1, Qt::AscendingOrder);
            //model->setHeaderData(1, Qt::Horizontal, "year");
            //model->setHeaderData(2, Qt::Horizontal, "name");

            //QTableView *view = new QTableView;
            /*view->setModel(model);
            view->setSelectionMode(QAbstractItemView::SingleSelection);
            view->setSelectionBehavior(QAbstractItemView::SelectRows);
    //        view->setColumnHidden(0, true);
            view->resizeColumnsToContents();
            view->setEditTriggers(QAbstractItemView::NoEditTriggers);

            QHeaderView *header = view->horizontalHeader();
            header->setStretchLastSection(true);

            view->show();*/
            //splitter->show();
   /* QSqlTableModel model;
    model.setTable("tree");

    model.select();
    ui->tableView->setModel(model);
*/
   // db.close();


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

/*void MainWindow::on_action_triggered()
{

}
*/


