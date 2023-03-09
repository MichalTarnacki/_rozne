//
//  Wilk.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Wilk.hpp"

Wilk::Wilk(Swiat &swiat):Zwierze(swiat){
    SetInicjatywa();
    SetSila();
};
char Wilk::Rysowanie() const{
    return 'W';
}
void Wilk::SetInicjatywa(){
    this->inicjatywa=5;
}
void Wilk::SetSila(){
    this->sila=9;
}
Organizm* Wilk::Urodz(){
    return new Wilk(this->swiat);
}
bool Wilk::MozeBycPartnerem(Organizm& organizm){
    if(dynamic_cast<Wilk*>(&organizm))
       return true;
    else
       return false;
}
