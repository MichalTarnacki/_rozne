//
//  WilczeJagody.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef WilczeJagody_hpp
#define WilczeJagody_hpp

#include <stdio.h>
#include "Roslina.hpp"
class WilczeJagody: public Roslina{
    void SetSila() override;
public:
    WilczeJagody(Swiat &swiat);
    void Kolizja(Organizm& organizm) override;
    char Rysowanie() const override;
    Organizm* Urodz() override;
    int GetPrawdopodobienstwo() override;
    bool MozeBycPartnerem(Organizm& organizm) override;
};
#endif /* WilczeJagody_hpp */
