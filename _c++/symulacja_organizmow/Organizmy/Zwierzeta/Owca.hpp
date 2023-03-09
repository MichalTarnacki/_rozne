//
//  Owca.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Owca_hpp
#define Owca_hpp

#include <stdio.h>
#include "Zwierze.hpp"

class Owca: public Zwierze{
    void SetInicjatywa() override;
    void SetSila() override;
public:
    Owca(Swiat &swiat);
    char Rysowanie() const override;
    Organizm* Urodz() override;
    bool MozeBycPartnerem(Organizm& organizm) override;
};
#endif /* Owca_hpp */
