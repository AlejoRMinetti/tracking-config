//#-------------------------------------------------
//#
//# Project created by QtCreator 2016-05-30T18:42:28
//# Author: Nauroze Hoath
//#
//#-------------------------------------------------


#include "video/camaraConfig.h"
#include <QApplication>


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    //w.Start(); // todo como thread en MainVideoCapture

    return a.exec();
}


