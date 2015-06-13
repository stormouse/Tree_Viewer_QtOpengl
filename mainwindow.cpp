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
#include<QModelIndex>
#include<QStandardItem>
#include<DBManager.h>
#include<newfrom.h>
#include<QTextCodec>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DBManager k;
    k.ConnectToDB();
    QSqlDatabase db = QSqlDatabase::database("test", false);

    QSqlTableModel *modelsupply  = new QSqlTableModel(0,db);
    modelsupply->setTable("Trees");
    modelsupply->select();

    model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Name"));

    QTextCodec*code = QTextCodec::codecForName("GB2312");
    QStandardItem* itemQiao = new QStandardItem(code->toUnicode("乔木类"));
    QStandardItem* itemGuan = new QStandardItem(code->toUnicode("灌木类"));
    QStandardItem* itemTeng = new QStandardItem(code->toUnicode("藤木类"));
    QStandardItem* itemPu = new QStandardItem(code->toUnicode("匍匐类"));
    model->appendRow(itemQiao);
    model->appendRow(itemGuan);
    model->appendRow(itemTeng);
    model->appendRow(itemPu);
    if (modelsupply->select()) {
        for (int i = 0; i < modelsupply->rowCount(); ++i) {
            QSqlRecord record = modelsupply->record(i);
            QString kind = record.value("Tvariety").toString();
            //QString qiao = "乔木类";
            if(kind=="arbor")
            {
             QStandardItem* itemName = new QStandardItem(record.value("Tname").toString());
             itemQiao->appendRow(itemName);
            }
            else
            {
                QStandardItem* itemName = new QStandardItem(record.value("Tname").toString());
                itemGuan->appendRow(itemName);
            }


            //int age = record.value("age").toInt();
        }
    }
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->treeView->setModel(model);


	thefile = NULL;
	
	//set default mode
	ui->action_move->setIcon(QIcon(":/image/blackmove.png"));
	ui->action_rotate->setIcon(QIcon(":/image/rotate.png"));
	ui->action_zoom->setIcon(QIcon(":/image/zoom.png"));
	ui->openGLWidget->SetMode(Mode::MOVE);

	//set disabled actions
	ui->action_undo->setEnabled(false);
	ui->action_redo->setEnabled(false);

	connect(ui->openGLWidget, SIGNAL(Pushed()), this, SLOT(on_pushed()));
}

void MainWindow::keyPressEvent(QKeyEvent  *event)
{
   // ui->openGLWidget->setFocusPolicy(Qt::StrongFocus);
    if(event->key()== Qt::Key_Right)
    {
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

void MainWindow::connectDB()
{
   /*QSqlDatabase db = QSqlDatabase::database("test", false);
   if(db.isValid())
       {
           return;
       }
   db = QSqlDatabase::addDatabase("QODBC", "test");
   db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=G:\\test.mdb");
   if(!db.open()){
       qDebug() << "Error:";
   }*/
}
void MainWindow::queryDB()
{
    //QSqlDatabase db = QSqlDatabase::database("test", false);

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




/*void MainWindow::on_action_2_triggered()
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
}*/




/*void MainWindow::on_pushButton_clicked()
{
    QString home = ui->lineEdit->text();
    if(home == "")
    {
        model->setTable("tree");
        model->removeColumns(1,2);
        model->select();
    }
    else
    {
        model->setFilter(QObject::tr("home = '%1'").arg(home));//根据姓名进行筛选
        model->select();
    }
}*/

void MainWindow::resizeEvent(QResizeEvent *event)
{
	if (ui->openGLWidget->GetImage() != NULL)
	{
		int width = ui->openGLWidget->size().width();
		int height = ui->openGLWidget->size().height();
		int img_width = ui->openGLWidget->GetImage()->width();
		int img_height = ui->openGLWidget->GetImage()->height();
		if (height*img_width > width*img_height)
			height = width*img_height / img_width;
		else
			width = height*img_width / img_height;
		ui->openGLWidget->resize(width, height);
	}
}

/*void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{

    qDebug() << index.data().toString();
    ui->treename->setText();
}*/



void MainWindow::on_action_move_triggered()
{
    ui->action_move->setIcon(QIcon(":/image/blackmove.png"));
    ui->action_rotate->setIcon(QIcon(":/image/rotate.png"));
    ui->action_zoom->setIcon(QIcon(":/image/zoom.png"));
	
	ui->openGLWidget->SetMode(Mode::MOVE);
}

void MainWindow::on_action_rotate_triggered()
{
    ui->action_rotate->setIcon(QIcon(":/image/blackrotate.png"));
    ui->action_move->setIcon(QIcon(":/image/move.png"));
    ui->action_zoom->setIcon(QIcon(":/image/zoom.png"));

	ui->openGLWidget->SetMode(Mode::ROTATE);
}

void MainWindow::on_action_zoom_triggered()
{
    ui->action_zoom->setIcon(QIcon(":/image/blackzoom.png"));
    ui->action_move->setIcon(QIcon(":/image/move.png"));
    ui->action_rotate->setIcon(QIcon(":/image/rotate.png"));

	ui->openGLWidget->SetMode(Mode::ZOOM);
}

void MainWindow::on_action_open_triggered()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open"), ".", tr("Project Files(*.tip)"));
	if (thefile)
		delete thefile;
	thefile = new TreeFile(path);
	thefile->ReadXMLFile(ui->openGLWidget->GetObjectFactory(), ui->openGLWidget);
}

void MainWindow::on_action_new_triggered()
{
    NewFrom *from = new NewFrom();
    from->show();
}

void MainWindow::on_action_save_triggered()
{

}

void MainWindow::on_action_othersave_triggered()
{

}

void MainWindow::on_action_undo_triggered()
{
	ActionNode x = ui->openGLWidget->GetStack()->PopFromUndo();
	ui->action_redo->setEnabled(true);
	//to-do
	switch (x.operation)
	{
	case ActionNode::ADD:
		for (int i = 0; i < x.count(); i++)
		{
			//Object* obj = ui->openGLWidget->GetObjectFactory()->FindObjectByName(x.changedTrees[i].name);
			ui->openGLWidget->GetObjectFactory()->RemoveObject(x.changedTrees[i].name);
		}
		break;
	case ActionNode::REMOVE:
		for (int i = 0; i < x.count(); i++)
		{
			Object* obj = new Object();
			if (obj->Load(TreeInfo(x.changedTrees[i].info)))
			{
				obj->setName(x.changedTrees[i].name);
				obj->SetPosition(x.changedTrees[i].position);
				obj->SetEulerAngles(x.changedTrees[i].angle);
				obj->SetScale(x.changedTrees[i].scale);
				ui->openGLWidget->GetObjectFactory()->AddObject(obj);
			}
		}
		break;
	case ActionNode::ALTER:
		for (int i = 0; i < x.count(); i++)
		{
			Object* obj = ui->openGLWidget->GetObjectFactory()->FindObjectByName(x.changedTrees[i].name);
			obj->SetPosition(x.changedTrees[i].position);
			obj->SetEulerAngles(x.changedTrees[i].angle);
			obj->SetScale(x.changedTrees[i].scale);
		}
		break;
	}
	if (ui->openGLWidget->GetStack()->IsUndoEmpty())
	{
		ui->action_undo->setEnabled(false);
	}
	ui->openGLWidget->update();
}

void MainWindow::on_action_redo_triggered()
{
	ActionNode x = ui->openGLWidget->GetStack()->PopFromRedo();
	switch (x.operation)
	{
	case ActionNode::REMOVE:
		for (int i = 0; i < x.count(); i++)
		{
			//Object* obj = ui->openGLWidget->GetObjectFactory()->FindObjectByName(x.changedTrees[i].name);
			ui->openGLWidget->GetObjectFactory()->RemoveObject(x.changedTrees[i].name);
		}
		break;
	case ActionNode::ADD:
		for (int i = 0; i < x.count(); i++)
		{
			Object* obj = new Object();
			if (obj->Load(TreeInfo(x.changedTrees[i].info)))
			{
				obj->setName(x.changedTrees[i].name);
				obj->SetPosition(x.changedTrees[i].position);
				obj->SetEulerAngles(x.changedTrees[i].angle);
				obj->SetScale(x.changedTrees[i].scale);
				ui->openGLWidget->GetObjectFactory()->AddObject(obj);
			}
		}
		break;
	case ActionNode::ALTER:
		for (int i = 0; i < x.count(); i++)
		{
			Object* obj = ui->openGLWidget->GetObjectFactory()->FindObjectByName(x.changedTrees[i].name);
			obj->SetPosition(x.changedTrees[i].position);
			obj->SetEulerAngles(x.changedTrees[i].angle);
			obj->SetScale(x.changedTrees[i].scale);
		}
		break;
	}
	if (ui->openGLWidget->GetStack()->IsRedoEmpty())
	{
		ui->action_redo->setEnabled(false);
	}
	ui->openGLWidget->update();
}
/*void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    //qDebug() << index.data().toString();
    //QSqlTableModel model2(ui->tableView);
    //QSqlDatabase db = QSqlDatabase::database("test", false);
    QSqlQueryModel *model2 = new QSqlQueryModel(ui->tableView);
    model2->setQuery(QString("select * from tree;"));
    //model2.setQuery(QString("select * from tree"));
    int row = ui->tableView->currentIndex().row();
    QSqlRecord record = model2->record(row);
    ui->treename->setText(record.value(2).toString());
    int row = ui->tableView->currentIndex().row();
    //ui->treename->setText();
    //qDebug() << row;


}*/
void MainWindow::on_treeView_clicked(const QModelIndex &index)
{

    /*QModelIndex row = ui->treeView->currentIndex();
    row = row.sibling(row.row(),0);
    QString t = ui->treeView->model()->itemData(row).values()[0].toString();
    //QSqlQueryModel *model2 = new QSqlQueryModel(ui->treeView);
    ui->treename->setText(t);*/

}

void MainWindow::on_pushed()
{
	ui->action_undo->setEnabled(true);
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{

    DBManager db;
    db.ConnectToDB();

    QModelIndex row = ui->treeView->currentIndex();
    row = row.sibling(row.row(),0);
    QString Treename = ui->treeView->model()->itemData(row).values()[0].toString();
    QString Modelname = db.FindMnameByTreeName(Treename);
    QString Modelpath = db.FindPatyByName(Treename);


	QString name = ui->openGLWidget->AddTree(TreeInfo(Modelname, Modelpath));
    ui->openGLWidget->update();
	ActionNode x;
	x.operation = ActionNode::ADD;
	Object* obj = ui->openGLWidget->GetObjectFactory()->FindObjectByName(name);
	x.changedTrees.push_back(TreeNode(name, TreeInfo(Modelname, Modelpath), obj->GetPosition(), obj->GetEulerAngles(), obj->GetScale()));
	ui->openGLWidget->GetStack()->PushToUndo(x);
}
