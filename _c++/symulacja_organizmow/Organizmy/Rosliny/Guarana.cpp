//
//  Guarana.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Guarana.hpp"

Guarana::Guarana(Swiat &swiat):Roslina(swiat){

}
void Guarana::Kolizja(Organizm& organizm){
    std::cout << "Organizm: " << organizm.Rysowanie() << " na pozycji " << organizm.GetPolozenie() << " zjada Guarane, jego sila rosnie" << std::endl;
    organizm.ZwiekszSile(3);
    Organizm::Kolizja(organizm);
}
char Guarana::Rysowanie() const{
    return 'g';
}
Organizm* Guarana::Urodz(){
    return new Guarana(this->swiat);
}
int Guarana::GetPrawdopodobienstwo(){
    return 20;
}
bool Guarana::MozeBycPartnerem(Organizm& organizm){
    if(dynamic_cast<Guarana*>(&organizm))
       return true;
    else
       return false;
}
