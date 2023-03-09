//
//  Zolw.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Zolw_hpp
#define Zolw_hpp

#include <stdio.h>
#include "Zwierze.hpp"

class Zolw: public Zwierze{
    void SetInicjatywa() override;
    void SetSila() override;
public:
    Zolw(Swiat &swiat);
    void Akcja() override;
    void Kolizja(Organizm& organizm) override;
    char Rysowanie() const override;
    Organizm* Urodz() override;
    bool MozeBycPartnerem(Organizm& organizm) override;
};

#endif /* Zolw_hpp */
