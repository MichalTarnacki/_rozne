//
//  Lis.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Lis.hpp"
Lis::Lis(Swiat &swiat):Zwierze(swiat){
    
}
void Lis::Akcja(){
    Zwierze::Akcja();
    for (Organizm *organizm: swiat.GetOrganizmy()){
        if(organizm->GetSila()>this->GetSila()&&organizm->GetPolozenie()==this->GetPolozenie()){
            this->SetPolozenie(this->GetPoprzedniePolozenie());
            std::cout << "Lis chcial isc na pozycje: " << organizm->GetPolozenie() << " ale wytropil: " << organizm->Rysowanie() << " i nie idzie dalej " << std::endl;
        }
    }
}
char Lis::Rysowanie() const{
    return 'L';
}
void Lis::SetInicjatywa(){
    this->inicjatywa=7;
}
void Lis::SetSila(){
    this->sila=3;
}
Organizm* Lis::Urodz(){
    return new Lis(this->swiat);
}
bool Lis::MozeBycPartnerem(Organizm& organizm){
    if(dynamic_cast<Lis*>(&organizm))
       return true;
    else
       return false;
}

