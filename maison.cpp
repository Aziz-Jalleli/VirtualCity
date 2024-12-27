#include "maison.h"
#include<iostream>
#include<Qstring>
using namespace std;

Maison::Maison(int id,QString nom,QString type,int cons_eau,int cons_elec,int effet_satisfaction,int capaciteHabitants ,int habitantsActuels) : Batiment(nullptr, id, nom, type, cons_eau, cons_elec, effet_satisfaction) {
    this->capaciteHabitants=capaciteHabitants;
    this->habitantsActuels=habitantsActuels;
    cons_elec=1000;
    effet_satisfaction=10;

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
