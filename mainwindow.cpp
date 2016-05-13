#include "mainwindow.h"
#include "mywidget.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <string>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sc = 0;
    cc = 0;
    tc = 0;
    childWindow = new ChildWindow(ui->mdiArea, this);
    childWindow->setAttribute(Qt::WA_DeleteOnClose);
    childWindow->setFixedHeight(200);
    childWindow->setFixedWidth(200);
    childWindow->showMaximized();

    connect(ui->clear_button, SIGNAL(clicked()),
            childWindow, SLOT(clearImage()));

    //n = network();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createChild(){}

void MainWindow::print()
{
    QString name = ui->path->text();
    name += (ui->square->isChecked() ? "s" + QString::number(sc) +
                                       ".bmp" : (ui->circle->isChecked() ? "c" + QString::number(cc) + ".bmp" : "t" +
                                                                           QString::number(tc) + ".bmp"));
    if(ui->square->isChecked()) sc++;
    else if(ui->circle->isChecked()) cc++;
    else tc++;

    childWindow->saveImage(name, "bmp");

    childWindow->clearImage();
}


void MainWindow::on_pushButton_clicked()
{

    n.train(7, 7, 7, ui->path->text().toStdString());
    ui->pushButton->setDisabled(true);

}

void MainWindow::on_openButton_2_clicked()
{
    childWindow->saveImage(ui->path->text() + "predict.bmp", "bmp");
    childWindow->clearImage();
    ui->ans->setText(QString::fromStdString(std::to_string(n.predict(ui->path->text().toStdString() + "predict.bmp"))));
}
