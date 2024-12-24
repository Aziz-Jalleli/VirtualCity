#include "batiment.h"
#include<iostream>
#include<Qstring>
using namespace std;

Batiment::Batiment(QObject *parent,int id,QString nom,QString type,int cons_eau,int cons_elec,int effet_satisfaction) : QObject(parent) {
    this->id=id;
    this->nom=nom;
    this->type=type;
    this->cons_eau=cons_eau;
    this->cons_elec=cons_elec;
    this->effet_satisfaction=effet_satisfaction;

}

void Batiment::afficherDetails(){
    cout<<id<<endl;
    cout<<nom.toStdString()<<endl;
    cout<<type.toStdString()<<endl;
    cout<<cons_eau<<endl;
    cout<<cons_elec<<endl;
    cout<<effet_satisfaction<<endl;
}
int Batiment::get_eau(){
    return cons_eau;
}
int Batiment::get_elec(){
    return cons_elec;
}
int Batiment::get_satisfaction(){
    return effet_satisfaction;
}
