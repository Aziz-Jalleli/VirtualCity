#include "parc.h"
#include<iostream>
#include<Qstring>
using namespace std;
parc::parc(int id,QString nom,float surface) : Batiment(nullptr, id, nom, "Parc", 0, 700, 5) {
    cons_eau=surface/10;
    effetBienEtre=0;
    effet_satisfaction=5;

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
int parc::get_effetbienetre(){
    return effetBienEtre;
}
