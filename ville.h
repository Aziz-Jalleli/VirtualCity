#ifndef VILLE_H
#define VILLE_H
#include<Qstring>
#include <QObject>
#include <vector>
#include "batiment.h"
#include <memory>
#include <QGraphicsScene>
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
    vector<std::shared_ptr<Batiment>> batiments;
    QGraphicsScene* scene;

public:
    Ville(QObject *parent=nullptr, QString="", int=0);
      Ville(QGraphicsScene* scene);
    Ville& operator=(const Ville& other);
    void ajouterBatiment(shared_ptr<Batiment> );
    void supprimerBatiment(int );
    void calculerPopulation();
    void calculerConsommationTotale();
    void CalculerSatisfaction();
    int get_Elec () const;
    void set_Elec (int );
    int get_satisfaction () const;
    void set_satisfaction (int ) ;
    void Event_panne_courant ();
    vector<std::shared_ptr<Batiment>> get_batiments() const;
};

#endif // VILLE_H
