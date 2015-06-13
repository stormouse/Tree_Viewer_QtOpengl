#include "newfrom.h"
#include "ui_newfrom.h"
#include<QFileDialog>
NewFrom::NewFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewFrom)
{
    ui->setupUi(this);

    resize(800,600);

        this->image = new QImage();

    connect(ui->OpenImageBtn,SIGNAL(clicked()), this, SLOT(on_slotOpenImage_triggered()));
}
void NewFrom::on_slotOpenImage_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, "open image file",
                ".",
                "Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
    if(fileName != "")
    {
        ui->select->setText(fileName);
        if(image->load(fileName))
        {
            ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
             ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


            QGraphicsScene *scene = new QGraphicsScene;
            QPixmap map = QPixmap::fromImage(*image);




            QPixmap sized = map.scaled(
               QSize(ui->graphicsView->width(),
                 ui->graphicsView->height()),
               Qt::KeepAspectRatio);


             scene->addPixmap(sized);


            ui->graphicsView->setScene(scene);

            ui->graphicsView->show();
        }
    }
}
NewFrom::~NewFrom()
{
    delete image;
    delete ui;
}

/*void NewFrom::on_pushButton_3_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open"), ".", tr("Image Files(*.jpg *.png)"));

}*/

void NewFrom::on_pushButton_3_clicked()
{
    QString newpath = QFileDialog::getExistingDirectory();
    ui->savePos->setText(newpath);
}
