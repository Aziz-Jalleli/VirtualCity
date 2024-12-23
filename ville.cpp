#include "ville.h"


Ville::Ville(QObject *parent, string nom, float budget,float population,int satisfaction, float Eau,float electricite ):QObject(parent)
{
    this->nom=nom;
    this->budget=budget;
    this->population=population;
    this->satisfaction=satisfaction;
    this->Eau=Eau;
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
