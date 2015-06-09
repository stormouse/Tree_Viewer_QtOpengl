#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlTableModel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void connectDB();
    void queryDB();
    void keyPressEvent(QKeyEvent  *event);
    QSqlTableModel *model;
    ~MainWindow();
	void resizeEvent(QResizeEvent *event);

private slots:


    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    //void on_action_triggered();


    void on_pushButton_clicked();

    //void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
