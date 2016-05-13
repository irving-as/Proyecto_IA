#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "mywidget.h"
#include "childwindow.h"
#include "network.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ChildWindow *childWindow;
    int sc;
    int cc;
    int tc;
    network n;

public slots:
    void createChild();
    void print();
private slots:
    void on_pushButton_clicked();
    void on_openButton_2_clicked();
};




#endif // MAINWINDOW_H
