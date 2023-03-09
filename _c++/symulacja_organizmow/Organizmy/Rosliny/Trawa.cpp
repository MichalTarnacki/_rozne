//
//  Trawa.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Trawa.hpp"

Trawa::Trawa(Swiat &swiat):Roslina(swiat){
}

char Trawa::Rysowanie() const{
    return 't';
}
Organizm* Trawa::Urodz(){
    return new Trawa(this->swiat);
}
int Trawa::GetPrawdopodobienstwo(){
    return 30;
}

bool Trawa::MozeBycPartnerem(Organizm& organizm){
    if(dynamic_cast<Trawa*>(&organizm))
       return true;
    else
       return false;
}
