//#-------------------------------------------------
//#
//# Project created by QtCreator 2016-05-30T18:42:28
//# Author original: Nauroze Hoath
//#

//  Tutorial:
//  https://hetpro-store.com/TUTORIALES/category/programacion/opencv/
//  https://www.opencv-srf.com/2010/09/object-detection-using-color-seperation.html

//  Version adaptada para TPO Info2 por
//  Alejo R Minetti
//  David Ochoa
//#-------------------------------------------------

#include "video/camaraConfig.h"
// error ui por no crear la ventana desde Qt (ui from class)
#include "ui_camaraConfig.h"
#include "myvideocapture.h"

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // openCV video on GUI
    mOpenCV_videoCapture[0] = new MyVideoCapture(0,this);
    mOpenCV_videoCapture[1] = new MyVideoCapture(2,this);

    connect(mOpenCV_videoCapture[0], &MyVideoCapture::newPixmapCapture,this,[&](){
        ui->opencvFrame_1->setPixmap(mOpenCV_videoCapture[0]->pixmap().scaled(320,240)); // mostrar imagen RGB
        // usando .scaled(ui->opencvFrame->width(),ui->opencvFrame->height()) se va agrandando la pantalla sola!
        ui->opencvFrame_3->setPixmap(mOpenCV_videoCapture[0]->pixmapDST().scaled(320,240));
    });

    connect(mOpenCV_videoCapture[1], &MyVideoCapture::newPixmapCapture,this,[&](){
        ui->opencvFrame_2->setPixmap(mOpenCV_videoCapture[1]->pixmap().scaled(320,240)); // mostrar imagen RGB
        // usando .scaled(ui->opencvFrame->width(),ui->opencvFrame->height()) se va agrandando la pantalla sola!
        ui->opencvFrame_4->setPixmap(mOpenCV_videoCapture[1]->pixmapDST().scaled(320,240));
    });

    // arraque desde el inicio las capturas
    mOpenCV_videoCapture[0]->start(QThread::HighPriority);
    mOpenCV_videoCapture[1]->start(QThread::HighPriority);
}

MainWindow::~MainWindow()
{
    delete ui;
    //mOpenCV_videoCapture->terminate();
    //mOpenCV_videoCapture->quit();
}

