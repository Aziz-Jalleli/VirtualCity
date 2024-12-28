#ifndef USINE_H
#define USINE_H
#include<Qstring>
#include"batiment.h"
class usine:public Batiment
{
private:
    int production_eau,production_elec,pollution;
public:
    usine();
    usine(int,QString);
    void produire_eau();
    void produire_elec();
    void calculer_polution();
    void afficherDetails() override;
    void calculerImpactRessources() override;
    QString getDetails() const override;
    int geteau() const;
};

#endif // USINE_H
