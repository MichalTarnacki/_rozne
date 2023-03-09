//
//  main.cpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#include <iostream>
#include "Swiat.hpp"
#include <SDL2/SDL.h>
int main(int argc, const char * argv[]) {
    
    srand((unsigned int)time(NULL));
    Plansza plansza = Plansza(10,10);
    KonfiguracjaOrganizmow konfiguracja = KonfiguracjaOrganizmow(1,0,0,0,0,0,0,0,0,0,0,0);
    Swiat swiat = Swiat(plansza, konfiguracja);
    swiat.Symuluj();
    SDL_Quit();
}
