#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include<vector>
#include<QString>
#include "batiment.h"
#include "parc.h"
#include "ville.h"

#include "ville.h"
class Simulation: public QObject
{
    Q_OBJECT
private:
    int cycleActuel;
    Ville Myville;
    vector<QString> Evenements;
public:
    Simulation (const Ville&);
    void demarrerCycle();
    void terminerCycle();
    void Event_pigeons();
    void Event_jardiniers();
    void declencherEvenement();
    void Event_panne_transports_publics();
    void Event_panne_courant ();
};

#endif // SIMULATION_H
