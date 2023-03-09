//
//  Roslina.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Roslina.hpp"

Roslina::Roslina(Swiat &swiat):Organizm(swiat){}
void Roslina::SetInicjatywa(){
    this->inicjatywa=0;
}
void Roslina::Akcja(){
    if(CzyMozeSieRozmnazac())
        Zasiej();
}
void Roslina::Zasiej(){
    int x = rand() % 100;
    if(x>=(this->GetPrawdopodobienstwo()))
        return;
    if(!SprawdzCzyMoznaBezpiecznieRuszyc(1))
        return;
    Polozenie nowePolozenie;
    bool uniq=true;
    while(true) {
        uniq=true;
        nowePolozenie.setXY(polozenie.GetX()+(rand()%3-1), polozenie.GetY()+rand()%3-1);
        if(nowePolozenie.GetX()>=0&&nowePolozenie.GetY()>=0&& nowePolozenie.GetX()<swiat.GetPlansza().GetN()&&nowePolozenie.GetY()<swiat.GetPlansza().GetM()){
            for (Organizm *organizm: swiat.GetOrganizmy()){
                if(nowePolozenie==organizm->GetPolozenie())
                    uniq=false;
            }
            if(uniq){
                break;
            }
        }
    }
    this->SetZdolnoscRozrodu(false);
    std::cout << "Roslina : " << this->Rysowanie() << " zasiala na polu: "<< nowePolozenie << std::endl;
    swiat.NarodzOrganizm(*this, nowePolozenie);
}
void Roslina::SetSila(){
    this->sila=0;
}
