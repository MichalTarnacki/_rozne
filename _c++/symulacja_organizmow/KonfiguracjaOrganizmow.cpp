//
//  KonfiguracjaOrganizmow.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "KonfiguracjaOrganizmow.hpp"

KonfiguracjaOrganizmow::KonfiguracjaOrganizmow(
                       unsigned int liczbaLudzi,
                       unsigned int liczbaWilkow,
                       unsigned int liczbaOwiec,
                       unsigned int liczbaLisow,
                       unsigned int liczbaZolwi,
                       unsigned int liczbaAntylop,
                       unsigned int liczbaCyberOwiec,
                       unsigned int liczbaTraw,
                       unsigned int liczbaMleczy,
                       unsigned int liczbaGuarany,
                       unsigned int liczbaWilczychJagod,
                       unsigned int liczbaBarszuSosnowskiego){
    this-> liczbaLudzi = liczbaLudzi;
    this-> liczbaWilkow = liczbaWilkow;
    this-> liczbaOwiec = liczbaOwiec;
    this-> liczbaLisow = liczbaLisow;
    this-> liczbaZolwi = liczbaZolwi;
    this-> liczbaAntylop = liczbaAntylop;
    this-> liczbaCyberOwiec = liczbaCyberOwiec;
    this-> liczbaTraw = liczbaTraw;
    this-> liczbaMleczy = liczbaMleczy;
    this-> liczbaGuarany = liczbaGuarany;
    this-> liczbaWilczychJagod = liczbaWilczychJagod;
    this-> liczbaBarszuSosnowskiego = liczbaBarszuSosnowskiego;

};

unsigned int KonfiguracjaOrganizmow::getLacznaLiczbaOrganizmow(){
    return (
            liczbaWilkow +
            liczbaOwiec +
            liczbaLisow +
            liczbaZolwi +
            liczbaAntylop +
            liczbaCyberOwiec +
            liczbaTraw +
            liczbaMleczy +
            liczbaGuarany +
            liczbaWilczychJagod +
            liczbaBarszuSosnowskiego +
            liczbaLudzi
            );
}
