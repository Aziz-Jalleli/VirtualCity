#ifndef MAISON_H
#define MAISON_H

#include <QObject>
#include "batiment.h"
class Maison: public batiment
{
     Q_OBJECT;
private:
     int capaciteHabitants;
     int habitantsActuels;
public:
    Maison(int,int);
    void ajouterHabitants();
    void retirerHabitants();
};


#endif // MAISON_H
