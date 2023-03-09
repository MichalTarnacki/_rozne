//
//  Plansza.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Plansza_hpp
#define Plansza_hpp

#include <stdio.h>
#include <iostream>
class Plansza{
    unsigned int N,M;
public:
    Plansza(int n, int m);
    Plansza();
    Plansza(Plansza& plansza);
    unsigned int GetN() const;
    unsigned int GetM() const;
    unsigned int GetLiczbaPol() const;
    void setN(int n);
    void setM(int m);
    void set(int n, int m);
    friend std::ostream& operator <<(std::ostream&out, Plansza& plansza);
    friend std::ostream& operator <<=(std::ostream&out, Plansza& plansza);
};
#endif /* Plansza_hpp */
