//
//  Organizm.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Organizm.hpp"
#include <ctime>

Organizm::Organizm(Swiat& swiat): swiat(swiat){
    SetCzasUrodzenia();
};

Polozenie Organizm::GetPolozenie(){
    return polozenie;
}
void Organizm::SetPolozenie(Polozenie polozenie){
    this->polozenie=polozenie;
}

double Organizm::GetInicjatywa(){
    return this->inicjatywa;
};
double Organizm::GetSila(){
    return this->sila;
};
double Organizm::GetDlugoscZycia(){
    time_t aktualny = time(NULL);
    return aktualny - this->czasUrodzenia;
};

void Organizm::SetCzasUrodzenia(){
    czasUrodzenia=time(NULL);
}
Polozenie Organizm::GetPoprzedniePolozenie(){
    return poprzedniePolozenie;
};
void Organizm::SetPoprzedniePolozenie(Polozenie polozenie){
    poprzedniePolozenie=polozenie;
};

void Organizm::Kolizja(Organizm &organizm){
    std::cout << "Organizm: " << organizm.Rysowanie() << " atakuje organizm: " << this->Rysowanie() << " na polu:" << this->GetPolozenie() << std::endl;
    if(this->GetSila()>organizm.GetSila()){
        swiat.ZabijOrganizm(organizm);
        std::cout << "  Zwycieza: " << this->Rysowanie() << std::endl;
    }
    else{
        swiat.ZabijOrganizm(*this);
        std::cout << "  Zwycieza: " << organizm.Rysowanie() << std::endl;
    }
}
bool Organizm::SprawdzCzyZyje(){
    return this->czyZywy;
};
void Organizm::Zabij(){
    this->czyZywy=false;
};

bool Organizm::SprawdzCzyMoznaBezpiecznieRuszyc(unsigned int zasiegRuchu){ //Y to M, X to N
    Polozenie nowePolozenie;
    bool pustePole;
    for(int i=-1; i<=1; i++){
        for(int j=-1; j<=1; j++){
            nowePolozenie.setXY(this->GetPolozenie().GetX()+j*zasiegRuchu, this->GetPolozenie().GetY()+i*zasiegRuchu);
            pustePole=true;
            if(nowePolozenie.GetY()<0||nowePolozenie.GetX()<0||nowePolozenie.GetX()>=swiat.GetPlansza().GetN()||nowePolozenie.GetY()>=swiat.GetPlansza().GetM())
                pustePole=false;
            else{
                for (Organizm *organizm: swiat.GetOrganizmy()){
                    if(organizm->GetPolozenie()==nowePolozenie)
                        pustePole=false;
                    }
                }
            if(pustePole)
                return true;
        }
    }
        return false;
};
void Organizm::ZwiekszSile(double oIle){
    this->sila+=oIle;
};

bool Organizm::CzyMozeSieRozmnazac(){
    return this->zdolnyDoRozrodu;
};

void Organizm::SetZdolnoscRozrodu(bool status){
    this->zdolnyDoRozrodu=status;
};
std::ostream & Organizm::operator<<(std::ostream &out){
    out << "[" << this->Rysowanie() << "] " << "Sila: " << this->sila << " Inicjatywa: " << this->inicjatywa << " Polozenie: " <<this->polozenie << " Czy zywy: " << this->czyZywy << " Zdolny do rozrodu: " << this->zdolnyDoRozrodu;
    return out;
}

std::ostream& operator <<(std::ostream&out, Organizm& organizm){
    return organizm<<out;
}
std::ostream & Organizm::operator<<=(std::ostream &out){
    out << this->Rysowanie() << " " << this->czasUrodzenia << " " << this->sila << " " << this->inicjatywa << " ";
    out <<= this->polozenie;
    out << " ";
    out <<= this->poprzedniePolozenie;
    out << " " << this->czyZywy << " " << this->zdolnyDoRozrodu;
    return out;
}

std::ostream& operator <<=(std::ostream&out, Organizm& organizm){
    return organizm<<=out;
}

Organizm::~Organizm(){};

void Organizm::WczytajWlasciwosci(double sila, double inicjatywa, Polozenie polozenie, Polozenie poprzedniePolozenie, time_t czasUrodzenia, bool czyZywy, bool zdolnyDoRozrodu, double parametr1, double parametr2){
    this->sila=sila;
    this->inicjatywa=inicjatywa;
    this->polozenie=polozenie;
    this->poprzedniePolozenie=poprzedniePolozenie;
    this->czasUrodzenia=czasUrodzenia;
    this->czyZywy=czyZywy;
    this->zdolnyDoRozrodu=zdolnyDoRozrodu;
}


