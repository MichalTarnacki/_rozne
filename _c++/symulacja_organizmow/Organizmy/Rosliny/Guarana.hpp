//
//  Guarana.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Guarana_hpp
#define Guarana_hpp

#include <stdio.h>
#include "Roslina.hpp"
class Guarana: public Roslina{

public:
    Guarana(Swiat &swiat);
    void Kolizja(Organizm& organizm) override;
    char Rysowanie() const override;
    Organizm* Urodz() override;
    int GetPrawdopodobienstwo() override;
    bool MozeBycPartnerem(Organizm& organizm) override;
};
#endif /* Guarana_hpp */
