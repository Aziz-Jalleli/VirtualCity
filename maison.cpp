#include "maison.h"
#include<iostream>
#include<Qstring>
using namespace std;

Maison::Maison() : Batiment(nullptr, 0, "", "Maison", 0, 1000, 10) {
    this->capaciteHabitants=0;
    this->habitantsActuels=0;

}
Maison::Maison(int id,QString nom,int capaciteHabitants) : Batiment(nullptr, id, nom, "Maison", 0, 1000, 10) {
    this->capaciteHabitants=capaciteHabitants;
    this->habitantsActuels=0;

}
void Maison::ajouterHabitants(int nb){
    int tmp= habitantsActuels+nb;
    if (tmp <capaciteHabitants){
        this->habitantsActuels =tmp;

    }else{
        this->habitantsActuels = this->capaciteHabitants;
    }
    Maison::calculerImpactRessources();

}
void Maison::retirerHabitants(int nb){
    int tmp= habitantsActuels-nb;
    if (tmp <=0){
        this->habitantsActuels =0;

    }else{
        this->habitantsActuels = tmp;
    }
    Maison::calculerImpactRessources();

}
void Maison::afficherDetails() {
    Batiment::afficherDetails();

    cout << capaciteHabitants <<endl;
    cout << habitantsActuels <<endl;
}
void Maison::calculerImpactRessources() {
    cons_eau=habitantsActuels*360;

}
int Maison::get_habitant() const{
    return habitantsActuels;
}
QString Maison:: getDetails() const {
    return Batiment::getDetails() +
           QString("\nCapacity: %1\nCurrent Inhabitants: %2")
               .arg(capaciteHabitants)
               .arg(habitantsActuels);
}
