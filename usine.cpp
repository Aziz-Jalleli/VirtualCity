#include "usine.h"

usine::usine(int id,QString nom,QString type,int cons_eau,int cons_elec,int satisfaction,int,int production_eau,int production_elec,int pollution ) :Batiment(id, nom, type, cons_eau, cons_elec,0,0,0){}
void usine::produire_eau(){
    production_eau+=1360;
        pollution+=3;
}
void usine::produire_elec(){
    production_elec+=6000;
        pollution+=6;
}
