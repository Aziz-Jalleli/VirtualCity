#include "ville.h"
#include<Qstring>

Ville::Ville(QObject *parent, QString nom, float budget,float population,int satisfaction, float eau,float electricite ):QObject(parent)
{
    this->nom=nom;
    this->budget=budget;
    this->population=population;
    this->satisfaction=satisfaction;
    this->eau=eau;
    this->electricite=electricite;

}
void Ville::ajouterBatiment(Batiment b){
    batiments.push_back(b);

}
void Ville::supprimerBatiment (int id){
    vector<batiments>::iterator = batiments.begin();
    while (it != batiments.end() && it->id != id){
        it++;
    }
    if (it != batiments.end()){
        batiments.erase(it);
    }


}
