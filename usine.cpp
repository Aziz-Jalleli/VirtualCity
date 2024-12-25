#include "usine.h"
#include<iostream>
using namespace std;

usine::usine(int id,QString nom,QString type,int cons_eau,int cons_elec,int effet_satisfaction) :Batiment(nullptr,id, nom, type, cons_eau, cons_elec,effet_satisfaction){
    usine::calculerImpactRessources();
    production_eau =0;
    production_elec=0;
    pollution =0;
    effet_satisfaction=10;
}
void usine::produire_eau(){
    production_eau+=1360;
        pollution+=3;
}
void usine::produire_elec(){
    production_elec+=6000;
        pollution+=6;
}
void usine::afficherDetails() {
    Batiment::afficherDetails();

    cout << production_eau <<endl;
    cout << production_elec <<endl;
    cout << pollution <<endl;
}
void usine::calculerImpactRessources() {
    cons_eau=500;
    cons_elec=2000;
}
