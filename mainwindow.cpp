#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"maison.h"
#include"QMessageBox"
#include"afficherdetails.h"
#include"addhabitant.h"
#include "createmaison.h"
#include <QLineEdit>
#include <QSpinBox>
#include"createville.h"
#include<memory>
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
    if (!v1) {
        QMessageBox::warning(this, "No City", "Please create a city before adding habitants.");
        return;
    }
    // Open the CreateMaison dialog
    createmaison createDialog(this);

    // If the user accepts the dialog
    if (createDialog.exec() == QDialog::Accepted) {
        // Retrieve input values
        QString houseName = createDialog.findChild<QLineEdit*>("lineEdit")->text();
        int capacity = createDialog.findChild<QSpinBox*>("spinBox")->value();

        // Create a new Maison object
         m1 = std::make_shared<Maison>(1, houseName, capacity);

        if (v1) {
            v1->ajouterBatiment(m1);

        }

        // Display the details of the created Maison
        Afficherdetails afficherdetails(this);
        afficherdetails.setDetails(m1->getDetails());
        afficherdetails.exec();

        QMessageBox::information(this, "Maison Created", "The Maison object has been successfully created.");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if (!v1) {
        QMessageBox::warning(this, "No City", "Please create a city before adding habitants.");
        return;
    }
    // Create and display the custom dialog
    addhabitant dialog(this);
    QStringList houseNames;
    for (const auto& maison : v1->get_batiments()) {
        houseNames << maison->getname(); // Assuming `getName()` exists in `Maison`
    }
    dialog.populateHouses(houseNames);

    // Execute the dialog
    if (dialog.exec() == QDialog::Accepted) {
        int selectedIndex = dialog.getSelectedHouseIndex();
        int numHabitants = dialog.getHabitants();

        // Ensure a valid house is selected
        if (selectedIndex < 0 || selectedIndex >= v1->get_batiments().size()) {
            QMessageBox::warning(this, "Invalid Selection", "Please select a valid house.");
            return;
        }

        // Add habitants to the selected house
        auto selectedMaison = std::dynamic_pointer_cast<Maison>(v1->get_batiments()[selectedIndex]);
        selectedMaison->ajouterHabitants(numHabitants);

        // Show a confirmation message
        QMessageBox::information(this,
                                 "Habitants Added",
                                 QString("%1 habitants have been added to %2.\nCurrent inhabitants: %3")
                                     .arg(numHabitants)
                                     .arg(selectedMaison->getname())
                                     .arg(selectedMaison->get_habitant()));
    }
}



void MainWindow::on_pushButton_3_clicked()
{
    createville createDialog(this);

    if (createDialog.exec() == QDialog::Accepted) {
        // Retrieve input values
        QString VilleName = createDialog.findChild<QLineEdit*>("lineEdit")->text();

        // Retrieve and validate budget input
        QString budgetText = createDialog.findChild<QLineEdit*>("lineEdit_2")->text();
        bool ok;
        int Budget = budgetText.toInt(&ok);

        if (!ok) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for the budget.");
            return;
        }

        // Create the Ville object
        v1 = std::make_shared<Ville>(nullptr, VilleName, Budget);
    }
}



