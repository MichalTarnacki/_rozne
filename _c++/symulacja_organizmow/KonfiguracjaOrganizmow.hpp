//
//  KonfiguracjaOrganizmow.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef KonfiguracjaOrganizmow_hpp
#define KonfiguracjaOrganizmow_hpp

#include <stdio.h>

class KonfiguracjaOrganizmow{
public:
    KonfiguracjaOrganizmow(unsigned int liczbaLudzi = 0,
                           unsigned int liczbaWilkow = 0,
                           unsigned int liczbaOwiec = 0,
                           unsigned int liczbaLisow = 0,
                           unsigned int liczbaZolwi = 0,
                           unsigned int liczbaAntylop = 0,
                           unsigned int liczbaCyberOwiec = 0,
                           unsigned int liczbaTraw = 0,
                           unsigned int liczbaMleczy = 0,
                           unsigned int liczbaGuarany = 0,
                           unsigned int liczbaWilczychJagod = 0,
                           unsigned int liczbaBarszuSosnowskiego = 0);
    unsigned int liczbaLudzi;
    unsigned int liczbaWilkow;
    unsigned int liczbaOwiec;
    unsigned int liczbaLisow;
    unsigned int liczbaZolwi;
    unsigned int liczbaAntylop;
    unsigned int liczbaCyberOwiec;
    unsigned int liczbaTraw;
    unsigned int liczbaMleczy;
    unsigned int liczbaGuarany;
    unsigned int liczbaWilczychJagod;
    unsigned int liczbaBarszuSosnowskiego;
    unsigned int getLacznaLiczbaOrganizmow();
};
#endif /* KonfiguracjaOrganizmow_hpp */
