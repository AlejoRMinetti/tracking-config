#ifndef MYVIDEOCAPTURE_H
#define MYVIDEOCAPTURE_H

#include <QPixmap>
#include <QImage>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <iostream>

using namespace cv;
using namespace std;

class MyVideoCapture : public QThread
{
    Q_OBJECT
public:
    MyVideoCapture(int idDevice, QObject *parent = nullptr );
    QPixmap pixmap() const { return mPixmap; }
    QPixmap pixmapDif()const{ return mPixmapDif; }
    QPixmap pixmapDST()const{ return mPixmapDST; }
signals:
    void newPixmapCapture();
protected:
    void run();
    double largest_area;
    double largest_contour_index;
    Rect bounding_rect;
private:
    QPixmap mPixmap,mPixmapDif,mPixmapDST;
    Mat actFrame, antFrame, difFrame, kernel, dst;
    VideoCapture mVideoCap;
    QImage  cvMatToQImage( const Mat &inMat );
    QPixmap cvMatToQPixmap( const Mat &inMat );
};

#endif // MYVIDEOCAPTURE_H
