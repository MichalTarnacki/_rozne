//
//  Antylopa.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Antylopa_hpp
#define Antylopa_hpp

#include <stdio.h>
#include "Zwierze.hpp"

class Antylopa: public Zwierze{
    void SetInicjatywa() override;
    void SetSila() override;
public:
    Antylopa(Swiat &swiat);
    void Akcja() override;
    void Kolizja(Organizm& organizm) override;
    char Rysowanie() const override;
    Organizm* Urodz() override;
    bool MozeBycPartnerem(Organizm& organizm) override;
};

#endif /* Antylopa_hpp */
