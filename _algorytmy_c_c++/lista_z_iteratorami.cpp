//
//  main.cpp
//  list
//
//  Created by Michal Tarnacki on 05/04/2022.
//
#include <iostream>
#include <string.h>
#include <stdlib.h>
#define OK 0
#define FATAL_ERROR -1
#define USER_ERROR -2
#define ULLINT unsigned long long int
#define COMMAND_SIZE 100
#define NUMBER_OF_ITERATORS 10

struct List{
    List* next=NULL;
    List* previous=NULL;
    unsigned long long int key=0;
};

enum INSERT{
    LAST,
    FIRST,
    AFTER,
    BEFORE,
    THIS,
};

enum MODE{
    PLUS,
    MINUS,
};


int Insert(List &list, ULLINT newKey, int mode){
    List* newList = (List*)malloc(sizeof(struct List));

    if(newList==NULL)
        return FATAL_ERROR;
    else if(list.previous==NULL&&list.next==NULL){
        list.next=newList;
        list.previous=newList;
        newList->next=&list;
        newList->previous=&list;
    }
    else if(list.previous!=NULL&&list.next!=NULL){
        if(mode==LAST){
            newList->next=&list;
            newList->previous=list.previous;
            list.previous->next=newList;
            list.previous=newList;
        }
        else if (mode==FIRST){
            newList->next=list.next;
            newList->previous=&list;
            list.next->previous=newList;
            list.next=newList;
        }
        else if (mode==AFTER){
            newList->next=list.next;
            newList->previous=&list;
            list.next->previous=newList;
            list.next=newList;
        }
        else if (mode==BEFORE){
            newList->next=&list;
            newList->previous=list.previous;
            list.previous->next=newList;
            list.previous=newList;
        }
        else{
            free(newList);
            return FATAL_ERROR;
        }
    }
    else{
        free(newList);
        return FATAL_ERROR;
    }
    newList->key=newKey;
    return OK;
}

int Delete(List &head, List &list,  int mode){
    List* tmp=NULL;
    if((mode==LAST||mode==FIRST)&&(&list!=&head))
        return FATAL_ERROR;
    else if(mode==THIS&&(&list==&head))
        return FATAL_ERROR;
    else if(mode==LAST){
        tmp=head.previous;
        head.previous->previous->next=&head;
        head.previous=head.previous->previous;
    }
    else if (mode==FIRST){
        tmp=head.next;
        head.next->next->previous=&head;
        head.next=head.next->next;
    }
    else if (mode==AFTER){
        tmp=list.next;
        list.next->next->previous=&list;
        list.next=list.next->next;
    }
    else if (mode==BEFORE){
        tmp=list.previous;
        list.previous->previous->next=&list;
        list.previous=list.previous->previous;
    }
    else if (mode==THIS){
        tmp=&list;
        if((tmp->previous==&head)&&(tmp->next==&head)){
            head.next=&head;
            head.previous=&head;
        }
        else{
            list.previous->next=list.next;
            list.next->previous=list.previous;
        }
    }
    else
        return FATAL_ERROR;
    if(tmp!=NULL)
        free(tmp);
    return OK;
}

int UpdateIterators(List **iterators, List &head, int number){
    List *ptr=iterators[number];
    for(int i=0; i<10; i++){
        if(iterators[i]==ptr){
            if(iterators[i]->next==&head){
                if(iterators[i]->previous==&head)
                    iterators[i]=NULL;
                else
                    iterators[i]=iterators[i]->previous;
            }
            else if(iterators[i]==&head)
                iterators[i]=NULL;
            else
                iterators[i]=iterators[i]->next;
            }
    }
    return OK;
}

int Menu_i(List& head, List** iterators, char *command, int &numberOfElements){
    int iteratorNumber;
    int number;
    List *ptr=&head;
    scanf("%d %s", &iteratorNumber, command);
    if(iteratorNumber<0||iteratorNumber>=NUMBER_OF_ITERATORS)
        return USER_ERROR;
    if(!strcmp(command, "BEG"))
        iterators[iteratorNumber]=head.next;
    else if(!strcmp(command, "END"))
        iterators[iteratorNumber]=head.previous;
    else{
        number=atoi(command);
        if(number>numberOfElements/2){
                for(int i=0; i<numberOfElements-number; i++)
                    ptr=ptr->previous;
        }
        else{
            for(int i=1; i<number+1; i++)
                ptr=ptr->next;
        }
        iterators[iteratorNumber]=ptr;
    }
    return OK;
}

int Menu_P(List& head, List** iterators, char *command, int &numberOfElements){
    List *ptr=&head;
    scanf("%s", command);
    if(!strcmp(command, "ALL")){
        for(int i=0; i<numberOfElements; i++){
            ptr=ptr->next;
            printf("%llu ", ptr->key);
        }
        printf("\n");
    }
    else {
        int number=atoi(command);
        if(number<0||number>=NUMBER_OF_ITERATORS||iterators[number]==nullptr)
            return USER_ERROR;
        printf("%llu\n", iterators[number]->key);
    }
    return OK;
}

int Menu_R(List& head, List** iterators, char *command, int &numberOfElements){
    int error=OK;
    int iteratorNumber;
    List *ptr=&head;
    scanf("%s", command);
    if(!strcmp(command, "END")){
        error=Delete(head, head, LAST);
        numberOfElements--;
    }
    else if(!strcmp(command, "BEG")){
        error=Delete(head, head, FIRST);
        numberOfElements--;
    }
    else{
        iteratorNumber=atoi(command);
        if(iteratorNumber<0||iteratorNumber>=NUMBER_OF_ITERATORS)
            return USER_ERROR;
        if(iterators[iteratorNumber]!=NULL){
            ptr=iterators[iteratorNumber];
            UpdateIterators(iterators, head, iteratorNumber);
            error=Delete(head, *ptr, THIS);
            numberOfElements--;
        }
        }
    if(error)
        return FATAL_ERROR;
    else
        return OK;
}

int Menu_Aa(List& head, List** iterators, char *command, int &numberOfElements){
    ULLINT key;
    int iteratorNumber;
    scanf("%s", command);
    if(!strcmp(command, "END")){
        scanf("%llu", &key);
        Insert(head, key, LAST);
        numberOfElements++;
    }
    else if(!strcmp(command, "BEG")){
        scanf("%llu", &key);
        if(head.next!=NULL)
            Insert(*head.next, key, AFTER);
        else
            Insert(head, key, FIRST);
        numberOfElements++;
    }
    else{
        scanf("%llu", &key);
        iteratorNumber=atoi(command);
        if(iteratorNumber<0||iteratorNumber>=NUMBER_OF_ITERATORS)
            return USER_ERROR;
        if(iterators[iteratorNumber]!=NULL){
            Insert(*iterators[iteratorNumber], key, AFTER);
            numberOfElements++;
        }
    }
    return OK;
}

int Menu_aA(List& head, List** iterators, char *command, int &numberOfElements){
    ULLINT key;
    int iteratorNumber;
    scanf("%s", command);
    if(!strcmp(command, "BEG")){
        scanf("%llu", &key);
        Insert(head, key, FIRST);
        numberOfElements++;
    }
    else if(!strcmp(command, "END")){
        scanf("%llu", &key);
        if(head.previous!=NULL)
            Insert(*head.previous, key, BEFORE);
        else
            Insert(head, key, LAST);
        numberOfElements++;
    }
    else{
        scanf("%llu", &key);
        iteratorNumber=atoi(command);
        if(iteratorNumber<0||iteratorNumber>=NUMBER_OF_ITERATORS)
            return USER_ERROR;
        if(iterators[iteratorNumber]!=NULL){
            Insert(*iterators[iteratorNumber], key, BEFORE);
            numberOfElements++;
        }
    }
    return OK;
}

int MoveIterator(int mode, List& head, List** iterators){
    int iteratorNumber;
    scanf("%d ", &iteratorNumber);
    if(iteratorNumber<0||iteratorNumber>=NUMBER_OF_ITERATORS)
        return USER_ERROR;
    if(mode==PLUS){
        if(!(iterators[iteratorNumber]->next==&head))
        iterators[iteratorNumber]=iterators[iteratorNumber]->next;
    }
    else if(mode==MINUS){
        if(!(iterators[iteratorNumber]->previous==&head))
        iterators[iteratorNumber]=iterators[iteratorNumber]->previous;
    }
    else
        return FATAL_ERROR;
    return OK;
}

int ClearMemory(List& head, int numberOfElements){
    int error=OK;
    for(int i=0; i<numberOfElements; i++){
        error=Delete(head, head, LAST);
        numberOfElements--;
    }
    if(error)
        return FATAL_ERROR;
    else
        return OK;
};


int main() {
    char command[COMMAND_SIZE];
    int error=OK;
    List head;
    List *iterators[NUMBER_OF_ITERATORS];
    for(int i=0; i<NUMBER_OF_ITERATORS; i++)
        iterators[i]=NULL;
    int numberOfElements=0;

    while(true){
        scanf("%s", command);
        if(!strcmp(command, "I"));
        else if (!strcmp(command, "i"))
            error=Menu_i(head, iterators, command, numberOfElements);
        else if (!strcmp(command, "+"))
            error=MoveIterator(PLUS, head, iterators);
        else if (!strcmp(command, "-"))
            error=MoveIterator(MINUS, head, iterators);
        else if (!strcmp(command, ".A"))
            error=Menu_aA(head, iterators, command, numberOfElements);
        else if (!strcmp(command, "A."))
            error=Menu_Aa(head, iterators, command, numberOfElements);
        else if (!strcmp(command, "R"))
            error=Menu_R(head, iterators, command, numberOfElements);
        else if (!strcmp(command, "P"))
            error=Menu_P(head, iterators, command, numberOfElements);

        if(feof(stdin)!=0||error)
        break;
    }
    ClearMemory(head, numberOfElements);
}
