//
//  Mlecz.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Mlecz.hpp"

Mlecz::Mlecz(Swiat &swiat):Roslina(swiat){

}
void Mlecz::Akcja(){
    for(int i=0; i<3;i++)
        Roslina::Akcja();
}
char Mlecz::Rysowanie() const{
    return 'm';
}
Organizm* Mlecz::Urodz(){
    return new Mlecz(this->swiat);
}
int Mlecz::GetPrawdopodobienstwo(){
    return 10;
}

bool Mlecz::MozeBycPartnerem(Organizm& organizm){
    if(dynamic_cast<Mlecz*>(&organizm))
       return true;
    else
       return false;
}
