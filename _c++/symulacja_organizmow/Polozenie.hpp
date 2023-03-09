//
//  Polozenie.hpp
//  WirtualnySwiat
//
//  Created by Michal Tarnacki on 10/04/2022.
//

#ifndef Polozenie_hpp
#define Polozenie_hpp

#include <stdio.h>
#include <iostream>

class Polozenie{
    unsigned int x, y;
public:
    Polozenie(int x, int y);
    Polozenie();
    unsigned int GetX() const;
    unsigned int GetY() const;
    void setX(int x);
    void setY(int y);
    void setXY(int x, int y);
    bool operator==(const Polozenie &powownywane) const;
    Polozenie& operator=(const Polozenie &nowepolozenie);
    friend std::ostream & operator<<(std::ostream &out, const Polozenie & polozenie);
    friend std::ostream & operator<<=(std::ostream &out, const Polozenie & polozenie);
};


#endif /* Polozenie_hpp */
