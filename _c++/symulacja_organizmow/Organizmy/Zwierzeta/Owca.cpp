//
//  Owca.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Owca.hpp"

Owca::Owca(Swiat &swiat):Zwierze(swiat){
    SetInicjatywa();
    SetSila();
};
char Owca::Rysowanie() const{
    return 'O';
}
void Owca::SetInicjatywa(){
    this->inicjatywa=4;
}
void Owca::SetSila(){
    this->sila=4;
}
Organizm* Owca::Urodz(){
    return new Owca(this->swiat);
}
bool Owca::MozeBycPartnerem(Organizm& organizm){
    if(dynamic_cast<Owca*>(&organizm))
       return true;
    else
       return false;
}
