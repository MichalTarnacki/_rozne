
#include <iostream>
#include <string.h>
using namespace std;

struct Data{
    int dzien;
    int rok;
    int miesiac;
};

struct Dane{
    Data data;
    char imie[100];
};

int PorownajDate(Data data1, Data data2){
    if(data1.rok>data2.rok)
        return 1;
    else if(data2.rok>data1.rok)
        return -1;
    else{
        if(data1.miesiac>data2.miesiac)
            return 1;
        else if(data2.miesiac>data1.miesiac)
            return -1;
        else{
            if(data1.dzien>data2.dzien)
                return 1;
            else if(data2.dzien>data1.dzien)
                return -1;
            else
                return 0;
        }
    }
}

class Vector{
    unsigned int Size=1;
    unsigned int numberOfElements=0;
    Dane *dane;
public:

    Vector():Size(1), numberOfElements(0){
        dane=(Dane*)malloc(Size*sizeof(struct Dane));
    }

    void Resize(unsigned int newSize){
        Dane *newDane;
        newDane=(Dane*)malloc(newSize*sizeof(struct Dane));
        for(unsigned int i=0; i<numberOfElements; i++)
            newDane[i]=dane[i];
        free(dane);
        dane=newDane;
        this->Size=newSize;
    }
    Dane at(unsigned int position){
        return dane[position];
    }
    unsigned int size(){
        return numberOfElements;
    }
    void decrement(){
        numberOfElements--;
    }
    void InsertElement(unsigned int position, Dane noweDane){
        if(position>=Size)
            Resize(2*Size);
        dane[position]=noweDane;
        if(position>=numberOfElements)
            numberOfElements++;

    }
//    void push_back(Dane noweDane){
//        if(numberOfElements>=Size)
//            Resize(2*Size);
//        dane[numberOfElements]=noweDane;
//        numberOfElements++;
//    }
//    void removeFirst(){
//        for(unsigned int i=0; i<numberOfElements-1; i++){
//            dane[i]=dane[i+1];
//        }
//        numberOfElements--;
//    }
    Dane front(){
        return dane[0];
    }
    ~Vector(){
        free(dane);
    }

};



enum Orientacja{
    MIN, //Imie
    MAX //Data
};
//WARNING??????
unsigned int Parrent(unsigned int i){
    return i/2;
}
unsigned int Left(unsigned int i){
    return i*2;
}
unsigned int Right(unsigned int i){
    return i*2+1;
}
void HeapifyName(Vector &tab, unsigned int i, unsigned int size){
    unsigned int L=Left(i);
    unsigned int R=Right(i);
    int maxps;
    if(L<=size && (strcmp(tab.at(L-1).imie, tab.at(i-1).imie)<0))
        maxps=L;
    else
        maxps=i;
    if(R<=size && (strcmp(tab.at(R-1).imie, tab.at(maxps-1).imie)<0))
        maxps = R;
    if (maxps!=i){
        Dane tmp = tab.at(i-1);
        tab.InsertElement(i-1, tab.at(maxps-1));
        tab.InsertElement(maxps-1, tmp);
        HeapifyName(tab, maxps, size);
    }
};

void HeapifyData(Vector &tab, unsigned int i, unsigned int size){
    unsigned int L=Left(i);
    unsigned int R=Right(i);
    unsigned int maxps;
    if(L<=size && (PorownajDate(tab.at(L-1).data, tab.at(i-1).data)==-1))
        maxps=L;
    else
        maxps=i;
    if(R<=size && PorownajDate(tab.at(R-1).data, tab.at(maxps-1).data)==-1)
        maxps = R;
    if (maxps!=i){
        Dane tmp = tab.at(i-1);
        tab.InsertElement(i-1, tab.at(maxps-1));
        tab.InsertElement(maxps-1, tmp);
        HeapifyData(tab, maxps, size);
    }
};


void BulidHeap(Vector &tab, unsigned int size, Orientacja orientacja){
    for(int i=Parrent(size); i>0; i--){
        if(orientacja==MIN)
            HeapifyName(tab, i, size);
        else
            HeapifyData(tab, i, size);
    }

}

void HeapInsert(Vector &tab, unsigned int size, Dane dane, Orientacja orientacja){

    size=size+1;
    int i=size;
    if(orientacja==MIN){
        while(i>1&&strcmp(tab.at(Parrent(i)-1).imie, dane.imie)>0){
            tab.InsertElement(i-1, tab.at(Parrent(i)-1));
            i=Parrent(i);
        }
    }
    else{
        while(i>1&&PorownajDate(tab.at(Parrent(i)-1).data, dane.data)==1){
            tab.InsertElement(i-1, tab.at(Parrent(i)-1));
            i=Parrent(i);
        }
    }
    tab.InsertElement(i-1, dane);

}

Dane input(){
    Dane dane;
    scanf(" %d-%d-%d %s", &dane.data.dzien, &dane.data.miesiac, &dane.data.rok, dane.imie);
    return dane;
}
void output(Dane dane){
    printf("%02d-%02d-%04d %s\n", dane.data.dzien, dane.data.miesiac, dane.data.rok, dane.imie);
}

void HeapGetMax(Vector&tab, Orientacja orientacja){
    output(tab.front());
    tab.InsertElement(0, tab.at(tab.size()-1));
    tab.decrement();
    if(orientacja==MIN)
        HeapifyName(tab, 1, tab.size());
    else
        HeapifyData(tab, 1, tab.size());
}


int main(int argc, const char * argv[]) {
    Vector tab;
    Dane dane;
    int n;
    char q='\0';
    Orientacja orientacja = MIN;
    do {
        scanf("%s", &q);
        if (q == '+') {
            cin >> n;
            for(int i=0; i<n; i++){
                dane=input();
                HeapInsert(tab, tab.size(), dane, orientacja);
            }
        }
        else if (q == '-') {
            cin >> n;
            for(int i=0; i<n; i++){
                HeapGetMax(tab, orientacja);
            }
            cout << std::endl;
        }
        else if (q == 'p'){
            for(int i=0; i<tab.size(); i++){
                output(tab.at(i));
            }
            cout << std::endl;
        }
        else if (q == 'r'){
            if(orientacja==MAX)
                orientacja=MIN;
            else
                orientacja=MAX;
            BulidHeap(tab, tab.size(), orientacja);
        }

       } while (q != 'q');
    return 0;
}
