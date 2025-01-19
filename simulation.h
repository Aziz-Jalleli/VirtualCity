#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include<vector>
#include<QString>
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
    Simulation (shared_ptr<Ville> villePtr);
    Simulation (const Ville&);
    std::shared_ptr<Ville> get_ville();
    void demarrerCycle();
    void terminerCycle();
    QString Event_pigeons();
    QString Event_jardiniers();
    QString declencherEvenement();
    QString Event_panne_transports_publics();
    QString Event_panne_courant ();

    void service_nettoyage();
    QString Tempete_neige();
    void deneigement();
};

#endif // SIMULATION_H
