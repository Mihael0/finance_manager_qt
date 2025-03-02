#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "excel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->startOfCurrentMonth->setFrame(false);
    _SetAppTimeToStartOfMonth();
    _InitializeCurrentMonth();
    ui->startOfCurrentMonth->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
}

void MainWindow::_InitializeCurrentMonth(void){
    if(ui){
        ui->currentMonth->setFrame(false);
        ui->currentMonth->setText(_GetCurrentTime().toString("dd-MM-yyyy"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dailyExpenses_returnPressed()
{
    // CreateNewExcelBook();
    // libxl:: Book* book = xlCreateBook();
    // if(book){
    //     QString filepath = "../data/" + _GetCurrentTime().toString("MM-yyyy") + ".xls";
    //     QByteArray ba_filepath = filepath.toLocal8Bit();
    //     const char *c_filepath = ba_filepath.data();
    //     // Check if an excel sheet of the given month exists.
    //     if(book->load(c_filepath)){
    //         // what a time to be alive.
    //         int a = 5;
    //     }else{
    //         int b = 10;
    //         // what a time to not be alive.
    //     }
    // }

}

void MainWindow::on_nextDay_clicked()
{
    // Increment the current day by 1.
    _IncrementDayOfLocalAppTime();
    ui->startOfCurrentMonth->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
}


void MainWindow::on_previousDay_clicked()
{
    // Decrement the current day by 1.
    _DecrementDayOfLocalAppTime();
    ui->startOfCurrentMonth->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
}

