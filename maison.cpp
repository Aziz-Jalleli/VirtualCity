#include "maison.h"
#include<iostream>
#include<Qstring>
using namespace std;

Maison::Maison(int id,QString nom,QString type,int cons_eau,int cons_elec,int satisfaction,int capaciteHabitants ,int habitantsActuels) : Batiment( id, nom, type, cons_eau, cons_elec, satisfaction) {
    this->capaciteHabitants=capaciteHabitants;
    this->habitantsActuels=habitantsActuels;

}
Void Maison::ajouterHabitants(int nb){
    int tmp= habitantsActuels+nb;
    if (tmp <capaciteHabitants){
        this->habitantsActuels =tmp;

    }else{
        this->habitantsActuels = this->capaciteHabitants;
    }

}
Void Maison::retireHabitants(int nb){
    int tmp= habitantsActuels-nb;
    if (tmp <=0){
        this->habitantsActuels =0;

    }else{
        this->habitantsActuels = tmp;
    }

}
