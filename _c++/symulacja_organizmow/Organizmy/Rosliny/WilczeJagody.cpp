//
//  WilczeJagody.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "WilczeJagody.hpp"

WilczeJagody::WilczeJagody(Swiat &swiat):Roslina(swiat){

}
void WilczeJagody::Kolizja(Organizm& organizm){
    std::cout << "Organizm: " << organizm.Rysowanie() << " na pozycji " << organizm.GetPolozenie() << " zjada Wilcze Jagody i umiera" << std::endl;
    swiat.ZabijOrganizm(organizm);
}
char WilczeJagody::Rysowanie() const{
    return 'w';
}
void WilczeJagody::SetSila(){
    this->sila=99;
}
Organizm* WilczeJagody::Urodz(){
    return new WilczeJagody(this->swiat);
}
int WilczeJagody::GetPrawdopodobienstwo(){
    return 5;
}
bool WilczeJagody::MozeBycPartnerem(Organizm& organizm){
    if(dynamic_cast<WilczeJagody*>(&organizm))
       return true;
    else
       return false;
}
