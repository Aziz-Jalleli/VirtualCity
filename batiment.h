#ifndef BATIMENT_H
#define BATIMENT_H

#include <QObject>

class Batiment:public QObject
{
    Q_OBJECT;
protected:
    int id;
    QString nom;
    QString type;
    int cons_eau;
    int cons_elec;
    int effet_satisfaction;
public:
    Batiment(QObject *parent = nullptr,int id=0,QString nom="unknown",QString type="unknown",int cons_eau=0,int cons_elec=0,int effet_satisfaction=0);
    ~Batiment();
    virtual void afficherDetails();
    virtual bool isParc() const { return false; }
    virtual void calculerImpactRessources();
    Batiment(const Batiment& other);
    Batiment& operator=(const Batiment& other);
    int get_eau()const;
    int get_elec()const;
    int get_satisfaction() const;
    int get_id()const;
    virtual QString getDetails() const;


};

#endif // BATIMENT_H
