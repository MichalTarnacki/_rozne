//
//  ZmienneDoWczytania.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 23/04/2022.
//

#ifndef ZmienneDoWczytania_hpp
#define ZmienneDoWczytania_hpp

#include <stdio.h>
#include <list>
#include <time.h>
#include "Polozenie.hpp"

class Organizm;
class Swiat;

class ZmienneDoWczytania{
public:
    double sila, inicjatywa, parametr1=0, parametr2=0;
    time_t czasUrodzenia;
    bool czyZywy, zdolnyDoRozrodu;
    char znak;
    unsigned int liczbaOrganizmow, numerRundy, x,y, x2, y2;
    Polozenie polozenie, poprzedniePolozenie;
    std::list<Organizm*> tymczasoweOrganizmy;
    ZmienneDoWczytania(Swiat &swiat);
    ~ZmienneDoWczytania();
};

#endif /* ZmienneDoWczytania_hpp */
