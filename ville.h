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
    Ville(QObject *parent = nullptr,QString=0, int budget=0,int=0,int=0 ,int=0 ,int=0);
    void ajouterBatiment(Batiment b);
    void supprimerBatiment(int id);
    void calculerPopulation();
    void calculerConsommationTotale();
    int get_Elec ();
    void set_Elec (newelec);
    int get_satisfaction ();
    void set_satisfaction (newv);
    void Event_panne_courant ();
    vector<Batiment> get_batiments();
};

#endif // VILLE_H
