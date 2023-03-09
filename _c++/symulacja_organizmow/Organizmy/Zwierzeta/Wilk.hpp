//
//  Wilk.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Wilk_hpp
#define Wilk_hpp

#include <stdio.h>
#include "Zwierze.hpp"

class Wilk: public Zwierze{
    void SetInicjatywa() override;
    void SetSila() override;
public:
    Wilk(Swiat &swiat);
    char Rysowanie() const override;
    Organizm* Urodz() override;
    bool MozeBycPartnerem(Organizm& organizm) override;
};
#endif /* Wilk_hpp */
