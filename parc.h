#ifndef PARC_H
#define PARC_H

#include <QObject>
#include "batiment.h"


class parc:public Batiment
{
    Q_OBJECT;
private:
    float surface;
    int effetBienEtre;
public:
    bool isParc() const override { return true; }

    parc(int,QString,float);
    void ameliorerBienEtre () ;
    void afficherDetails() override;
    void calculerImpactRessources() override;
    void diminueBienEtre();
    int get_effetbienetre();

};

#endif // PARC_H
