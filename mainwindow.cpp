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
#include"createusine.h"
#include"produireeau.h"
#include"produireelectricite.h"
#include"createparc.h"
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

void MainWindow::on_Create_Maison_clicked()
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


void MainWindow::on_Ajouter_Habitant_clicked()
{
    if (!v1) {
        QMessageBox::warning(this, "No City", "Please create a city before adding habitants.");
        return;
    }
    // Create and display the custom dialog
    addhabitant dialog(this);
    QStringList houseNames;
    for (const auto& maison : v1->get_batiments()) {
        if(maison->gettype()=="Maison"){
            houseNames << maison->getname(); // Assuming `getName()` exists in `Maison`
    }
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



void MainWindow::on_Create_Ville_clicked()
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




void MainWindow::on_Create_Usine_clicked()
{
    if (!v1) {
        QMessageBox::warning(this, "No City", "Please create a city before adding habitants.");
        return;
    }
    createusine createDialog(this);

    // If the user accepts the dialog
    if (createDialog.exec() == QDialog::Accepted) {
        // Retrieve input values
        QString UsineName = createDialog.findChild<QLineEdit*>("lineEdit")->text();


        // Create a new Maison object
        u1 = std::make_shared<usine>(1, UsineName);

        if (v1) {
            v1->ajouterBatiment(u1);

        }

        // Display the details of the created Maison
        Afficherdetails afficherdetails(this);
        afficherdetails.setDetails(u1->getDetails());
        afficherdetails.exec();

        QMessageBox::information(this, "Usine Created", "The Usine object has been successfully created.");
    }
}


void MainWindow::on_Produire_eau_clicked()
{
    if (!v1) {
        QMessageBox::warning(this, "No City", "Please create a city before adding habitants.");
        return;
    }
    // Create and display the custom dialog
    produireeau dialog(this);
    QStringList UsineNames;
    for (const auto& Usine : v1->get_batiments()) {
        if(Usine->gettype()=="Usine"){
            UsineNames << Usine->getname(); // Assuming `getName()` exists in `Maison`
        }
    }
    dialog.populateUsines(UsineNames);

    // Execute the dialog
    if (dialog.exec() == QDialog::Accepted) {
        int selectedIndex = dialog.getSelectedUsineIndex();


        // Ensure a valid house is selected
        if (selectedIndex < 0 || selectedIndex >= v1->get_batiments().size()) {
            QMessageBox::warning(this, "Invalid Selection", "Please select a valid Usine.");
            return;
        }

        // Add habitants to the selected house
        auto selectedUsine = std::dynamic_pointer_cast<usine>(v1->get_batiments()[selectedIndex]);
        selectedUsine->produire_eau();

        // Show a confirmation message
        QMessageBox::information(this,
                                 "water produced",
                                 QString(" 1360 water have been added to %2.\nCurrent waterproduced: %3")
                                     .arg(selectedUsine->getname())
                                     .arg(selectedUsine->geteau()));
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    if (!v1) {
        QMessageBox::warning(this, "No City", "Please create a city before adding habitants.");
        return;
    }
    // Create and display the custom dialog
    produireelectricite dialog(this);
    QStringList UsineNames;
    for (const auto& Usine : v1->get_batiments()) {
        if(Usine->gettype()=="Usine"){
            UsineNames << Usine->getname(); // Assuming `getName()` exists in `Maison`
        }
    }
    dialog.populateUsines(UsineNames);

    // Execute the dialog
    if (dialog.exec() == QDialog::Accepted) {
        int selectedIndex = dialog.getSelectedUsineIndex();


        // Ensure a valid house is selected
        if (selectedIndex < 0 || selectedIndex >= v1->get_batiments().size()) {
            QMessageBox::warning(this, "Invalid Selection", "Please select a valid Usine.");
            return;
        }

        // Add habitants to the selected house
        auto selectedUsine = std::dynamic_pointer_cast<usine>(v1->get_batiments()[selectedIndex]);
        selectedUsine->produire_elec();

        // Show a confirmation message
        QMessageBox::information(this,
                                 "water produced",
                                 QString(" 6000 water have been added to %2.\nCurrent waterproduced: %3")
                                     .arg(selectedUsine->getname())
                                     .arg(selectedUsine->getelectricite()));
    }
}


void MainWindow::on_Create_Parc_clicked()
{
    if (!v1) {
        QMessageBox::warning(this, "No City", "Please create a city before adding a park.");
        return;
    }

    // Check if a park already exists (you need to define this check depending on your class structure)
    bool parcExists = false;
    for (const auto& batiment : v1->get_batiments()) {
        if (std::dynamic_pointer_cast<parc>(batiment)) {
            parcExists = true;
            break;
        }
    }

    if (parcExists) {
        QMessageBox::information(this, "Park Exists", "A park has already been created.");
        return;
    }

    createparc createDialog(this);

    // If the user accepts the dialog
    if (createDialog.exec() == QDialog::Accepted) {
        // Retrieve input values
        QString ParcName = createDialog.findChild<QLineEdit*>("lineEdit")->text();
        QString SurfaceText = createDialog.findChild<QLineEdit*>("lineEdit_2")->text();

        bool ok;
        float Surface = SurfaceText.toFloat(&ok);

        if (!ok) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid float for the surface.");
            return;
        }

        // Create a new Parc object
        auto p1 = std::make_shared<parc>(1, ParcName, Surface);

        if (v1) {
            v1->ajouterBatiment(p1);
        }

        // Display the details of the created Parc
        Afficherdetails afficherdetails(this);
        afficherdetails.setDetails(p1->getDetails());
        afficherdetails.exec();

        QMessageBox::information(this, "Parc Created", "The park has been successfully created.");
    }
}


void MainWindow::on_Ameliore_BienEtre_clicked()
{
    if (!v1) {
        QMessageBox::warning(this, "No City", "Please create a city first.");
        return;
    }

    bool foundParc = false;

    for (const auto& Parc : v1->get_batiments()) {
        qDebug() << "Checking building type:" << Parc->gettype();
        if (Parc->gettype() == "Parc") {
            auto p = std::dynamic_pointer_cast<parc>(Parc);
            if (p) {
                qDebug() << "Found Parc: " << p->getname();
                p->ameliorerBienEtre();
                QMessageBox::information(this, "Bien-être amélioré",
                                         QString("5% de bien-être ajoutés. Bien-être actuel : %1")
                                             .arg(p->get_effetbienetre()));
                foundParc = true;
                break;
            }
        }
    }

    if (!foundParc) {
        QMessageBox::information(this, "No Parcs Created", "Create a parc before.");
    }
}
