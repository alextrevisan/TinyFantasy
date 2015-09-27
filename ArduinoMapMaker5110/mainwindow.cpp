#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QFileDialog>
#include <QStandardPaths>
#include <QPixmap>


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

void MainWindow::on_selectFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).at(0),
        tr("Image Files (*.png *.jpg *.bmp)"));
    ui->filename->setText(fileName);
}

void MainWindow::on_pushButton_clicked()
{
    QImage image(ui->filename->text());
    QByteArray array;
    array.resize(ui->sizeX->value()*ui->sizeY->value()/8);
    for(int i = 0; i< array.size();++i)
    {
        array[i] = 0;
    }
    for(int x = 0; x < (int)image.width()/ui->sizeX->value();++x)
    {
        for(int y = 0; y < (int)image.height()/ui->sizeY->value();++y)
        {
            QPixmap tmp = QPixmap::fromImage(image);
            int startx = x*ui->sizeX->value();
            int starty = y*ui->sizeY->value();
            QPixmap tile = tmp.copy(startx,starty,startx+ui->sizeX->value(),starty+ui->sizeY->value());
            for(int tilex = 0; tilex < ui->sizeX->value();++tilex)
            {
                for(int tiley = 0; tiley < ui->sizeY->value();++tiley)
                {
                    int value = (tile.toImage().pixel(tilex,tiley)==qRgb(0,0,0))?1:0;
                    char bank = tiley / 8;
                    char bitMask = 1 << (tiley % 8);
                    char &byte = array.data()[(ui->sizeX->value() * bank) + tilex];
                    if (value)
                        byte |= bitMask;
                    else
                        byte &= ~bitMask;
                }
            }
            tile.save(QString("m%1x%2.png").arg(x).arg(y));
            QFile binfile(QString("m%1x%2.bin").arg(x).arg(y));
            binfile.open(QFile::WriteOnly);
            binfile.write(array);
            binfile.close();
        }
    }
}
