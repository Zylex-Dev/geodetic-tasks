#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QtWidgets>
#include <cmath>
#include <qmath.h>
#include <QIntValidator>
#include <QValidator>
#include <QPalette>
#include <QMessageBox>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    double Xb;
//    double Yb;

private slots:

// кнопки

    void on_pushButton_DirectTask_clicked();

    void on_pushButton_ReverseTask_clicked();

    void on_pushButton_DirectBack_clicked();

    void on_pushButton_DirectCalculate_clicked();

    void on_pushButton_DirectResultBack_clicked();

    void on_pushButton_DirectResultOK_clicked();

    void on_pushButton_ReverseBack_clicked();

    void on_pushButton_ReverseCalculate_clicked();

    void on_pushButton_ReverseResultBack_clicked();

    void on_pushButton_ReverseResultOK_clicked();

// строчки (лайн эдиты)



// спин боксы

    void on_spinBox_DirectDegrees_valueChanged(int arg1);

    void on_spinBox_DirectMinutes_valueChanged(int arg1);

    void on_spinBox_DirectSeconds_valueChanged(int arg1);

    void setValidator();

private:
    Ui::MainWindow *ui;

//    void DirectTask(int Xa, int Ya, int L, int degrees, int minutes, int seconds,  Xb, int Yb)
//    {
//        double radians = (degrees + (minutes + seconds/60) /60) * M_PI / 180; // converting degreeses from spinbox to radians
//        //L = round((L * 100) / 100); // rounding to 2points after comma
//        //Xa = round((Xa * 100) / 100); // rounding to 2points after comma
//        //Ya = round((Ya * 100) / 100); // rounding to 2points after comma


//        double deltaX = L * cos(radians); // calculating deltaX
//        deltaX = round(deltaX * 100) / 100; // rounding to 2points after comma
//        double deltaY = L * sin(radians); // calcuating deltaY
//        deltaY = round(deltaY * 100) / 100; // rounding to 2points after comma

//        Xb = Xa + deltaX;
//        Xb = round(Xb * 100) / 100;
//        Yb = Ya + deltaY;
//        Yb = round(Yb * 100) / 100;

//    }

    void ReverseTask(int Xa, int Ya, int Xb, int Yb)
    {

    }

};


#endif // MAINWINDOW_H
