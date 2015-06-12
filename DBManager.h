#ifndef DBMANAGER_H
#define DBMANAGER_H

#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QSqlTableModel>
#include<QSqlQuery>
#include<QSqlRecord>
#include<QSqlError.h>
#include<QDir.h>
class DBManager
{
private:
	QSqlDatabase db;
public:
	bool ConnectToDB()
	{
		db = QSqlDatabase::database("test", false);
		//if (!db.isValid())
		//{
			db = QSqlDatabase::addDatabase("QODBC", "test");
			QString path = QDir().currentPath();
			db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=" + path + "\\TreesModel.mdb");
			if (db.open())
				return true;
			else
			{
				qDebug() << db.lastError().text() << endl;
				return false;
			}
		//}
		//else return true;
	}
	QString FindPathByTreeName(QString name)
	{
		db = QSqlDatabase::database("test", false);
		QString sqlcmd = "Select Mpath From Model Where Mname=\'"+name+"\'";
		QSqlQuery query = db.exec(sqlcmd);
		if (query.next())
		{
			return query.value(0).toString();
		}
		else return "";
	}
	
};

#endif