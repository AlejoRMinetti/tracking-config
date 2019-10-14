#include "myvideocapture.h"

MyVideoCapture::MyVideoCapture(int idDevice, QObject *parent )
    : QThread (parent), mVideoCap{idDevice}
{
}

void MyVideoCapture::run()
{
    if(mVideoCap.isOpened()){
        while (true) {
            mVideoCap >> actFrame;
            if(!actFrame.empty()){
                if(!antFrame.empty()){
                   subtract(actFrame,antFrame,difFrame);
                   threshold(difFrame, difFrame, 15,255,CV_THRESH_BINARY);
                   morphologyEx(difFrame, difFrame,CV_MOP_OPEN, kernel,cv::Point2i(-1,-1),1);
                   cvtColor(difFrame,difFrame,CV_BGR2GRAY);
                   mPixmapDif = cvMatToQPixmap(difFrame);

                   vector<vector<Point>> contours;
                   vector<Vec4i> hierarchy;
                   largest_area = 0;
                   largest_contour_index = 0;

                   findContours(difFrame, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
                   for (size_t i=0; i< contours.size(); i++) {
                       double a = contourArea(contours[i],false);
                       if( a > largest_area){
                           largest_area = a;
                           largest_contour_index = i;
                           bounding_rect = boundingRect(contours[i]);
                       }
                   }
                   dst = actFrame.clone();
                   Scalar color(255,255, 255);
                   drawContours(dst,contours, (int)largest_contour_index, color, CV_FILLED,  8, hierarchy);
                   rectangle(dst, bounding_rect, Scalar(0, 255, 0), 1, 8, 0);
                   mPixmapDST = cvMatToQPixmap(dst);

                }
                antFrame = actFrame.clone();
                mPixmap = cvMatToQPixmap(actFrame);
                emit newPixmapCapture();
            }
        }
    }
}

QImage  MyVideoCapture::cvMatToQImage( const Mat &inMat ){
      switch ( inMat.type() ){
         case CV_8UC4:
            {
                QImage image( inMat.data,inMat.cols, inMat.rows,
                       static_cast<int>(inMat.step),QImage::Format_ARGB32 );
                return image;
            }
         case CV_8UC3:
            {
                QImage image( inMat.data,inMat.cols, inMat.rows,
                       static_cast<int>(inMat.step),QImage::Format_RGB888 );
               return image.rgbSwapped();
            }

         case CV_8UC1:
            {
                QImage image( inMat.data,inMat.cols, inMat.rows,
                       static_cast<int>(inMat.step),QImage::Format_Grayscale8 );
                return image;
            }
         default:
            qDebug() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
      }
      return QImage();
}


QPixmap MyVideoCapture::cvMatToQPixmap( const cv::Mat &inMat ){
     return QPixmap::fromImage( cvMatToQImage( inMat ) );
 }
