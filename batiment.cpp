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
int Batiment::get_eau() const{
    return cons_eau;
}
int Batiment::get_elec() const{
    return cons_elec;
}
int Batiment::get_satisfaction() const {
    return effet_satisfaction;
}
int Batiment::get_id () const{
    return id;
}
Batiment::Batiment(const Batiment& other)
    : QObject(other.parent()), id(other.id), nom(other.nom), type(other.type), cons_eau(other.cons_eau), cons_elec(other.cons_elec), effet_satisfaction(other.effet_satisfaction)
{
    // If you had pointers or dynamically allocated resources, you would need to deep copy them here
}

// Assignment operator for deep copy
Batiment& Batiment::operator=(const Batiment& other) {
    if (this != &other) {
        // Assign all members
        id = other.id;
        nom = other.nom;
        type = other.type;
        cons_eau = other.cons_eau;
        cons_elec = other.cons_elec;
        effet_satisfaction = other.effet_satisfaction;
        // If you had dynamic memory, it would be a deep copy here as well
    }
    return *this;
}
void Batiment::calculerImpactRessources(){

}
Batiment::~Batiment(){

}
