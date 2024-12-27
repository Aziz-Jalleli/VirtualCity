#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"maison.h"
#include"QMessageBox"
#include"afficherdetails.h"
#include"addhabitant.h"
#include "createmaison.h"
#include <QLineEdit>
#include <QSpinBox>
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
    // Open the CreateMaison dialog
    createmaison createDialog(this);

    // If the user accepts the dialog
    if (createDialog.exec() == QDialog::Accepted) {
        // Retrieve input values
        QString houseName = createDialog.findChild<QLineEdit*>("lineEdit")->text();
        int capacity = createDialog.findChild<QSpinBox*>("spinBox")->value();

        // Create a new Maison object
        m1 = std::make_unique<Maison>(1, houseName, capacity);

        // Display the details of the created Maison
        Afficherdetails afficherdetails(this);
        afficherdetails.setDetails(m1->getDetails());
        afficherdetails.exec();

        QMessageBox::information(this, "Maison Created", "The Maison object has been successfully created.");
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
        m1->ajouterHabitants(numHabitants);

        // Display a confirmation message
        QMessageBox::information(this,
                                 tr("Habitants Added"),
                                 tr("%1 habitants have been added.\nCurrent inhabitants: %2")
                                     .arg(numHabitants)
                                     .arg(m1->get_habitant()));
    }
}

