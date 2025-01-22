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
#include "batimentgraphicsitem.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "graphicswindow.h"
#include "CityWindow.h"

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

        // Validate that houseName is not empty
        if (houseName.isEmpty()) {
            QMessageBox::warning(this, "Invalid Input", "House name cannot be empty.");
            return;
        }

        // Create a new Maison object
        m1 = std::make_shared<Maison>(1, houseName, capacity);

        // Ensure the object is properly added to the city (v1)
        if (v1) {
            v1->ajouterBatiment(m1);  // Add Maison to the city's building list
        }

        // Add the building (Maison) to the graphics window if available
        if (graphicsWindow) {
            graphicsWindow->addBuilding(houseName, "Maison");
        } else {
            QMessageBox::warning(this, "Error", "City layout window is not available.");
        }
        if (cityWindow) {
            cityWindow->createHouseInFrontOfCamera();
        } else {
            QMessageBox::warning(this, "Error", "City layout window is not available.");
        }

        QMessageBox::information(this, "Maison Created", "The Maison object has been successfully created.");
    }

    updateProgressBars();
}

void MainWindow::on_Ajouter_Habitant_clicked()
{
    if (!s1->get_ville()) {
        QMessageBox::warning(this, "No City", "Please create a city before adding habitants.");
        return;
    }

    // Create and display the custom dialog
    addhabitant dialog(this);
    QStringList houseNames;
    QList<std::shared_ptr<Maison>> maisonList;

    // Populate the list with names of valid Maison objects
    for (const auto& batiment : v1->get_batiments()) {
        if (auto maison = std::dynamic_pointer_cast<Maison>(batiment)) {  // Attempt to cast to Maison
            houseNames << maison->getname();  // Add the name of the valid Maison
            maisonList << maison;  // Store the actual Maison objects in the list
        }
    }

    if (houseNames.isEmpty()) {
        QMessageBox::warning(this, "No Houses", "There are no valid houses available.");
        return;
    }

    dialog.populateHouses(houseNames);

    // Execute the dialog
    if (dialog.exec() == QDialog::Accepted) {
        int selectedIndex = dialog.getSelectedHouseIndex();
        int numHabitants = dialog.getHabitants();

        // Ensure a valid house is selected
        if (selectedIndex < 0 || selectedIndex >= maisonList.size()) {
            QMessageBox::warning(this, "Invalid Selection", "Please select a valid house.");
            return;
        }

        // Get the selected Maison object from maisonList by index and add habitants
        auto selectedMaison = maisonList[selectedIndex];
        if (selectedMaison) {
            selectedMaison->ajouterHabitants(numHabitants);

            // Show a confirmation message
            QMessageBox::information(this,
                                     "Habitants Added",
                                     QString("%1 habitants have been added to %2.\nCurrent inhabitants: %3")
                                         .arg(numHabitants)
                                         .arg(selectedMaison->getname())
                                         .arg(selectedMaison->get_habitant()));
        } else {
            QMessageBox::warning(this, "Selection Error", "The selected house is not valid.");
        }
    }

    updateProgressBars();
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


        s1 = std::make_shared<Simulation>(std::make_shared<Ville>(nullptr, VilleName, Budget));
        v1 = s1->get_ville();

        QGraphicsScene *scene = new QGraphicsScene();
        scene->setSceneRect(0, 0, 800, 600);

        // Create the city layout (for example, a 5x5 grid)
        graphicsWindow = new GraphicsWindow(scene);
        graphicsWindow->createCityLayout(5, 5); // 5x5 grid of blocks

        // Display the window
        QGraphicsView *view = new QGraphicsView(scene);
        view->show();
        cityWindow = new CityWindow(v1, nullptr);
        cityWindow->show();

    }
    updateProgressBars();
}




void MainWindow::on_Create_Usine_clicked()
{
    if (!s1) {
        QMessageBox::warning(this, "No City", "Please create a city before adding habitants.");
        return;
    }
    createusine createDialog(this);

    // If the user accepts the dialog
    if (createDialog.exec() == QDialog::Accepted) {
        // Retrieve input values
        QString UsineName = createDialog.findChild<QLineEdit*>("lineEdit")->text();

        // Check if v1 is valid
        if (!v1) {
            QMessageBox::warning(this, "Error", "City object is not initialized.");
            return;
        }

        // Check for duplicate names in existing buildings
        bool alreadyExists = false;
        for (const auto& batiment : v1->get_batiments()) {
            if (batiment->getname() == UsineName) {
                alreadyExists = true;
                break;
            }
        }

        if (alreadyExists) {
            QMessageBox::warning(this, "Duplicate Usine", "An Usine with this name already exists.");
            return;
        }

        // Create a new Usine object
        u1 = std::make_shared<usine>(1, UsineName);

        // Add the new Usine to the city
        v1->ajouterBatiment(u1);

        // Update graphics window if available
        if (graphicsWindow) {
            graphicsWindow->addBuilding(UsineName, "Usine");
        } else {
            QMessageBox::warning(this, "Error", "City layout window is not available.");
        }
        if (cityWindow) {
            cityWindow->createFactoryInFrontOfCamera();
        } else {
            QMessageBox::warning(this, "Error", "City layout window is not available.");
        }


        QMessageBox::information(this, "Usine Created", "The Usine object has been successfully created.");
    }
    updateProgressBars();
}



void MainWindow::on_Produire_eau_clicked()
{
    if (!s1) {
        QMessageBox::warning(this, "No City", "Please create a city before adding habitants.");
        return;
    }

    // Create and display the custom dialog
    produireeau dialog(this);

    // Create a filtered list of Usine objects
    QStringList UsineNames;
    std::vector<std::shared_ptr<usine>> usineList;

    for (const auto& batiment : v1->get_batiments()) {
        if (batiment->gettype() == "Usine") {
            auto usineObj = std::dynamic_pointer_cast<usine>(batiment);
            if (usineObj) {
                usineList.push_back(usineObj);
                UsineNames << usineObj->getname();
            }
        }
    }

    // Populate the dialog with filtered Usine names
    dialog.populateUsines(UsineNames);

    // Execute the dialog
    if (dialog.exec() == QDialog::Accepted) {
        int selectedIndex = dialog.getSelectedUsineIndex();

        if (selectedIndex < 0 || selectedIndex >= usineList.size()) {
            QMessageBox::warning(this, "Invalid Selection", "Please select a valid Usine.");
            return;
        }

        auto selectedUsine = usineList[selectedIndex];
        selectedUsine->produire_eau();

        // Show a confirmation message
        QMessageBox::information(this,
                                 "Water Produced",
                                 QString("1360 water have been added to %1.\nCurrent water produced: %2")
                                     .arg(selectedUsine->getname())
                                     .arg(selectedUsine->geteau()));
    }
    updateProgressBars();
}

void MainWindow::on_pushButton_6_clicked()
{
    if (!s1) {
        QMessageBox::warning(this, "No City", "Please create a city before adding habitants.");
        return;
    }

    // Create and display the custom dialog
    produireelectricite dialog(this);
    QStringList UsineNames;
    std::vector<std::shared_ptr<usine>> usineList;

    // Filter the batiments to include only Usine objects
    for (const auto& batiment : v1->get_batiments()) {
        if (batiment->gettype() == "Usine") {
            auto usineObj = std::dynamic_pointer_cast<usine>(batiment);
            if (usineObj) {
                usineList.push_back(usineObj);
                UsineNames << usineObj->getname();
            }
        }
    }

    // Populate the dialog with the filtered Usine names
    dialog.populateUsines(UsineNames);

    // Execute the dialog
    if (dialog.exec() == QDialog::Accepted) {
        int selectedIndex = dialog.getSelectedUsineIndex();

        if (selectedIndex < 0 || selectedIndex >= usineList.size()) {
            QMessageBox::warning(this, "Invalid Selection", "Please select a valid Usine.");
            return;
        }

        auto selectedUsine = usineList[selectedIndex];
        selectedUsine->produire_elec();

        // Show a confirmation message
        QMessageBox::information(this,
                                 "Electricity Produced",
                                 QString("6000 electricity have been added to %1.\nCurrent electricity produced: %2")
                                     .arg(selectedUsine->getname())
                                     .arg(selectedUsine->getelectricite()));
    }
    updateProgressBars();
}

void MainWindow::on_Create_Parc_clicked()
{
    if (!s1) {
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
        if (cityWindow) {
            cityWindow->createParkInFrontOfCamera();
        } else {
            QMessageBox::warning(this, "Error", "City layout window is not available.");
        }

        if (graphicsWindow) {
            graphicsWindow->addBuilding(ParcName, "Parc");
        } else {
            QMessageBox::warning(this, "Error", "City layout window is not available.");
        }

        QMessageBox::information(this, "Parc Created", "The park has been successfully created.");
    }
    updateProgressBars();
}


void MainWindow::on_Ameliore_BienEtre_clicked()
{
    if (!s1) {
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
void MainWindow::updateProgressBars() {
    if (!s1) {
        // If no city is created, reset all progress bars to 0
        ui->Eau->setMaximum(1);
        ui->Eau->setValue(0);

        ui->Electricite->setMaximum(1);
        ui->Electricite->setValue(0);

        ui->satisfaction->setMaximum(1);
        ui->satisfaction->setValue(0);

        ui->Pollution->setMaximum(1);
        ui->Pollution->setValue(0);
        return;
    }

    // Update Eau ProgressBar
    int maxEau = v1->get_Eau();               // Get the maximum water capacity
    int producedEau = v1->get_produced_eau(); // Get the current produced water

    ui->Eau->setMaximum(maxEau > 0 ? maxEau : 1); // Prevent division by 0
    ui->Eau->setValue(producedEau);

    // Update Electricite ProgressBar
    int maxElectricite = v1->get_Elec();                     // Get the maximum electricity capacity
    int producedElectricite = v1->get_produced_electricite(); // Get the current produced electricity

    ui->Electricite->setMaximum(maxElectricite > 0 ? maxElectricite : 1); // Prevent division by 0
    ui->Electricite->setValue(producedElectricite);

    //update Satisfaction ProgressBar

    int maxSatisfaction= v1->getSatisfaction();

    ui->satisfaction->setMaximum(250); // Prevent division by 0
    ui->satisfaction->setValue(maxSatisfaction);

    //update Pollution ProgressBar

    int maxPollution= v1->getPollution();

    ui->Pollution->setMaximum(150); // Prevent division by 0
    ui->Pollution->setValue(maxPollution);

    //update Population ProgressBar

    int maxPopulation= v1->getPopulation();

    ui->Population->display(maxPopulation);


    // Optional: Update labels or log debug messages if needed
    qDebug() << "Updated Progress Bars:";
    qDebug() << "Eau -> Max:" << maxEau << " Produced:" << producedEau;
    qDebug() << "Electricite -> Max:" << maxElectricite << " Produced:" << producedElectricite;
}


void MainWindow::on_SimulateEvent_clicked()
{
    if (!s1) {
        QMessageBox::warning(this, "No City", "Please create a city before adding a park.");
        return;
    }
    QString Message=s1->declencherEvenement();
    QMessageBox::information(this,"Event" ,Message);
    if (Message.contains("tempête de neige", Qt::CaseInsensitive)) {
        ui->Produire_eau->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
    }
    updateProgressBars();

}
