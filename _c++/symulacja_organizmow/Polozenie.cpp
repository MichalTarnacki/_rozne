//
//  Polozenie.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Polozenie.hpp"
#include "Organizm.hpp"

Polozenie::Polozenie(int x, int y){
    setX(x);
    setY(y);
}
Polozenie::Polozenie(){
    setX(0);
    setY(0);
}
unsigned int Polozenie::GetX() const{
    return this->x;
}
unsigned int Polozenie::GetY() const{
    return this->y;
}
void Polozenie::setX(int x){
    this->x=x;
}
void Polozenie::setY(int y){
   this->y=y;
}
void Polozenie::setXY(int x, int y){
    setX(x);
    setY(y);
}

bool Polozenie::operator==(const Polozenie &powownywane) const{
    if(this->GetX()==powownywane.GetX()&&this->GetY()==powownywane.GetY())
        return true;
    return false;
};

Polozenie& Polozenie::operator=(const Polozenie &nowepolozenie){
    this->setX(nowepolozenie.GetX());
    this->setY(nowepolozenie.GetY());
    return *this;
};

std::ostream & operator<<(std::ostream &out, const Polozenie & polozenie){
    out << "(" << polozenie.x <<"," << polozenie.y <<")";
    return out;
}
std::ostream & operator<<=(std::ostream &out, const Polozenie & polozenie){
    out << polozenie.x << " " << polozenie.y;
    return out;
}
