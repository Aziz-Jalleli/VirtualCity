#ifndef SIMULATION_H
#define SIMULATION_H
#include"ville.h"
#include <QObject>

class Simulation:public QObject
{
    Q_OBJECT
private:
    Ville ville;
    int CycleActuel;
    QString event;

public:
    Simulation();
    void event_pigeon();
    void event_panne_courant();
    void service_nettoyage();
    void event_greve();
    void event_panne_transport();
    void event_tempete();
};

#endif // SIMULATION_H
