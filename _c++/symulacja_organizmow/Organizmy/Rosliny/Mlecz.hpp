//
//  Mlecz.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Mlecz_hpp
#define Mlecz_hpp

#include <stdio.h>
#include "Roslina.hpp"

class Mlecz: public Roslina{

public:
    Mlecz(Swiat &swiat);
    void Akcja() override;
    char Rysowanie() const override;
    Organizm* Urodz() override;
    int GetPrawdopodobienstwo() override;
    bool MozeBycPartnerem(Organizm& organizm) override;
};
#endif /* Mlecz_hpp */
