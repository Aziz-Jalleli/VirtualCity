#include "usine.h"
#include<iostream>
using namespace std;

usine::usine():Batiment(nullptr, 0, "", "Usine", 500, 2000, 10){
    pollution=0;
    production_eau=0;
    production_elec=0;
}
usine::usine(int id,QString nom) :Batiment(nullptr,id, nom, "Usine", 500, 2000,10){
    pollution =0;
    production_eau=0;
    production_elec=0;
}
void usine::produire_eau(){
    production_eau+=50;
        pollution+=3;
}
void usine::produire_elec(){
    production_elec+=100;
        pollution+=6;
}
void usine::afficherDetails() {
    Batiment::afficherDetails();

    cout << production_eau <<endl;
    cout << production_elec <<endl;
    cout << pollution <<endl;
}
QString usine:: getDetails() const {
    return Batiment::getDetails() +
           QString("\nProduction eau: %1\nProduction electricite: %2\nPollution: %3")
               .arg(production_eau)
               .arg(production_elec)
               .arg(pollution);
}
void usine::calculerImpactRessources() {
    cons_eau=500;
    cons_elec=2000;
}
int usine::geteau() const{
    return production_eau;
}
int usine::getelectricite() const{
    return production_elec;
}

