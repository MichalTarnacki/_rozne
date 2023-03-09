//
//  Trawa.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Trawa_hpp
#define Trawa_hpp

#include <stdio.h>
#include "Roslina.hpp"

class Trawa: public Roslina{
public:

    Trawa(Swiat &swiat);
    char Rysowanie() const override;
    Organizm* Urodz() override;
    int GetPrawdopodobienstwo() override;
    bool MozeBycPartnerem(Organizm& organizm) override;
};
#endif /* Trawa_hpp */
