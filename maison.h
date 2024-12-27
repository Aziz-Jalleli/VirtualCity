#ifndef MAISON_H
#define MAISON_H

#include <QObject>
#include "batiment.h"
class Maison: public Batiment
{
private:
     int capaciteHabitants;
     int habitantsActuels;
public:
    Maison();
    Maison(int,QString,int);
    QString getname();
    void ajouterHabitants(int);
    void retirerHabitants(int);
    void afficherDetails() override;
    void calculerImpactRessources() override;
    int get_habitant() const;
    QString getDetails() const override;
};


#endif // MAISON_H
