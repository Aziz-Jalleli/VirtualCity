#ifndef VILLE_H
#define VILLE_H
#include<Qstring>
#include <QObject>
#include <vector>
#include "batiment.h"
using namespace std;
class Ville: public QObject
{

    Q_OBJECT;
private:
    QString nom;
    int budget;
    int population;
    int satisfaction;
    int eau;
    int electricite;
    vector<Batiment> batiments;

public:
    Ville(QObject *parent = nullptr,QString=0, int budget=0,int population=0,int satisfaction=0 ,int eau=0 ,int electricite=0);
    Ville(QObject *parent, QString, int, int, int);
    Ville& operator=(const Ville& other);
    void ajouterBatiment(Batiment& );
    void supprimerBatiment(int );
    void calculerPopulation();
    void calculerConsommationTotale();
    void CalculerSatisfaction();
    int get_Elec () const;
    void set_Elec (int );
    int get_satisfaction () const;
    void set_satisfaction (int ) ;
    void Event_panne_courant ();
    vector<Batiment> get_batiments() const;
};

#endif // VILLE_H
