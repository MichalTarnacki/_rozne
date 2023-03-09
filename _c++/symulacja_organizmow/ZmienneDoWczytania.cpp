//
//  ZmienneDoWczytania.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 23/04/2022.
//

#include "ZmienneDoWczytania.hpp"
#include "WszystkieOrganizmy.h"

ZmienneDoWczytania::ZmienneDoWczytania(Swiat &swiat){
    Trawa *trawa = new Trawa(swiat);
    tymczasoweOrganizmy.push_back(trawa);
    Mlecz *mlecz = new Mlecz(swiat);
    tymczasoweOrganizmy.push_back(mlecz);
    Guarana *guarana = new Guarana(swiat);
    tymczasoweOrganizmy.push_back(guarana);
    WilczeJagody *wilczeJagody = new WilczeJagody(swiat);
    tymczasoweOrganizmy.push_back(wilczeJagody);
    BarszczSosnowskiego *barszczSosnowskiego = new BarszczSosnowskiego(swiat);
    tymczasoweOrganizmy.push_back(barszczSosnowskiego);
    Wilk *wilk = new Wilk(swiat);
    tymczasoweOrganizmy.push_back(wilk);
    Owca *iwca = new Owca(swiat);
    tymczasoweOrganizmy.push_back(iwca);
    Lis *lis = new Lis(swiat);
    tymczasoweOrganizmy.push_back(lis);
    Zolw *zolw = new Zolw(swiat);
    tymczasoweOrganizmy.push_back(zolw);
    Antylopa *antylopa = new Antylopa(swiat);
    tymczasoweOrganizmy.push_back(antylopa);
    CyberOwca *cyberOwca = new CyberOwca(swiat);
    tymczasoweOrganizmy.push_back(cyberOwca);
    Czlowiek *czlowiek = new Czlowiek(swiat);
    tymczasoweOrganizmy.push_back(czlowiek);
}
ZmienneDoWczytania::~ZmienneDoWczytania(){
    Organizm* ptr=nullptr;
    for (Organizm *organizm: tymczasoweOrganizmy){
        if(ptr!=nullptr){
            tymczasoweOrganizmy.remove(ptr);
            delete ptr;
        }
        ptr=organizm;
    }
    ptr=tymczasoweOrganizmy.back();
    tymczasoweOrganizmy.remove(ptr);
    delete ptr;
}
