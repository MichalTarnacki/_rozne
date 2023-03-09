//
//  Czlowiek.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Czlowiek.hpp"
#include <SDL2/SDL.h>
Czlowiek::Czlowiek(Swiat &swiat):Zwierze(swiat){
    SetInicjatywa();
    SetSila();
};

void Czlowiek::Akcja(){
    if(czyRuchAntylopyAktywny){
        if(swiat.GetNumerRundy()-czasAktywacji<3)
            Ruch(2);
        else if (swiat.GetNumerRundy()-czasAktywacji<5){
            int x=rand()%100;
            if(x>=50)
                Ruch(2);
            else
                Ruch(1);
        }
        else{
            czyRuchAntylopyAktywny=false;
            Czlowiek::Akcja();
            }
    }
    else
        Zwierze::Akcja();
}
void Czlowiek::Ruch(unsigned int zasiegRuchu){
    Polozenie nowePolozenie;
    if(kierunek==Sterowany){
        char kierunek='\0';
        SDL_Event event;
        swiat.RysujSwiat();
        int x,y;
        do {
            do{
                while( SDL_PollEvent( &event ) ){
                    switch( event.type ){
                        case SDL_KEYDOWN:{
                            switch(event.key.keysym.sym){
                                case SDLK_UP:{
                                    kierunek='w';
                                    break;
                                }
                                case SDLK_DOWN:{
                                    kierunek='s';
                                    break;
                                }
                                case SDLK_LEFT:{
                                    kierunek='a';
                                    break;
                                }
                                case SDLK_RIGHT:{
                                    kierunek='d';
                                    break;
                                }
                                case SDLK_r:{
                                    kierunek='r';
                                    break;
                                }
                            }
                        }
                    }
                    break;
                  }
                if(kierunek=='r'){
                    SpecjalnaUmiejetnosc();
                    return;
                }
            } while(kierunek!='w'&&kierunek!='a'&&kierunek!='s'&&kierunek!='d');
            if(kierunek=='w'){
                x=0;
                y=-1;
            }
            else if(kierunek=='a'){
                x=-1;
                y=0;
            }
            else if(kierunek=='s'){
                x=0;
                y=1;
            }
            else{
                x=1;
                y=0;
            }

            nowePolozenie.setXY(polozenie.GetX()+zasiegRuchu*x, polozenie.GetY()+zasiegRuchu*y);
        } while (nowePolozenie==polozenie||nowePolozenie.GetX()<0 || nowePolozenie.GetY()<0 || nowePolozenie.GetX()>=swiat.GetPlansza().GetN()||nowePolozenie.GetY()>=swiat.GetPlansza().GetM());
        swiat.WyczyscEkran();
    }
    else{
        nowePolozenie=polozenie;
        if(kierunek==Zachod)
            nowePolozenie.setXY(polozenie.GetX()-zasiegRuchu, polozenie.GetY());
        else if(kierunek==Wschod)
            nowePolozenie.setXY(polozenie.GetX()+zasiegRuchu, polozenie.GetY());
        else if (kierunek==Polnoc)
            nowePolozenie.setXY(polozenie.GetX(), polozenie.GetY()-zasiegRuchu);
        else if(kierunek==Polodnie)
            nowePolozenie.setXY(polozenie.GetX(), polozenie.GetY()+zasiegRuchu);
        if(nowePolozenie.GetX()<0 || nowePolozenie.GetY()<0 || nowePolozenie.GetX()>=swiat.GetPlansza().GetN()||nowePolozenie.GetY()>=swiat.GetPlansza().GetM())
            nowePolozenie=polozenie;
    }
    polozenie=nowePolozenie;
}
char Czlowiek::Rysowanie() const{
    return '+';
}
void Czlowiek::SetInicjatywa(){
    this->inicjatywa=5;
}
void Czlowiek::SetSila(){
    this->sila=9;
}
Organizm* Czlowiek::Urodz(){
    return new Czlowiek(this->swiat);
}
bool Czlowiek::MozeBycPartnerem(Organizm& organizm){
    if(dynamic_cast<Czlowiek*>(&organizm))
       return true;
    else
       return false;
}
void Czlowiek::SpecjalnaUmiejetnosc(){
    if(!czyRuchAntylopyAktywny){
        if(czasAktywacji==-1||swiat.GetNumerRundy()-czasAktywacji>9){
        czyRuchAntylopyAktywny=true;
        czasAktywacji=swiat.GetNumerRundy();
        std::cout << "Czlowiek aktywowal specjalna umiejetnosc" << std::endl;
        }
    }
    if(this->kierunek==Sterowany)
        Czlowiek::Akcja();
};

std::ostream & Czlowiek::operator<<(std::ostream &out){
    Organizm::operator<<(out);
    out << " Czy ruch antylopy aktywny:" << this->czyRuchAntylopyAktywny << " Czas aktywacji: " << this->czasAktywacji;
    return out;
}
std::ostream & Czlowiek::operator<<=(std::ostream &out){
    Organizm::operator<<=(out);
    out << " " << this->czyRuchAntylopyAktywny << " " << this->czasAktywacji;
    return out;
}

void Czlowiek::WczytajWlasciwosci(double sila, double inicjatywa, Polozenie polozenie, Polozenie poprzedniePolozenie, time_t czasUrodzenia, bool czyZywy, bool zdolnyDoRozrodu, double parametr1, double parametr2){
    this->czyRuchAntylopyAktywny=parametr1;
    this->czasAktywacji=parametr2;
    Organizm::WczytajWlasciwosci(sila, inicjatywa, polozenie, poprzedniePolozenie, czasUrodzenia, czyZywy, zdolnyDoRozrodu);
}

void Czlowiek::UstawKierunekRuchu(KierunekRuchu kierunek){
    this->kierunek=kierunek;
}
