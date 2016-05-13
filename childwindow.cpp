
#include "childwindow.h"

#include <QMdiSubWindow>

#include "mywidget.h"

ChildWindow::ChildWindow(QWidget *parent, MainWindow *m) :
  QMdiSubWindow(parent)
{
    myWidget = new MyWidget(this);
    this->setWidget(myWidget);
}

ChildWindow::~ChildWindow()
{
    myWidget->~MyWidget();
}

void ChildWindow::clearImage()
{
    myWidget->image.fill(qRgb(255, 255, 255));
    myWidget->modified = true;
    myWidget->update();
}

bool ChildWindow::saveImage(const QString &fileName, const char *fileFormat)
{
   return myWidget->saveImage(fileName, fileFormat);
}
