#ifndef PARC_H
#define PARC_H

#include <QObject>
#include "batiment.h"


class parc
{
    Q_OBJECT;
private:
    float surface;
    int effetBienEtre;
public:

    parc(int,QString,QString,int,int ,int,float,int);
    void ameliorerBienEtre ();
    void afficherDetails() override;
};

#endif // PARC_H
