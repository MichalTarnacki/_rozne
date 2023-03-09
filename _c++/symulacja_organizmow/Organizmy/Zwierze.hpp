//
//  Zwierze.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Zwierze_hpp
#define Zwierze_hpp

#include <stdio.h>
#include "Organizm.hpp"

class Zwierze: public Organizm{
    virtual void SetInicjatywa() override = 0;
    virtual void SetSila() override  = 0;
public:
    Zwierze(Swiat &swiat);
    virtual void Akcja() override;
    virtual char Rysowanie() const override = 0;
    virtual void Ruch(unsigned int zasiegRuchu);
    bool RuchBezKolizji(unsigned int zasiegRuchu);
    virtual Organizm* Urodz() override = 0;
    virtual bool MozeBycPartnerem(Organizm& organizm) override = 0;
    void Kopulacja(Organizm& organizm);
    void Kolizja(Organizm &organizm) override;
    
};

#endif /* Zwierze_hpp */
