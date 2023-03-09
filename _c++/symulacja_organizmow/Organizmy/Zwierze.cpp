
//
//  Zwierze.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Zwierze.hpp"

Zwierze::Zwierze(Swiat &swiat):Organizm(swiat){
    
}
void Zwierze::Ruch(unsigned int zasiegRuchu=1){
    Polozenie nowePolozenie;
    do {
        nowePolozenie.setXY(polozenie.GetX()+zasiegRuchu*(rand()%3-1), polozenie.GetY()+zasiegRuchu*rand()%3-1);
    } while (nowePolozenie==polozenie||nowePolozenie.GetX()<0 || nowePolozenie.GetY()<0 || nowePolozenie.GetX()>=swiat.GetPlansza().GetN()||nowePolozenie.GetY()>=swiat.GetPlansza().GetM());
    polozenie=nowePolozenie;
};
bool Zwierze::RuchBezKolizji(unsigned int zasiegRuchu=1){
    if(!SprawdzCzyMoznaBezpiecznieRuszyc(zasiegRuchu))
        return false;
    Polozenie nowePolozenie;
    bool uniq=true;
    while(true) {
        uniq=true;
        nowePolozenie.setXY(polozenie.GetX()+zasiegRuchu*(rand()%3-1), polozenie.GetY()+zasiegRuchu*(rand()%3-1));
        if(!(nowePolozenie==polozenie)&&nowePolozenie.GetX()>=0&&nowePolozenie.GetY()>=0&&nowePolozenie.GetX()<swiat.GetPlansza().GetN()&&nowePolozenie.GetY()<swiat.GetPlansza().GetM()){
            for (Organizm *organizm: swiat.GetOrganizmy()){
                if(nowePolozenie==organizm->GetPolozenie())
                    uniq=false;
            }
            if(uniq){
                this->SetPolozenie(nowePolozenie);
                break;
            }
        }
    }
    return true;
};

void Zwierze::Akcja(){
    Ruch();
}
void Zwierze::Kolizja(Organizm &organizm){
    if(MozeBycPartnerem(organizm)){
        organizm.SetPolozenie(organizm.GetPoprzedniePolozenie());
        if(organizm.CzyMozeSieRozmnazac()&&this->CzyMozeSieRozmnazac())
            Kopulacja(organizm);
    }
    else
        Organizm::Kolizja(organizm);
}

void Zwierze::Kopulacja(Organizm &organizm){
    if(!organizm.SprawdzCzyMoznaBezpiecznieRuszyc(1))
        return;
    Polozenie nowePolozenie;
    bool uniq=true;
    while(true) {
        uniq=true;
        nowePolozenie.setXY(organizm.GetPolozenie().GetX()+(rand()%3-1), organizm.GetPolozenie().GetY()+rand()%3-1);
        if(nowePolozenie.GetX()>=0&&nowePolozenie.GetY()>=0&& nowePolozenie.GetX()<swiat.GetPlansza().GetN()&&nowePolozenie.GetY()<swiat.GetPlansza().GetM()){
            for (Organizm *organizm1: swiat.GetOrganizmy()){
                if(nowePolozenie==organizm1->GetPolozenie())
                    uniq=false;
            }
            if(uniq){
                break;
            }
        }
    }
    this->SetZdolnoscRozrodu(false);
    organizm.SetZdolnoscRozrodu(false);
    std::cout << "Zwierze : " << this->Rysowanie() << " rozmnaza sie, a jego dziecko laduje na polu: "<< nowePolozenie << std::endl;
    swiat.NarodzOrganizm(*this, nowePolozenie);
}

