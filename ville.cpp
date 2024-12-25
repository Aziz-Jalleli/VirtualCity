
#include "ville.h"
#include "batiment.h"
#include "maison.h" // Si vous utilisez une classe Maison
#include <QString>
#include <vector>

using namespace std;

Ville::Ville(QObject* parent, QString nom, int budget, int population, int satisfaction, int eau, int electricite)
    : QObject(parent), nom(nom), budget(budget), population(population), satisfaction(satisfaction), eau(eau), electricite(electricite) {}

Ville::Ville(QObject* parent, QString nom, int budget, int population, int satisfaction)
    : QObject(parent), nom(nom), budget(budget), population(population), satisfaction(satisfaction), eau(0), electricite(0) {}

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
        eau += batiment.get_eau();
        electricite += batiment.get_elec();
    }
}

void Ville::CalculerSatisfaction() {
    satisfaction = 0;
    for (const auto &batiment : batiments) {
        satisfaction += batiment.get_satisfaction();
    }
}

void Ville::calculerPopulation() {
    population = 0;
    for (const auto &batiment : batiments) {
        const Maison *m = dynamic_cast<const Maison *>(&batiment);
        if (m) {
            population += m->get_habitant();
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

vector<Batiment> Ville::get_batiments() const{
    return batiments;
}
