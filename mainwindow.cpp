#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::showMaximized(); // полноэкранный режим при запуске программы
    // при запуске программы всегда открывается первая страница Menu
    ui->stackedWidget->setCurrentIndex(0);
    this->setCentralWidget(ui->stackedWidget);

    // устанавливаем range у spinbox

    //direct
    ui->spinBox_DirectDegrees->setRange(0,360);
    ui->spinBox_DirectMinutes->setRange(0,60);
    ui->spinBox_DirectSeconds->setRange(0,60);
    //reverse
    ui->spinBox_ReverseResultDegrees->setRange(0,360);
    ui->spinBox_ReverseResultMinutes->setRange(0,60);
    ui->spinBox_ReverseResultSeconds->setRange(0,60);

    setValidator();
}

MainWindow::~MainWindow()
{
    delete ui;
}


   // Pushbuttons //

//MainMenu
void MainWindow::on_pushButton_DirectTask_clicked() // кнопка выбора решения прямой геодезической задачи В ГЛАВНОМ МЕНЮ
{
    ui->stackedWidget->setCurrentIndex(1); // 0 - Menu; 1 - Direct; 2 - DirectRes; 3 - Reverse;  4 - ReverseRes;

    ui->lineEdit_DirectValue_L->clear();
    ui->lineEdit_DirectCoordinates_X->clear();
    ui->lineEdit_DirectCoordinates_Y->clear();
    ui->spinBox_DirectDegrees->clear();
    ui->spinBox_DirectMinutes->clear();
    ui->spinBox_DirectSeconds->clear();
}

void MainWindow::on_pushButton_ReverseTask_clicked() // кнопка выбора решения обратной геодезической задачи В ГЛАВНОМ МЕНЮ
{
    ui->stackedWidget->setCurrentIndex(3);

    ui->lineEdit_ReverseResultValue_L->clear();
    ui->lineEdit_ReverseCoordinates_X_1->clear();
    ui->lineEdit_ReverseCoordinates_X_2->clear();
    ui->lineEdit_ReverseCoordinates_Y_1->clear();
    ui->lineEdit_ReverseCoordinates_Y_2->clear();
}

//DirectTask
void MainWindow::on_pushButton_DirectBack_clicked() // кнопка НАЗАД в прямой геодезической задаче
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_DirectCalculate_clicked() // кнопка РЕШИТЬ в прямой геодезической задаче
{
    ui->stackedWidget->setCurrentIndex(2);

    ui->lineEdit_DirectResultCoordinates_X->setReadOnly(true);
    ui->lineEdit_DirectResultCoordinates_Y->setReadOnly(true);

    double Xa = ui->lineEdit_DirectCoordinates_X->text().toDouble();
    double Ya = ui->lineEdit_DirectCoordinates_Y->text().toDouble();
    double L = ui->lineEdit_DirectValue_L->text().toDouble();

    int degrees = ui->spinBox_DirectDegrees->text().toInt();
    int minutes = ui->spinBox_DirectMinutes->text().toInt();
    int seconds = ui->spinBox_DirectSeconds->text().toInt();



    double radians = (degrees + (minutes + seconds/60) /60) * M_PI / 180; // converting degreeses from spinbox to radians


    double deltaX = L * cos(radians); // calculating deltaX

    double deltaY = L * sin(radians); // calcuating deltaY

    double Xb = Xa + deltaX;
    Xb = round(Xb * 100) / 100;
    double Yb = Ya + deltaY;
    Yb = round(Yb * 100) / 100;

    ui->lineEdit_DirectResultCoordinates_X->setText(QString::number(Xb,'f',2));
    ui->lineEdit_DirectResultCoordinates_Y->setText(QString::number(Yb,'f',2));



}

void MainWindow::on_pushButton_DirectResultBack_clicked() // кнпока НАЗАД в МЕНЮ РЕЗУЛЬТАТА в прямой геодезической задаче
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_DirectResultOK_clicked() // кнопка ОК в МЕНЮ РЕЗУЛЬТАТА в прямой геодезической задаче
{
    ui->stackedWidget->setCurrentIndex(0);

    ui->lineEdit_DirectValue_L->clear();

    ui->lineEdit_DirectCoordinates_X->clear();
    ui->lineEdit_DirectCoordinates_Y->clear();
    ui->spinBox_DirectDegrees->clear();
    ui->spinBox_DirectMinutes->clear();
    ui->spinBox_DirectSeconds->clear();
}


//ReverseTask
void MainWindow::on_pushButton_ReverseBack_clicked() // кнопка НАЗАД в обратной геодезической задаче
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_ReverseCalculate_clicked() // кнопка РАССЧИТАТЬ в обратной геодезической задаче
{
    ui->stackedWidget->setCurrentIndex(4);

    ui->lineEdit_ReverseResultValue_L->setReadOnly(true);
    ui->spinBox_ReverseResultDegrees->setReadOnly(true);
    ui->spinBox_ReverseResultMinutes->setReadOnly(true);
    ui->spinBox_ReverseResultSeconds->setReadOnly(true);
    ui->spinBox_ReverseResultDegrees->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_ReverseResultMinutes->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_ReverseResultSeconds->setButtonSymbols(QAbstractSpinBox::NoButtons);


    double Xa = ui->lineEdit_ReverseCoordinates_X_1->text().toDouble();
    double Ya = ui->lineEdit_ReverseCoordinates_Y_1->text().toDouble();
    double Xb = ui->lineEdit_ReverseCoordinates_X_2->text().toDouble();
    double Yb = ui->lineEdit_ReverseCoordinates_Y_2->text().toDouble();

    double deltaX = Xb - Xa;
    double deltaY = Yb - Ya;


    double radians = atan(abs(deltaY) / abs(deltaX)); // angle in radians

    double degree = radians * 180 / M_PI; // convert to degrees

    double intpart1; // degree
    double fractpart1 = modf(degree,&intpart1); //intpart1 - degrees

    double minutes = fractpart1 * 60;

    double intpart2;
    double fractpart2 = modf(minutes, &intpart2); //intpart2 - minutes

    double seconds = fractpart2 * 60;
    double intpart3;
    double fractpart3 = modf(seconds, &intpart3); //intpart3 - seconds


    if (deltaX > 0 and deltaY > 0)
    { // r = alpha

        double r = (((intpart1 * 60)) + intpart2 + (intpart3 / 60)); //minutes
        // convert to degrees/minutes/seconds
        double degr = r / 60;
        double int1;
        double fract1 = modf(degr, &int1); // int1 - degree result

        double minutes = fract1 * 60;

        double int2;
        double fract2 = modf(minutes, &int2); // int2 - minutes result

        double seconds = fract2 * 60;
        double int3;
        double fract3 = modf(seconds, &int3); // int3 - seconds result


        ui->spinBox_ReverseResultDegrees->setValue(int1);
        ui->spinBox_ReverseResultMinutes->setValue(int2);
        ui->spinBox_ReverseResultSeconds->setValue(int3);
    }
    if (deltaX < 0 and deltaY > 0)
    { // r = 180 - alpha

        double r = 180  *60 - (((intpart1 * 60)) + intpart2 + (intpart3 / 60)); //minutes
        // convert to degrees/minutes/seconds
        double degr = r / 60;
        double int1;
        double fract1 = modf(degr, &int1); // int1 - degree result

        double minutes = fract1 * 60;

        double int2;
        double fract2 = modf(minutes, &int2); // int2 - minutes result

        double seconds = fract2 * 60;
        double int3;
        double fract3 = modf(seconds, &int3); // int3 - seconds result


        ui->spinBox_ReverseResultDegrees->setValue(int1);
        ui->spinBox_ReverseResultMinutes->setValue(int2);
        ui->spinBox_ReverseResultSeconds->setValue(int3);
    }
    if (deltaX < 0 and deltaY < 0)
    { // r = alpha - 180

        double r = 180*60 + (((intpart1 * 60)) + intpart2 + (intpart3 / 60)); //minutes
        // convert to degrees/minutes/seconds
        double degr = r / 60;
        double int1;
        double fract1 = modf(degr, &int1); // int1 - degree result

        double minutes = fract1 * 60;

        double int2;
        double fract2 = modf(minutes, &int2); // int2 - minutes result

        double seconds = fract2 * 60;
        double int3;
        double fract3 = modf(seconds, &int3); // int3 - seconds result


        ui->spinBox_ReverseResultDegrees->setValue(int1);
        ui->spinBox_ReverseResultMinutes->setValue(int2);
        ui->spinBox_ReverseResultSeconds->setValue(int3);
    }
    if (deltaX > 0 and deltaY < 0)
    { // r = 360 - alpha

        double r = 360*60 - (((intpart1 * 60)) + intpart2 + (intpart3 / 60)); //minutes
        // convert to degrees/minutes/seconds
        double degr = r / 60;
        double int1;
        double fract1 = modf(degr, &int1); // int1 - degree result

        double minutes = fract1 * 60;

        double int2;
        double fract2 = modf(minutes, &int2); // int2 - minutes result

        double seconds = fract2 * 60;
        double int3;
        double fract3 = modf(seconds, &int3); // int3 - seconds result


        ui->spinBox_ReverseResultDegrees->setValue(int1);
        ui->spinBox_ReverseResultMinutes->setValue(int2);
        ui->spinBox_ReverseResultSeconds->setValue(int3);

    }

    // horizontal laying
    double L = sqrt((deltaX*deltaX) + (deltaY*deltaY));
    ui->lineEdit_ReverseResultValue_L->setText(QString::number(L,'f',2));














    //ui->lineEdit_ReverseResultValue_L->setText(QString::number(,'f',25)
}

void MainWindow::on_pushButton_ReverseResultBack_clicked() // кнопка НАЗАД в МЕНЮ РЕЗУЛЬТАТА в обратной геодезической задаче
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_ReverseResultOK_clicked() // кнпока ОК в МЕНЮ РЕЗУЛЬТАТА в обратной геодезической задаче
{
    ui->stackedWidget->setCurrentIndex(0);

    ui->lineEdit_ReverseResultValue_L->clear();
    ui->lineEdit_ReverseCoordinates_X_1->clear();
    ui->lineEdit_ReverseCoordinates_X_2->clear();
    ui->lineEdit_ReverseCoordinates_Y_1->clear();
    ui->lineEdit_ReverseCoordinates_Y_2->clear();
}




    // LineEdits //

//DirectTask

void MainWindow::setValidator()
{
    QRegExp regExpMinus("(-?\\d{0,1000}(\\.\\d{0,2})?)|(\\d{0,1000})");
    QValidator *validatorMinus = new QRegExpValidator(regExpMinus, this);
    ui->lineEdit_DirectCoordinates_X->setValidator(validatorMinus);
    ui->lineEdit_DirectCoordinates_Y->setValidator(validatorMinus);
    ui->lineEdit_ReverseCoordinates_X_1->setValidator(validatorMinus);
    ui->lineEdit_ReverseCoordinates_Y_1->setValidator(validatorMinus);
    ui->lineEdit_ReverseCoordinates_X_2->setValidator(validatorMinus);
    ui->lineEdit_ReverseCoordinates_Y_2->setValidator(validatorMinus);


    QRegExp regExp("\\d{0,1000}(\\.\\d{0,2})?");
    QValidator *validator = new QRegExpValidator(regExp, ui->lineEdit_DirectValue_L);
    ui->lineEdit_DirectValue_L->setValidator(validator);
    ui->lineEdit_ReverseResultValue_L->setValidator(validator);


}



    // SpinBoxes //

//DirectTask
void MainWindow::on_spinBox_DirectDegrees_valueChanged(int arg1)
{
    if (arg1 == 360)
    {
        ui->spinBox_DirectMinutes->setValue(0);
        ui->spinBox_DirectMinutes->setReadOnly(true);

        ui->spinBox_DirectSeconds->setValue(0);
        ui->spinBox_DirectSeconds->setReadOnly(true);
    }
    else
    {
        ui->spinBox_DirectMinutes->setReadOnly(false);
        ui->spinBox_DirectSeconds->setReadOnly(false);
    }
}

void MainWindow::on_spinBox_DirectMinutes_valueChanged(int arg1)
{
    if (arg1 == 60)
    {
        int arg = ui->spinBox_DirectDegrees->value();
        ui->spinBox_DirectDegrees->setValue(arg + 1);
        ui->spinBox_DirectMinutes->setValue(0);
    }
}

void MainWindow::on_spinBox_DirectSeconds_valueChanged(int arg1)
{
    if (arg1 == 60)
    {
        int arg = ui->spinBox_DirectMinutes->value();
        ui->spinBox_DirectMinutes->setValue(arg + 1);
        ui->spinBox_DirectSeconds->setValue(0);
    }
}

