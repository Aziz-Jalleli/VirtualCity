#ifndef PARC_H
#define PARC_H

#include <QObject>
#include <QObject>
#include "batiment.h"
class parc
{
    Q_OBJECT;
private:
    float surface;
    void ameliorerBienEtre;
public:

    parc(int,QString,QString,int,int ,int,float,int);
    void ameliorerBienEtre ();
};

#endif // PARC_H
