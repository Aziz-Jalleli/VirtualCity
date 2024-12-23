#ifndef VILLE_H
#define VILLE_H
#include<string>
#include <QObject>
#include <vector>
#include "batiment.h"
using namespace std;
class Ville: public QObject
{

    Q_OBJECT;
private:
    string nom;
    float budget;
    float population;
    int satisfaction;
    vector<Batiment> batiments;
    string ressources;
public:
    Ville(QObject *parent = nullptr,string nom='', float budget =0,float population=0,int satisfaction =0,string ressources = "Eau");
    void ajouterBatiment(Batiment b);
    void supprimerBatiment(int id);
};

#endif // VILLE_H
