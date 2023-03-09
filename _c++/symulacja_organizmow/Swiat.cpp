//
//  Swiat.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "WszystkieOrganizmy.h"
#include "ZmienneDoWczytania.hpp"
#include <SDL2/SDL.h>
#include <fstream>
#define MIEJSCE_ZAPISU "./save.game"


Swiat::Swiat(Plansza plansza, KonfiguracjaOrganizmow konfiguracja){
    SDL_Window * window=nullptr;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = nullptr;
    window = SDL_CreateWindow("Okno do sterowania z klawiatury",
                                  200, 200, 50,
                                  50, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
    this->plansza=plansza;
    if(konfiguracja.getLacznaLiczbaOrganizmow()>plansza.GetLiczbaPol()) throw "Za duzo zwierzat!!";
    WczytajOrganizmy(konfiguracja);
    LosujPozycje();
}
void Swiat::WykonajTure(){
        SortujOrganizmy();
        PrzywrocMozliwosciRozrodu();
    for (Organizm *organizm: organizmy){
        if(organizm->SprawdzCzyZyje()){
            organizm->Akcja();
            for (Organizm *organizm2: organizmy){
                if(organizm2->SprawdzCzyZyje()&&organizm->GetPolozenie()==organizm2->GetPolozenie()&&organizm!=organizm2){
                    organizm2->Kolizja(*organizm);
                }
            }
            organizm->SetPoprzedniePolozenie(organizm->GetPolozenie());
        }
    }
        UsunMartweOrganizmy();
        AktualizujNumerRundy();
}
void Swiat::RysujSwiat() const{
    bool found;
    Polozenie polozenie = Polozenie(0,0);
    std::cout << "+-----------------------------------------+" << std::endl;
    std::cout << "|Wirtualny Swiat - Michal Tarnacki s188627|" << std::endl;
    std::cout << "+-----------------------------------------+" << std::endl;
    for(int y=0; y<plansza.GetM()+2; y++){
        for(int x=0; x<plansza.GetN()+2; x++){
            if((x==0&&y==0)||(x==0&&y==plansza.GetM()+1)||(x==plansza.GetN()+1&&y==0)||(x==plansza.GetN()+1&&y==plansza.GetM()+1))
                std::cout << '+';
            else if (x==0||x==plansza.GetN()+1)
                std::cout << '|';
            else if (y==0||y==plansza.GetM()+1)
                std::cout << '-';
            else{
                polozenie.setXY(x-1, y-1);
                found=false;
                for (Organizm *organizm: organizmy){
                    if(organizm->SprawdzCzyZyje()&&organizm->GetPolozenie()==polozenie){
                        std::cout << organizm->Rysowanie();
                        found = true;
                    }
                }
                if(!found)
                    std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Aktualna liczba organizmow:" << liczbaOrganizmow << std::endl;
}
void Swiat::Symuluj(){
    SterujCzlowiekiem(Polnoc);
    SDL_Event event;
    bool quit=false;
    bool wczytaj=false;
    WyczyscEkran();
    std::cout << "Wcisnij W aby wczytac poprzedni stan lub dowolny klawisz aby zaczac od nowa";
    while(!quit){
        while( SDL_PollEvent( &event ) ){
            switch( event.type ){
                case SDL_KEYDOWN:{
                    if(event.key.keysym.sym==SDLK_w){
                            wczytaj=true;
                            quit=true;
                        }
                    else
                        quit=true;
            }
            break;
          }
        }
    }
    if(wczytaj)
        Wczytaj();
    WyczyscEkran();
    RysujSwiat();
    while(!SprawdzCzyZostalTylkoJedenGatunek()){
        quit=false;
        while(!quit){
            while( SDL_PollEvent( &event ) ){
                switch( event.type ){
                    case SDL_KEYDOWN:{
                        if(event.key.keysym.sym==SDLK_UP){
                            SterujCzlowiekiem(Polnoc);
                            quit=true;
                            }
                        else if(event.key.keysym.sym==SDLK_RIGHT){
                            SterujCzlowiekiem(Wschod);
                            quit=true;
                        }
                        else if(event.key.keysym.sym==SDLK_DOWN){
                            SterujCzlowiekiem(Polodnie);
                            quit=true;
                        }
                        else if(event.key.keysym.sym==SDLK_LEFT){
                            SterujCzlowiekiem(Zachod);
                            quit=true;
                        }
                        else if(event.key.keysym.sym==SDLK_r){
                            if(!IstniejeCzlowiek())
                                quit=true;
                            else
                                WlaczSpecjalnaUmiejetnosc();
                        }
                        else if(event.key.keysym.sym==SDLK_s){
                            ZapiszAktualnyStan();
                            std::cout << "Zapisano aktualny stan:" << std::endl;
                        }
                        else{
                            if(!IstniejeCzlowiek())
                                quit=true;
                        }
                }
                break;
              }
            }
        }
        WyczyscEkran();
        WykonajTure();
        RysujSwiat();
    }
    remove(MIEJSCE_ZAPISU);
}
void Swiat::SortujOrganizmy(){
    std::list<Organizm*>::iterator ptrI;
    std::list<Organizm*>::iterator ptrJ;
    Organizm* organizmTmp;
    Organizm* organizmTmp2;
    for(int i=0; i<organizmy.size()-1; i++){
        ptrJ = organizmy.begin();
        ptrI = organizmy.begin();
        std::advance(ptrI, 1);
        for(int j=0; j<organizmy.size()-i-1; j++){
            organizmTmp=*ptrJ;
            organizmTmp2=*ptrI;
            if(organizmTmp->GetInicjatywa()<organizmTmp2->GetInicjatywa()||((organizmTmp->GetInicjatywa()==organizmTmp2->GetInicjatywa())&&organizmTmp->GetDlugoscZycia()<organizmTmp2->GetDlugoscZycia()))
                std::swap(*ptrI, *ptrJ);
            if(j==organizmy.size()-2){
                ptrJ = organizmy.begin();
                ptrI = organizmy.begin();
                std::advance(ptrI, 1);
            }
            else{
                std::advance(ptrJ, 1);
                std::advance(ptrI, 1);
            }
        }
    }
}

void Swiat::WczytajOrganizmy(KonfiguracjaOrganizmow konfiguracja){
    Organizm * nowyOrganizm;
    for(int i=0; i<konfiguracja.liczbaLudzi; i++){
        nowyOrganizm = new Czlowiek(*this);
        organizmy.push_back(nowyOrganizm);
    }
    for(int i=0; i<konfiguracja.liczbaAntylop; i++){
        nowyOrganizm = new Antylopa(*this);
        organizmy.push_back(nowyOrganizm);
    }
    for(int i=0; i<konfiguracja.liczbaWilkow; i++){
        nowyOrganizm = new Wilk(*this);
        organizmy.push_back(nowyOrganizm);
    }
    for(int i=0; i<konfiguracja.liczbaOwiec; i++){
        nowyOrganizm = new Owca(*this);
        organizmy.push_back(nowyOrganizm);
    }
    for(int i=0; i<konfiguracja.liczbaLisow; i++){
        nowyOrganizm = new Lis(*this);
        organizmy.push_back(nowyOrganizm);
    }
    for(int i=0; i<konfiguracja.liczbaZolwi; i++){
        nowyOrganizm = new Zolw(*this);
        organizmy.push_back(nowyOrganizm);
    }
    for(int i=0; i<konfiguracja.liczbaCyberOwiec; i++){
        nowyOrganizm = new CyberOwca(*this);
        organizmy.push_back(nowyOrganizm);
    }
    for(int i=0; i<konfiguracja.liczbaTraw; i++){
        nowyOrganizm = new Trawa(*this);
        organizmy.push_back(nowyOrganizm);
    }
    for(int i=0; i<konfiguracja.liczbaMleczy; i++){
        nowyOrganizm = new Mlecz(*this);
        organizmy.push_back(nowyOrganizm);
    }
    for(int i=0; i<konfiguracja.liczbaGuarany; i++){
        nowyOrganizm = new Guarana(*this);
        organizmy.push_back(nowyOrganizm);
    }
    for(int i=0; i<konfiguracja.liczbaWilczychJagod; i++){
        nowyOrganizm = new WilczeJagody(*this);
        organizmy.push_back(nowyOrganizm);
    }
    for(int i=0; i<konfiguracja.liczbaBarszuSosnowskiego; i++){
        nowyOrganizm = new BarszczSosnowskiego(*this);
        organizmy.push_back(nowyOrganizm);
    }
    liczbaOrganizmow=konfiguracja.getLacznaLiczbaOrganizmow();
}

void Swiat::LosujPozycje(){
    Polozenie polozenie;
    bool uniq;
    for (Organizm *organizm: organizmy){
        do{
        polozenie.setXY(rand()%plansza.GetN(),rand()%plansza.GetM());
            uniq=true;
            for (Organizm *organizm2: organizmy){
                if(polozenie==organizm2->GetPolozenie())
                    uniq=false;
            }
        } while(!uniq);
        organizm->SetPolozenie(polozenie);
        organizm->SetPoprzedniePolozenie(polozenie);
    }
};

Plansza Swiat::GetPlansza(){
    return this->plansza;
}

void Swiat::ZabijOrganizm(Organizm& organizm){
    organizm.Zabij();
    liczbaOrganizmow--;
};
void Swiat::NarodzOrganizm(Organizm& organizm, Polozenie polozenie){
    Organizm* nowyOrganizm = organizm.Urodz();
    nowyOrganizm->SetPolozenie(polozenie);
    nowyOrganizm->SetPoprzedniePolozenie(polozenie);
    nowyOrganizm->SetZdolnoscRozrodu(false);
    organizmy.push_front(nowyOrganizm);
    liczbaOrganizmow++;
};

void Swiat::UsunMartweOrganizmy(){
    Organizm* organizm=nullptr;
    for (Organizm *organizm2: organizmy){
        if(organizm!=nullptr){
            organizmy.remove(organizm);
            delete organizm;
            organizm=nullptr;
        }
        if(!organizm2->SprawdzCzyZyje())
            organizm=organizm2;
    }
    organizm=organizmy.back();
    if(!organizm->SprawdzCzyZyje()){
        organizmy.remove(organizm);
        delete organizm;
    }
}
std::list <Organizm*>& Swiat::GetOrganizmy(){
    return organizmy;
};

void Swiat::PrzywrocMozliwosciRozrodu(){
    for (Organizm *organizm: organizmy){
        if(!organizm->CzyMozeSieRozmnazac())
            organizm->SetZdolnoscRozrodu(true);
    };
}
void Swiat::AktualizujNumerRundy(){
    numerRundy++;
};
int Swiat::GetNumerRundy(){
    return numerRundy;
};
bool Swiat::SprawdzCzyZostalTylkoJedenGatunek() const {
    if(liczbaOrganizmow!=plansza.GetLiczbaPol())
        return false;
    Organizm* organizm = organizmy.front();
    for(Organizm* organizm2: organizmy){
        if(!organizm2->MozeBycPartnerem(*organizm)&&organizm2->SprawdzCzyZyje())
            return false;
    }
    return true;
};

void Swiat::ZapiszAktualnyStan(){
    std::fstream plik;
    plik.open(MIEJSCE_ZAPISU, std::ios::out);
    if(plik.is_open()==true){
        plik <<= plansza;
        plik << " " << numerRundy << " " << liczbaOrganizmow << std::endl;
        for(Organizm* organizm:organizmy){
            plik <<= *organizm;
            plik << std::endl;
        }
        plik.close();
    }
    else{
        std::cout << "nie udalo sie otworzyc pliku";
    }
};
void Swiat::Wczytaj(){
    std::fstream plik;
    plik.open(MIEJSCE_ZAPISU, std::ios::in);
    if(plik.is_open()==true){
        ZniszczSwiat();
        ZmienneDoWczytania zmienne(*this);
        plik >> zmienne.y >> zmienne.x >> zmienne.numerRundy >> zmienne.liczbaOrganizmow;
        this->plansza.set(zmienne.x,zmienne.y);
        this->numerRundy=zmienne.numerRundy;
        this->liczbaOrganizmow=zmienne.liczbaOrganizmow;
        for(int i=0; i<this->liczbaOrganizmow; i++){
            plik >> zmienne.znak;
            for(Organizm* organizm: zmienne.tymczasoweOrganizmy){
                if(zmienne.znak==organizm->Rysowanie()){
                    organizmy.push_back(organizm->Urodz());
                    plik >> zmienne.czasUrodzenia >> zmienne.sila >> zmienne.inicjatywa >> zmienne.x >> zmienne.y >> zmienne.x2 >> zmienne.y2 >> zmienne.czyZywy >> zmienne.zdolnyDoRozrodu;
                    if(dynamic_cast<Czlowiek*>(organizm))
                        plik >> zmienne.parametr1 >> zmienne.parametr2;
                    zmienne.polozenie.setXY(zmienne.x, zmienne.y);
                    zmienne.poprzedniePolozenie.setXY(zmienne.x2, zmienne.y2);
                    organizmy.back()->WczytajWlasciwosci(zmienne.sila, zmienne.inicjatywa, zmienne.polozenie, zmienne.poprzedniePolozenie, zmienne.czasUrodzenia, zmienne.czyZywy, zmienne.zdolnyDoRozrodu, zmienne.parametr1, zmienne.parametr2);
                    break;
                }
            }
        }
        plik.close();
    }
    else{
        std::cout << "nie udalo sie otworzyc pliku";
    }
}

Swiat::~Swiat(){
    ZniszczSwiat();
};
void Swiat::ZniszczSwiat(){
    for(Organizm *organizm: organizmy){
        organizm->Zabij();
        liczbaOrganizmow--;
    }
    UsunMartweOrganizmy();
}

void Swiat::WyczyscEkran() const{
    for(int i=0; i<100; i++) std::cout << std::endl;
//    system("CLEAR");
}

void Swiat::SterujCzlowiekiem(KierunekRuchu kierunek){
    Czlowiek *org;
    for(Organizm *organizm: organizmy){
        if(dynamic_cast<Czlowiek*>(organizm)){
            org=dynamic_cast<Czlowiek*>(organizm);
            org->UstawKierunekRuchu(kierunek);
        }
    }
}
void Swiat::WlaczSpecjalnaUmiejetnosc(){
    Czlowiek *org;
    for(Organizm *organizm: organizmy){
        if(dynamic_cast<Czlowiek*>(organizm)){
            org=dynamic_cast<Czlowiek*>(organizm);
            org->SpecjalnaUmiejetnosc();
        }
    }
}
bool Swiat::IstniejeCzlowiek(){
    for(Organizm *organizm: organizmy){
        if(dynamic_cast<Czlowiek*>(organizm)){
            return true;
        }
    }
    return false;
}
