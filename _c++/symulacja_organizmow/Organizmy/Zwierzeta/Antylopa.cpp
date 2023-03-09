//
//  Antylopa.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Antylopa.hpp"

Antylopa::Antylopa(Swiat &swiat):Zwierze(swiat){
    SetInicjatywa();
    SetSila();
};
void Antylopa::Akcja(){
    Ruch(2);
}
void Antylopa::Kolizja(Organizm& organizm){
    bool czySieRuszyl;
    int x=rand()%100;
    if(x>=50&&!dynamic_cast<Antylopa*>(&organizm)){
        czySieRuszyl=RuchBezKolizji(2);
        if(!czySieRuszyl)
            Zwierze::Kolizja(organizm);
        else{
            std::cout << "Antylopa: " << this->GetPolozenie() << " uciekae bez kolizji" << std::endl;
        }
    }
    else
        Zwierze::Kolizja(organizm);
}
char Antylopa::Rysowanie() const{
    return 'A';
}
void Antylopa::SetInicjatywa(){
    this->inicjatywa=4;
}
void Antylopa::SetSila(){
    this->sila=4;

}
Organizm* Antylopa::Urodz(){
    return new Antylopa(this->swiat);
}
bool Antylopa::MozeBycPartnerem(Organizm& organizm){
    if(dynamic_cast<Antylopa*>(&organizm))
       return true;
    else
       return false;
}
