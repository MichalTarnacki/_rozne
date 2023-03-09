//
//  Roslina.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Roslina_hpp
#define Roslina_hpp

#include <stdio.h>
#include "Organizm.hpp"

class Roslina: public Organizm{
    void SetInicjatywa() override;
    virtual void SetSila() override;
public:
    Roslina(Swiat &swiat);
    virtual void Akcja() override;
    virtual char Rysowanie() const override = 0;
    virtual int GetPrawdopodobienstwo() = 0;
    void Zasiej();
    virtual Organizm* Urodz() override = 0;
    virtual bool MozeBycPartnerem(Organizm& organizm) override = 0;
};
#endif /* Roslina_hpp */
