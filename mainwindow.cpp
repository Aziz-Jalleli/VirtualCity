#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"maison.h"
#include"QMessageBox"

#include"afficherdetails.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Maison m1(1,"darhamma","maison",0,0,0,4,0);

    Afficherdetails afficherdetails(this);
    afficherdetails.setDetails(m1.getDetails());
    afficherdetails.exec();
    QMessageBox::information(this, "Object Created", "The Maison object has been successfully created.");
}

