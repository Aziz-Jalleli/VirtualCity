#include "parc.h"
#include<iostream>
#include<Qstring>
using namespace std;
parc::parc(int id,QString nom,QString type,int cons_eau,int cons_elec,int satisfaction,float surface ,int effetBienEtre) : Batiment(nullptr, id, nom, type, cons_eau, cons_elec, effet_satisfaction) {
    this->surface=surface;
    this->effetBienEtre=effetBienEtre;
    effet_satisfaction=5;
    parc::calculerImpactRessources();
}

void parc::ameliorerBienEtre (){
    if(this->effetBienEtre<=95){

        this->effetBienEtre+=5;
    }else{
        this->effetBienEtre+=100;
    }
}
void parc::afficherDetails() {
    Batiment::afficherDetails();

    cout << surface <<endl;
    cout << effetBienEtre<<endl;
}
void parc::calculerImpactRessources() {
    cons_eau=surface/10;
    cons_elec=700;
}
void parc::diminueBienEtre(){
    this->effetBienEtre/2;
}
