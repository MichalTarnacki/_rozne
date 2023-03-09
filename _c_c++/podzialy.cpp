#include <iostream>
#include <cmath>
struct NK {
    int n;
    int k;
};
bool pierwsza(const int liczba){
    for (int i = 2; i <= sqrt(liczba); i++) {
        if (liczba % i == 0) return false;
    }
    return true;
}
int podzial[128];

void Podzial(int n, int k, int i){
    podzial[i]=k;
    if(!pierwsza(k))return;
    if(n==0){
        for(int m=0; m<i; m++) {
            std::cout << podzial[m];
            if(m<i-1) std::cout << '+';
        }
        std::cout << std::endl;
    }
    else if(n==1) return;
    else{
        if(n>1){
            if(n-k==0) Podzial(n-k, 0, i+1);
                else{
                    for(int j=2; j<=k; j++){
                        if(pierwsza(j))
                            Podzial(n-k, j, i+1);
            }
            }
        }
    }
};

int main() {
    int linie;
    std::cin >> linie;
    NK* nk = new NK[linie];
    if (nk == nullptr) return 1;
    for (int i = 0; i < linie; i++)
        std::cin >> nk[i].n >> nk[i].k;
    for (int i = 0; i < linie; i++)
        Podzial(nk[i].n, nk[i].k, 0);
    delete[] nk;
    return 0;
}
