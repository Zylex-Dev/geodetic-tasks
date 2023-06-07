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
#include <qcustomplot.h>


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

    void on_pushButton_Graph_clicked();

    void on_pushButton_Graph_Draw_clicked();

    void on_pushButton_Graph_Back_clicked();

    void on_pushButton_GraphResult_OK_clicked();

    void on_pushButton_GraphResult_Back_clicked();

    void on_spinBox_Graph_PointsValue_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

};


#endif // MAINWINDOW_H
