#ifndef MYWIDGET_H
#define MYWIDGET_H


#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QtGui>
#include "childwindow.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


namespace Ui {
    class MyWidget;
}
class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(ChildWindow *c = 0);
    bool saveImage(const QString &fileName, const char *fileFormat);
    QImage image;
    bool modified;


protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
    QPoint lastPoint;

signals:

public slots:
    void clearImage();

};

#endif // MYWIDGET_H
