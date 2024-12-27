#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"maison.h"
#include"QMessageBox"
#include"afficherdetails.h"
#include"addhabitant.h"
#include "createmaison.h"
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
    createmaison createMasionDialog(this);

    if (createMasionDialog.exec() == QDialog::Accepted) {
        // Create a new Maison object with data from the dialog
        m1 = createMasionDialog.createMaison();
        Afficherdetails afficherdetails(this);
        afficherdetails.setDetails(m1.getDetails());
        afficherdetails.exec();

        // Optionally, store the newMaison in a list, display its details, or perform other actions
        QMessageBox::information(this, "Object Created", "The Maison object has been successfully created.");

        // You can perform other actions with newMaison, e.g., add it to a list of maisons
        // maisonsList.append(newMaison);
    }
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

