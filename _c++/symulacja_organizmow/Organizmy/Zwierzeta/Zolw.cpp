//
//  Zolw.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Zolw.hpp"

Zolw::Zolw(Swiat &swiat):Zwierze(swiat){
    SetInicjatywa();
    SetSila();
};
void Zolw::Akcja(){
    int x=rand()%100;
    if(x>=75)
        Zwierze::Akcja();
}
void Zolw::Kolizja(Organizm& organizm){
    if(organizm.GetSila()<5&&!dynamic_cast<Zolw*>(&organizm)){
        organizm.SetPolozenie(organizm.GetPoprzedniePolozenie());
        std::cout << "Organizm: " << organizm.GetPolozenie() << " jest za slaby zeby walczyc z zolwiem, wraca na poprzenia pozycje: " << organizm.GetPolozenie() << std::endl;
    }
    else
        Zwierze::Kolizja(organizm);
}
char Zolw::Rysowanie() const{
    return 'Z';
}
void Zolw::SetInicjatywa(){
    this->inicjatywa=1;
}
void Zolw::SetSila(){
    this->sila=2;
}
Organizm* Zolw::Urodz(){
    return new Zolw(this->swiat);
}
bool Zolw::MozeBycPartnerem(Organizm& organizm){
    if(dynamic_cast<Zolw*>(&organizm))
       return true;
    else
       return false;
}
