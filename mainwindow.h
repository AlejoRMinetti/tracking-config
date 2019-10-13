#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "video/mainvideocapture.h"

namespace Ui {
class MainWindow;
}

class MainVideoCapture;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_defaultButton_clicked();
    ////////// update de slicers
    void UpdateDetectParametros();

private:
    Ui::MainWindow *ui;
    MainVideoCapture *mOpenCV_videoCapture;
};

#endif // MAINWINDOW_H
