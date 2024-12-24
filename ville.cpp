
#include "ville.h"
#include<Qstring>

using namespace std

Ville::Ville(QObject *parent, QString nom, float budget,float population,int satisfaction):QObject(parent)
{
    this->nom=nom;
    this->budget=budget;
    Ville::calculerPopulation();
    Ville::CalculerSatisfaction();
    this->eau=0;
    this->electricite=0;

}
void Ville::ajouterBatiment(Batiment b){
    batiments.push_back(b);

}
void Ville::supprimerBatiment (int id){
    vector<batiments>::iterator it = batiments.begin();
    while (it != batiments.end() && it->id != id){
        it++;
    }
    if (it != batiments.end()){
        batiments.erase(it);
    }
<<<<<<< HEAD

}
void Ville::calculerConsommationTotale(){
    for(int i=batiments.begin();i<batiments.size();i++){
        eau+=batiments[i].get_eau();
        electricite+=batiments[i].get_elec();

    }
}
void Ville::CalculerSatisfaction(){
    or(int i=batiments.begin();i<batiments.size();i++){
        satisfaction+=batiments[i].get_satisfaction();
    }
}
void Ville::calculerPopulation (){

    for(int i=batiments.begin();i<batiments.size();i++){
        if (batiment[i].get_habitant()){
            population+=get_habitant();
        }
    }
=======
}
int Ville::get_satisfaction(){
    return satisfaction;
}
void Ville::set_satisfaction(){
    satisfaction=satisfaction*85/100;
>>>>>>> Mohamed
}
