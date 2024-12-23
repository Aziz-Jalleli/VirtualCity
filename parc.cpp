#include "parc.h"
#include<iostream>
#include<Qstring>
using namespace std;
parc::parc(int id,QString nom,QString type,int cons_eau,int cons_elec,int satisfaction,float surface ,int effetBienEtre) : Batiment( id, nom, type, cons_eau, cons_elec, satisfaction) {
    this->surface=surface;
    this->effetBienEtre=effetBienEtre;
}
parc::parc(int id,QString nom,QString type,int cons_eau,int cons_elec,int satisfaction,float surface ) : Batiment( id, nom, type, cons_eau, cons_elec, satisfaction) {
    this->surface=surface;
}
void parc::ameliorerBienEtre (){
    if(this->effetBienEtre<=95){

        this->effetBienEtre+=5;
    }else{
        this->effetBienEtre+=100;
    }
}
