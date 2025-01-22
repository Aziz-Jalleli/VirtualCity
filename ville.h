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
    int produced_eau;
    int produced_electricite;
    int Pollution;
    vector<std::shared_ptr<Batiment>> batiments;
    QGraphicsScene* scene;

public:
    Ville(QObject *parent=nullptr, QString="", int=0);
      Ville(QGraphicsScene* scene);
    Ville(const Ville& );
    Ville& operator=(const Ville& other);
    void ajouterBatiment(shared_ptr<Batiment> );
    void supprimerBatiment(int );
    void Event_panne_courant ();
    vector<std::shared_ptr<Batiment>> get_batiments() const;
    int get_Eau ();
    int get_Elec ();
    int get_produced_eau();
    int get_produced_electricite();
    int getPopulation();
    int getSatisfaction();
    int getPollution();

    int get_satisfaction();
    void set_satisfaction(int);

    int get_pollution();
    void set_pollution(int);

    int getElec();
    void setElec(int);

    Ville(Ville&& other) noexcept {
        // Transfer ownership of resources from 'other' to 'this'
        // For example: this->resource = std::move(other.resource);
    }
};

#endif // VILLE_H
