#include "simulation.h"
#include "ville.h"
#include <cstdlib>
#include<iostream>
#include "parc.h"
#include<QString>
using namespace std;
Simulation::Simulation(std::shared_ptr<Ville> villePtr) {
    Myville = *villePtr;
    cycleActuel = 0;
    Evenements.push_back("TempeteNeige");
    Evenements.push_back("Grève");
    Evenements.push_back("PanneCourant");
    Evenements.push_back("pigeons");
    Evenements.push_back("transport");
}
Simulation::Simulation(const Ville& v) {
    Myville = v;
    cycleActuel=0;
    Evenements.push_back("TempeteNeige");
    Evenements.push_back("Grève");
    Evenements.push_back("PanneCourant");
    Evenements.push_back("pigeons");
    Evenements.push_back("transport");
}
std::shared_ptr<Ville> Simulation::get_ville() {
    return std::make_shared<Ville>(Myville);  // Return a copy of Myville
}
QString Simulation::declencherEvenement() {
    int index = rand() % Evenements.size();
    QString evenement = Evenements[index];
    if (evenement == "pigeons") {
        return Event_pigeons();
    }
    else if (evenement == "Grève") {
        return Event_jardiniers();
    }
    else if (evenement == "transport") {
        return Event_panne_transports_publics();
    }
    else if (evenement == "PanneCourant"){
        return Event_panne_courant();
    }
    else if (evenement == "TempeteNeige"){
        return Tempete_neige();
    }
    return QString("An unknown event occurred.");
}
void Simulation::demarrerCycle() {
    cycleActuel++;
    cout<< "Début du cycle " << cycleActuel << "...\n";
}

void Simulation::terminerCycle() {
    cout << "Fin du cycle " <<cycleActuel<< ".\n";
    cycleActuel--;
}

QString Simulation::Event_panne_courant (){
    int n= Myville.getElec()*2;
    Myville.setElec(n);
    return QString("Une panne de courant fait grimper la consommation d’énergie de 50 %.");
}

QString Simulation::Event_pigeons(){
    int n= Myville.get_satisfaction() - (Myville.get_satisfaction()*0.15);
    Myville.set_pollution(Myville.getPollution()+30);
    Myville.set_satisfaction(n);
    return QString("Une nuée de pigeons géants envahit votre ville ! Résultat  une baisse de 15% de la satisfaction des habitants. De plus, ils déplorent la présence de trop de déchets dans les rues. Heureusement, vous avez un  service de nettoyage  à gérer pour remettre de l'ordre.");
}

void Simulation::service_nettoyage(){
    int n= Myville.get_satisfaction() + (Myville.get_satisfaction()*0.15);
    Myville.set_pollution(Myville.getPollution()-30);
    Myville.set_satisfaction(n);
}

QString Simulation::Event_jardiniers() {
    int n = Myville.get_satisfaction() - (Myville.get_satisfaction() * 0.20);
    Myville.set_satisfaction(n);

    for (const auto& Parc :  Myville.get_batiments() ) {
        if(Parc->gettype()=="Parc"){
            auto p = std::dynamic_pointer_cast<parc>(Parc);
            p->diminueBienEtre();
        }
    }
    return QString("Les jardiniers de la ville sont en grève et refusent d’entretenir les parcs et espaces verts ! La satisfaction de vos habitants tombe de 20% et l’effet des parcs diminue de moitié.");

}

QString Simulation::Event_panne_transports_publics(){
    int n= Myville.get_satisfaction() - (Myville.get_satisfaction()*0.10);
    Myville.set_satisfaction(n);
     return QString("Une panne géante de transports publics se produit, tous les bus de la ville sont bloqués par un gigantesque embouteillage ! Résultat : la satisfaction chute brutalement. Les habitants doivent maintenant marcher pour aller au travail, à l'école et au parc.");
}

QString Simulation::Tempete_neige(){
    int n= Myville.get_satisfaction() - (Myville.get_satisfaction()*0.10);
    Myville.set_satisfaction(n);
    return QString("Une tempête de neige imprévu bloque les routes, interrompt la production des usines et rend les habitants grumpy.");
}

void Simulation::deneigement(){
    int n= Myville.get_satisfaction() + (Myville.get_satisfaction()*0.10);
    Myville.set_satisfaction(n);
}

