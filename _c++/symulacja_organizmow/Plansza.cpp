//
//  Plansza.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include "Plansza.hpp"

Plansza::Plansza(int n, int m){
    setN(n);
    setM(m);
}
Plansza::Plansza(){
    setN(20);
    setM(20);

}
Plansza::Plansza(Plansza& plansza){
    setN(plansza.GetN());
    setM(plansza.GetM());
}
unsigned int Plansza::GetN() const{
    return N;
}
unsigned int Plansza::GetM() const{
    return M;
}
unsigned int Plansza::GetLiczbaPol() const{
    return M*N;
}
void Plansza::setN(int n){
    if(n<=0) throw "Podano zbyt małe N";
    else N=n;
}
void Plansza::setM(int m){
    if(m<=0) throw "Podano zbyt małe M";
    else M=m;
}
void Plansza::set(int n, int m){
    setM(m);
    setN(n);
}
std::ostream& operator <<(std::ostream&out, Plansza& plansza) {
    out << "Plansza: " << plansza.M << "x" << plansza.N;
    return out;
}
std::ostream& operator <<=(std::ostream&out, Plansza& plansza) {
    out << plansza.M << " " << plansza.N;
    return out;
}
