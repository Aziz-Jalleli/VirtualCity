
#include "ville.h"
#include "batiment.h"
#include "maison.h" // Si vous utilisez une classe Maison
#include <QString>
#include <vector>

using namespace std;

Ville::Ville(QObject* parent, QString nom, int budget)
    : QObject(parent), nom(nom), budget(budget), population(0), satisfaction(0), eau(0), electricite(0) {}

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



void Ville::calculerConsommationTotale() {
    eau = 0;
    electricite = 0;
    for (const auto &batiment : batiments) {
        eau += batiment->get_eau();
        electricite += batiment->get_elec();
    }
}

void Ville::CalculerSatisfaction() {
    satisfaction = 0;
    for (const auto &batiment : batiments) {
        satisfaction += batiment->get_satisfaction();
    }
}

void Ville::calculerPopulation() {
    population = 0;

    for (const auto& batiment : batiments) {
        std::shared_ptr<Maison> maison = std::dynamic_pointer_cast<Maison>(batiment);
        if (maison) {
            population += maison->get_habitant();
        }
    }
}

int Ville::get_Elec() const {
    return electricite;
}

void Ville::set_Elec(int newelec) {
    electricite = newelec;
}

int Ville::get_satisfaction() const {
    return satisfaction;
}

void Ville::set_satisfaction(int newv) {
    satisfaction = newv;
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
