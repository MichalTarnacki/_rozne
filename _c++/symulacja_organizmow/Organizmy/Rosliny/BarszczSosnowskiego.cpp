//
//  BarszczSosnowskiego.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "BarszczSosnowskiego.hpp"
#include "CyberOwca.hpp"

BarszczSosnowskiego::BarszczSosnowskiego(Swiat &swiat):Roslina(swiat){

}
void BarszczSosnowskiego::Akcja(){
    ZabijWokolo();
    Roslina::Akcja();
}
void BarszczSosnowskiego::Kolizja(Organizm& organizm){
    if(!dynamic_cast<CyberOwca*>(&organizm))
        swiat.ZabijOrganizm(organizm);
}
char BarszczSosnowskiego::Rysowanie() const{
    return 'b';
}
void BarszczSosnowskiego::SetSila(){
    this->sila=9;
}

void BarszczSosnowskiego::ZabijWokolo(){
    bool juzZabil = false;
    Polozenie nowePolozenie;
    for(int i=-1; i<=1; i++){
        for(int j=-1; j<=1; j++){
            nowePolozenie.setXY(this->GetPolozenie().GetX()+j, this->GetPolozenie().GetY()+i);
            if(nowePolozenie.GetY()<0||nowePolozenie.GetX()<0||nowePolozenie.GetX()>=swiat.GetPlansza().GetN()||nowePolozenie.GetY()>=swiat.GetPlansza().GetM());
            else{
                for (Organizm *organizm: swiat.GetOrganizmy()){
                    if(organizm->SprawdzCzyZyje()&&organizm->GetPolozenie()==nowePolozenie&&organizm!=this&&!dynamic_cast<BarszczSosnowskiego*>(organizm)&&!dynamic_cast<CyberOwca*>(organizm))
                    {
                        if(juzZabil==false){
                            std::cout << "Barszcz " << this->polozenie << " zabija wszystkich wokoło" << std::endl;
                            juzZabil=true;
                        }
                        swiat.ZabijOrganizm(*organizm);
                        std::cout << "  Ginie: " << organizm->Rysowanie() << " " << organizm->GetPolozenie()<< std::endl;
                    }
                    }
                }
        }
    }
}

Organizm* BarszczSosnowskiego::Urodz(){
    return new BarszczSosnowskiego(this->swiat);
}
int BarszczSosnowskiego::GetPrawdopodobienstwo(){
    return 5;
}
bool BarszczSosnowskiego::MozeBycPartnerem(Organizm& organizm){
    if(dynamic_cast<BarszczSosnowskiego*>(&organizm))
       return true;
    else
       return false;
}
