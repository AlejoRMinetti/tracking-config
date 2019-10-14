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
#include "video/mainvideocapture.h"

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // openCV video habitaciones y configuracion
    int idVidCap = 0;
    for (int idDevice = 0; idDevice < 10; idDevice++) {
        if( MainVideoCapture::isCamIdOk(idDevice) ){
            //qDebug() << "Nueva camara: " << idVidCap +1 << " en id Devide: " << idDevice;
            mOpenCV_videoCapture[idVidCap] = new MainVideoCapture(idDevice,this);
            idVidCap ++;
        }
        if( idVidCap > 4-1)
            break;
    }
    //qDebug() << "Cantidad de camara: " << cams_activas;

    // openCV video on GUI
    //mOpenCV_videoCapture[0] = new MainVideoCapture(0, this);
    //mOpenCV_videoCapture[1] = new MainVideoCapture(2, this);
    connect(mOpenCV_videoCapture[0], &MainVideoCapture::newPixmapCapture,this,[&](){
        ui->opencvFrame->setPixmap(mOpenCV_videoCapture[0]->getAllDetections().scaled(320,240)); // mostrar imagen RGB
        // usando .scaled(ui->opencvFrame->width(),ui->opencvFrame->height()) se va agrandando la pantalla sola!
        ui->opencvFrame_3->setPixmap(mOpenCV_videoCapture[0]->getBinarioDetec().scaled(320,240));
        UpdateDetectParametros();
    });
    connect(mOpenCV_videoCapture[1], &MainVideoCapture::newPixmapCapture,this,[&](){
        ui->opencvFrame_2->setPixmap(mOpenCV_videoCapture[1]->getAllDetections().scaled(320,240)); // mostrar imagen // procesar y mostrar imagen HSV
        ui->opencvFrame_4->setPixmap(mOpenCV_videoCapture[1]->getBinarioDetec().scaled(320,240));
    });
    connect(mOpenCV_videoCapture[0], &MainVideoCapture::presenciaDetectada,this,[&](){
        ui->label_presencia->setText("Presencia!");
    });
    connect(mOpenCV_videoCapture[0], &MainVideoCapture::sinPresencia,this,[&](){
        ui->label_presencia->setText("Nada por aqui");
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

void MainWindow::on_addButton_clicked()
{
    // todo agregar nueva deteccion
    mOpenCV_videoCapture[0]->objects.push_back(
                mOpenCV_videoCapture[0]->setUpObject(
                ui->nameLineEdit->text().toStdString(),
                mOpenCV_videoCapture[0]->H_MIN,
                mOpenCV_videoCapture[0]->H_MAX,
                mOpenCV_videoCapture[0]->S_MIN,
                mOpenCV_videoCapture[0]->S_MAX,
                mOpenCV_videoCapture[0]->V_MIN,
                mOpenCV_videoCapture[0]->V_MAX));
    ui->nameLineEdit->clear();
}

void MainWindow::on_defaultButton_clicked()
{
    // todo guardar y reiniciar carga de deteccion
    ui->hminBox->setValue(0);
    ui->hmaxBox->setValue(255);
    ui->sminBox->setValue(0);
    ui->smaxBox->setValue(255);
    ui->vminBox->setValue(0);
    ui->vmaxBox->setValue(255);
}

////////// update de slicers
void MainWindow::UpdateDetectParametros(){
    // get parametros para creacion de deteccion de bordes
    mOpenCV_videoCapture[0]->H_MIN = ui->hminBox->text().toInt();
    mOpenCV_videoCapture[0]->H_MAX = ui->hmaxBox->text().toInt();
    mOpenCV_videoCapture[0]->S_MIN = ui->sminBox->text().toInt();
    mOpenCV_videoCapture[0]->S_MAX = ui->smaxBox->text().toInt();
    mOpenCV_videoCapture[0]->V_MIN = ui->vminBox->text().toInt();
    mOpenCV_videoCapture[0]->V_MAX = ui->vmaxBox->text().toInt();
}
