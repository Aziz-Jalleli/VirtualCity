
#include "ville.h"
#include "batiment.h"
#include "maison.h" // Si vous utilisez une classe Maison
#include <QString>
#include <vector>
#include"usine.h"

using namespace std;

Ville::Ville(QObject* parent, QString nom, int budget)
    : QObject(parent), nom(nom), budget(budget), population(0), satisfaction(0), eau(0), electricite(0),produced_eau(0),produced_electricite(0) {}
Ville::Ville(QGraphicsScene* scene)
    : scene(scene) {}
Ville& Ville::operator=(const Ville& other) {
    if (this == &other) {
        return *this;  // Avoid self-assignment
    }

    // Copy the data from 'other' to 'this'
    this->nom = other.nom;
    this->budget = other.budget;
    this->population = other.population;
    this->satisfaction = other.satisfaction;
    this->eau = other.eau;
    this->electricite = other.electricite;

    // Deep copy for batiments if needed
    this->batiments = other.batiments;

    return *this;  // Return the current object
}




int Ville::getSatisfaction() {
    for (const auto &batiment : batiments) {
        satisfaction += batiment->get_satisfaction();
    }
    return satisfaction;
}

int Ville::getPopulation() {

    for (const auto& batiment : batiments) {
        std::shared_ptr<Maison> maison = std::dynamic_pointer_cast<Maison>(batiment);
        if (maison) {
            population += maison->get_habitant();
        }
    }
    return population;
}

int Ville::get_produced_eau(){
    produced_eau = 0;
    for (const auto& batiment : batiments) {
        std::shared_ptr<usine> Usine = std::dynamic_pointer_cast<usine>(batiment);
        if (Usine) {
            produced_eau += Usine->geteau();
        }
    }
    return produced_eau;
}
int Ville::get_produced_electricite(){
    produced_electricite = 0;
    for (const auto& batiment : batiments) {
        std::shared_ptr<usine> Usine = std::dynamic_pointer_cast<usine>(batiment);
        if (Usine) {
            produced_electricite += Usine->getelectricite();
        }
    }
    return produced_electricite;
}

int Ville::get_Elec()  {
    electricite=0;
    for (const auto &batiment : batiments) {
        electricite += batiment->get_elec();
    }
    return electricite;
}
int Ville::get_Eau()  {
    eau=0;
    for (const auto &batiment : batiments) {
        eau += batiment->get_eau();
    }
    return eau;
}


vector<std::shared_ptr<Batiment>> Ville::get_batiments() const {
    return batiments;
}

void Ville::ajouterBatiment(shared_ptr<Batiment> b) {
    batiments.push_back(b);
}
void Ville::supprimerBatiment(int id) {
    auto it = batiments.begin();
    while (it != batiments.end() && (*it)->get_id() != id) {
        ++it;
    }
    if (it != batiments.end()) {
        batiments.erase(it);
    }
}
