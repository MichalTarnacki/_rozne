//
//  Organizm.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Organizm_hpp
#define Organizm_hpp

#include <stdio.h>
#include <time.h>
#include "Polozenie.hpp"
#include <iostream>
#include "Plansza.hpp"
#include "Swiat.hpp"

class Organizm{
    
    void SetCzasUrodzenia();

protected:
    double sila=0;
    double inicjatywa=0;
    Polozenie polozenie, poprzedniePolozenie;
    time_t czasUrodzenia;
    Swiat &swiat;
    bool czyZywy=true;
    bool zdolnyDoRozrodu=false;
    virtual void SetInicjatywa()=0;
    virtual void SetSila()=0;

public:
    Organizm(Swiat& swiat);
    virtual ~Organizm()=0;
    virtual void Akcja()=0;
    virtual void Kolizja(Organizm &organizm);
    virtual char Rysowanie() const = 0;
    double GetInicjatywa();
    double GetDlugoscZycia();
    double GetSila();
    Polozenie GetPolozenie();
    void SetPolozenie(Polozenie polozenie);
    Polozenie GetPoprzedniePolozenie();
    void SetPoprzedniePolozenie(Polozenie polozenie);
    bool SprawdzCzyMoznaBezpiecznieRuszyc(unsigned int zasiegRuchu);
    bool SprawdzCzyZyje();
    void Zabij();
    virtual Organizm* Urodz() = 0;
    void ZwiekszSile(double oIle);
    bool CzyMozeSieRozmnazac();
    void SetZdolnoscRozrodu(bool status);
    virtual bool MozeBycPartnerem(Organizm& organizm) = 0;
    virtual std::ostream & operator<<(std::ostream &out);
    virtual std::ostream & operator<<=(std::ostream &out);
    friend std::ostream& operator <<(std::ostream&out, Organizm& organizm);
    friend std::ostream& operator <<=(std::ostream&out, Organizm& organizm);
    virtual void WczytajWlasciwosci(double sila, double inicjatywa, Polozenie polozenie, Polozenie poprzedniePolozenie, time_t czasUrodzenia, bool czyZywy, bool zdolnyDoRozrodu, double parametr1=0, double parametr2=0);
};

#endif /* Organizm_hpp */
