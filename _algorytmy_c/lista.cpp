//  Created by Michal Tarnacki on 28/03/2022.
//
#include <iostream>
using namespace std;
struct list{
    list* next = NULL;
    int key = NULL;
    list *end = NULL;
};


void insertLast(list &lista, int &key){
    list *tmp = &lista;

    if(lista.end==NULL){
        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
    }
    else{
        tmp=lista.end;
    }
    tmp->next = new list;
    tmp->next->end=tmp;
    tmp->next->key = key;
    lista.end=tmp->next;
};
void deleteLast(list &lista){
    list *tmp=lista.end;
    list *tmp2=lista.end->end;
    lista.end=tmp2;
    tmp2->next=NULL;
    cout << tmp->key << endl;
    delete tmp;
};

int getElement(list &lista, int &index){
    list *tmp = lista.next;
    for(int i=0; i<index; i++){
            if(tmp->next == NULL)
                return -1;
            tmp=tmp->next;

        }
    return tmp->key;
};



int main(int argc, const char * argv[]) {
    char q;
    int key;
    list lista;
    do{
        cin >> q;
        if(q=='i'){
            cin >> key;
            insertLast(lista, key);
        }
        if(q=='d')
            deleteLast(lista);
        if(q=='g'){
            cin >> key;
            cout << getElement(lista, key) << endl;
        }
    }
    while(q!='q');

}
