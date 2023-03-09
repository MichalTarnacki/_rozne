//
//  Swiat.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Swiat_hpp
#define Swiat_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include "Plansza.hpp"
#include "Polozenie.hpp"
#include "KonfiguracjaOrganizmow.hpp"
#include "Ruch.h"

class Organizm;

class Swiat {
    Plansza plansza;
    unsigned int liczbaOrganizmow;
    std::list <Organizm*> organizmy;
    unsigned int numerRundy=0;
    void WykonajTure();
    void KolejnoscRuchu();
    void SortujOrganizmy();
    void WczytajOrganizmy(KonfiguracjaOrganizmow konfiguracja);
    void LosujPozycje();
    void UsunMartweOrganizmy();
    void PrzywrocMozliwosciRozrodu();
    void AktualizujNumerRundy();
    bool SprawdzCzyZostalTylkoJedenGatunek() const;
    void ZapiszAktualnyStan();
    void Wczytaj();
    void ZniszczSwiat();
    void SterujCzlowiekiem(KierunekRuchu kierunek);
    bool IstniejeCzlowiek();
    void WlaczSpecjalnaUmiejetnosc();
public:
    void WyczyscEkran() const;
    void RysujSwiat() const;
    Swiat(Plansza plansza, KonfiguracjaOrganizmow konfiguracja);
    void Symuluj();
    void ZabijOrganizm(Organizm& organizm);
    Plansza GetPlansza();
    std::list <Organizm*>& GetOrganizmy();
    void NarodzOrganizm(Organizm& organizm, Polozenie polozenie);
    int GetNumerRundy();
    ~Swiat();
};

#endif /* Swiat_hpp */
