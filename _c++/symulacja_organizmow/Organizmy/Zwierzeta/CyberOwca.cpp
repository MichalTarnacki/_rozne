//
//  CyberOwca.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "CyberOwca.hpp"

CyberOwca::CyberOwca(Swiat &swiat):Zwierze(swiat){
    SetInicjatywa();
    SetSila();
};
void CyberOwca::Akcja(){
    Zwierze::Akcja();
}
void CyberOwca::Kolizja(Organizm& organizm){
    Zwierze::Kolizja(organizm);
}
char CyberOwca::Rysowanie() const{
    return 'C';
}
void CyberOwca::SetInicjatywa(){
    this->inicjatywa=4;
}
void CyberOwca::SetSila(){
    this->sila=11;
}
Organizm* CyberOwca::Urodz(){
    return new CyberOwca(this->swiat);
}
bool CyberOwca::MozeBycPartnerem(Organizm& organizm){
    if(dynamic_cast<CyberOwca*>(&organizm))
       return true;
    else
       return false;
}
