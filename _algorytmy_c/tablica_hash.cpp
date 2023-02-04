//  Created by Michal Tarnacki on 16/05/2022.
//
#include <string>
#include <iostream>
#define SIZE 1000000
using namespace std;

struct List{
    int key=0;
    string imie;
    string nazwisko;
    List *next=NULL;
};

class HashTable{
    List *lista;
public:
    HashTable(){
        lista=new List[SIZE];
    }
    int GetHash(string s1, string s2){
        int hash=0;
        int i=0;
        while(i<s1.size()&&i<s2.size()){
            hash+=s1[i]*(s2[i]%5);
            i++;
        }
        return hash%SIZE;
    }
    int GetElement(string s1, string s2){
        int i = GetHash(s1, s2);
        List *list=&lista[i];
        do{
            if(list->imie==s1&&list->nazwisko==s2)
                return list->key;
            if(list->next!=NULL)
                list=list->next;
        } while(list->next!=NULL);
        if(list->imie==s1&&list->nazwisko==s2)
            return list->key;
        else
            return 0;
    }
    void InsertElement(string s1, string s2, int num){
        int i = GetHash(s1, s2);
        List *list=&lista[i];
        while(list->next!=NULL){
            if(list->imie==s1&&list->nazwisko==s2){
                list->key+=num;
                return;
            }
            list=list->next;
        }
        if(list->imie==s1&&list->nazwisko==s2){
            list->key+=num;
            return;
        }
        list->next=new List;
        list=list->next;
        list->key+=num;
        list->imie=s1;
        list->nazwisko=s2;
        ;
    }
    void ClearMem(){
        List *list, *tmplist;
        for(int i=0; i<SIZE; i++){
            list=&lista[i];
            if(list->next!=NULL){
                list=list->next;
                if(list->next!=NULL){
                    while(list->next!=NULL){
                        tmplist=list;
                        list=list->next;
                        delete tmplist;
                    }
                }
                else
                    delete list;
            }
        }
    }
    ~HashTable(){
        ClearMem();
        delete[] lista;
    }
};

#include <iostream>

int main(int argc, const char * argv[]) {
    HashTable hash;
    string s, a, b ,c;
    int n;

    while (cin >> s) {

        if(s=="+"){
            cin >> a >> b >> n;
            hash.InsertElement(a, b, n);
        }
        else if(s=="?"){
            cin >> a >> b;
            cout << (int)hash.GetElement(a, b) << '\n';
        }
    }
    return 0;
}
