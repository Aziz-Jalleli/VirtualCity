#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"maison.h"
#include"QMessageBox"
#include"afficherdetails.h"
#include"addhabitant.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m1(1, "darhamma", 4)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Afficherdetails afficherdetails(this);
    afficherdetails.setDetails(m1.getDetails());
    afficherdetails.exec();
    QMessageBox::information(this, "Object Created", "The Maison object has been successfully created.");
}


void MainWindow::on_pushButton_2_clicked()
{
    // Create and display the custom dialog
    addhabitant dialog(this);

    // Show the dialog and check if the user clicked "OK"
    if (dialog.exec() == QDialog::Accepted) {
        // Retrieve the number of habitants from the dialog
        int numHabitants = dialog.getHabitants();

        // Add habitants to the Maison object
        m1.ajouterHabitants(numHabitants);

        // Display a confirmation message
        QMessageBox::information(this,
                                 tr("Habitants Added"),
                                 tr("%1 habitants have been added.\nCurrent inhabitants: %2")
                                     .arg(numHabitants)
                                     .arg(m1.get_habitant()));
    }
}

