#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include<vector>
#include<QString>
#include<ville.h>
class Simulation
{
    Q_OBJECT
private:
    int cycleActuel;
    ville Myville;
    vector<QString> Evenements;
public:
    Simulation();
    Simulation (ville v);
    void demarrerCycle();
    void terminerCycle();
    void Event_pigeons();
    void Event_jardiniers();
    void declencherEvenement();
    void Event_panne_transports_publics();
};

#endif // SIMULATION_H
