#include "simulation.h"
#include "ville.h"
#include <cstdlib>
#include<iostream>
#include "batiment.h"
#include "parc.h"
using namespace std;
Simulation::Simulation(const Ville& v) {
    Myville =v;
    cycleActuel=0;
    Evenements.push_back("incendies");
    Evenements.push_back("Grève");
    Evenements.push_back("&nondation");
    Evenements.push_back("pigeons");
    Evenements.push_back("transport");
}
void Simulation::declencherEvenement() {
    int index = rand() % Evenements.size();
    QString evenement = Evenements[index];

    if (evenement == "pigeons") {
        Event_pigeons();
    }
    else if (evenement == "Grève") {
        Event_jardiniers();
    }
    else if (evenement == "transport") {
        Event_panne_transports_publics();
    }
}
void Simulation::demarrerCycle() {
    cycleActuel++;
    cout<< "Début du cycle " << cycleActuel << "...\n";
}

void Simulation::terminerCycle() {
    cout << "Fin du cycle " <<cycleActuel<< ".\n";
    cycleActuel--;
}
void Simulation::Event_panne_courant (){
    int n= Myville.get_Elec()-(Myville.get_Elec()*0.5);
    Myville.set_Elec(n);
}
void Simulation::Event_pigeons(){
    int n= Myville.get_satisfaction() - (Myville.get_satisfaction()*0.15);
    Myville.set_satisfaction(n);
}
void Simulation::Event_jardiniers() {
    int n = Myville.get_satisfaction() - (Myville.get_satisfaction() * 0.20);
    Myville.set_satisfaction(n);

    std::vector<Batiment> batiments = Myville.get_batiments(); // Vector of Batiment objects

    for (Batiment& b : batiments) { // Iterate by reference to avoid unnecessary copying
        parc* p = dynamic_cast<parc*>(&b); // Try to cast the Batiment to Parc
        if (p) {
            p->diminueBienEtre(); // Call diminueBienEtre for Parc objects
        }
    }
}




void Simulation::Event_panne_transports_publics(){
    int n= Myville.get_satisfaction() - (Myville.get_satisfaction()*0.10);
    Myville.set_satisfaction(n);
}

