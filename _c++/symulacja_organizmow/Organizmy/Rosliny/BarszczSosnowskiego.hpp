//
//  BarszczSosnowskiego.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef BarszczSosnowskiego_hpp
#define BarszczSosnowskiego_hpp

#include <stdio.h>
#include "Roslina.hpp"
class BarszczSosnowskiego: public Roslina{
    void SetSila() override;
public:
    BarszczSosnowskiego(Swiat &swiat);
    void Akcja() override;
    void Kolizja(Organizm& organizm) override;
    char Rysowanie() const override;
    void ZabijWokolo();
    Organizm* Urodz() override;
    int GetPrawdopodobienstwo() override;
    bool MozeBycPartnerem(Organizm& organizm) override;
};
#endif /* BarszczSosnowskiego_hpp */
