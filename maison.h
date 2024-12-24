#ifndef MAISON_H
#define MAISON_H

#include <QObject>
#include "batiment.h"
class Maison: public Batiment
{
     Q_OBJECT;
private:
     int capaciteHabitants;
     int habitantsActuels;
public:
    Maison(int,QString,QString,int,int,int,int,int);
    void ajouterHabitants(int);
    void retirerHabitants(int);
    void afficherDetails() override;
    void calculerImpactRessources() override;
    int get_habitant();
};


#endif // MAISON_H
