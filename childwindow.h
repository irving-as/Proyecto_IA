#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H
//#include "mywidget.h"
#include <QtGui>
#include <QWidget>
#include <QMdiSubWindow>
//#include "mainwindow.h"
#include <QDebug>

class MyWidget;
class MainWindow;

namespace Ui {
    class ChildWindow;
}

class ChildWindow : public QMdiSubWindow
{
    Q_OBJECT


public:
    explicit ChildWindow(QWidget *parent = 0, MainWindow *m = 0);
    ~ChildWindow();
    bool saveImage(const QString &fileName, const char *fileFormat);

private:
    MyWidget *myWidget;

public slots:
    void clearImage();
};

#endif // CHILDWINDOW_H
