//
//  Lis.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Lis_hpp
#define Lis_hpp

#include <stdio.h>
#include "Zwierze.hpp"

class Lis: public Zwierze{
    void SetInicjatywa() override;
    void SetSila() override;
public:
    Lis(Swiat &swiat);
    void Akcja() override;
    char Rysowanie() const override;
    Organizm* Urodz() override;
    bool MozeBycPartnerem(Organizm& organizm) override;
};

#endif /* Lis_hpp */
