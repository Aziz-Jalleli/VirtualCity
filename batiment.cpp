#include "batiment.h"
#include<iostream>
#include<Qstring>
using namespace std;

Batiment::Batiment(QObject *parent,int id,QString nom,QString type,int cons_eau,int cons_elec,int satisfaction) : QObject(parent) {
    this->id=id;
    this->nom=nom;
    this->type=type;
    this->cons_eau=cons_eau;
    this->cons_elec=cons_elec;
    this->satisfaction=satisfaction;

}
void Batiment::afficherDetails(){
    cout<<id<<endl;
    cout<<nom.toStdString()<<endl;
    cout<<type.toStdString()<<endl;
    cout<<cons_eau<<endl;
    cout<<cons_elec<<endl;
    cout<<satisfaction<<endl;
}
