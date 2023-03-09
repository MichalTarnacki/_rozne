//
//  Czlowiek.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Czlowiek_hpp
#define Czlowiek_hpp

#include <stdio.h>
#include "Zwierze.hpp"
#include "Ruch.h"

class Czlowiek: public Zwierze{
    bool czyRuchAntylopyAktywny;
    int czasAktywacji = - 1;
    enum KierunekRuchu kierunek = Sterowany;
    void SetInicjatywa() override;
    void SetSila() override;
public:
    Czlowiek(Swiat &swiat);
    void Akcja() override;
    char Rysowanie() const override;
    void Ruch(unsigned int zasiegRuchu) override;
    Organizm* Urodz() override;
    bool MozeBycPartnerem(Organizm& organizm) override;
    void SpecjalnaUmiejetnosc();
    std::ostream & operator<<(std::ostream &out) override;
    std::ostream & operator<<=(std::ostream &out) override;
    void WczytajWlasciwosci(double sila, double inicjatywa, Polozenie polozenie, Polozenie poprzedniePolozenie, time_t czasUrodzenia, bool czyZywy, bool zdolnyDoRozrodu, double parametr1=0, double parametr2=0) override;
    void UstawKierunekRuchu(KierunekRuchu kierunek);
};
#endif /* Czlowiek_hpp */
