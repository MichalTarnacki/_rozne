//
//  CyberOwca.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef CyberOwca_hpp
#define CyberOwca_hpp

#include <stdio.h>
#include "Zwierze.hpp"

class CyberOwca: public Zwierze{
    void SetInicjatywa() override;
    void SetSila() override;
public:
    CyberOwca(Swiat &swiat);
    void Akcja() override;
    void Kolizja(Organizm& organizm) override;
    char Rysowanie() const override;
    Organizm* Urodz() override;
    bool MozeBycPartnerem(Organizm& organizm) override;
};

#endif /* CyberOwca_hpp */
