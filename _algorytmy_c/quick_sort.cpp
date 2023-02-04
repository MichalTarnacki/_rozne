
#include <iostream>
#include <cmath>
struct Number{
    Number*next=NULL;
    char sign='\0';
};
enum NumberCompare{
    Greater,
    Smaller,
    Equal,
    Error,
};

void Insert(Number &number, char sign){
    Number* newNumber = (Number*)malloc(sizeof(struct Number));
    number.next=newNumber;
    newNumber->sign=sign;
}

int Compare(Number *num1, Number *num2){
    int condition=Equal;
    bool reverse=false;
    if(num1==NULL || num2==NULL)
        return Error;
    if(num1->next==NULL&&num2->next==NULL)
        return condition;
    else if(num1->next==NULL&&num2->next!=NULL){
        if(reverse)
            return Greater;;
        return Smaller;
    }
    else if(num1->next!=NULL&&num2->next==NULL){
        if(reverse)
            return Smaller;
        return Greater;
    }
    if(num1->next->sign=='-'&&num2->next->sign!='-')
        return Smaller;
    if(num1->next->sign!='-'&&num2->next->sign=='-')
        return Greater;
    if(num1->next->sign=='-'&&num2->next->sign=='-')
        reverse=true;
    Number *ptr1, *ptr2;
    ptr1=num1;
    ptr2=num2;
    do{
        if(ptr1->next==NULL&&ptr2->next==NULL)
            return condition;
        else if(ptr1->next==NULL&&ptr2->next!=NULL){
            if(reverse)
                return Greater;;
            return Smaller;
        }
        else if(ptr1->next!=NULL&&ptr2->next==NULL){
            if(reverse)
                return Smaller;
            return Greater;
        }
        if (condition==Equal){
            if(ptr1->next->sign>ptr2->next->sign){
                if(reverse)
                    condition=Smaller;
                else
                    condition=Greater;
            }
            else if (ptr1->next->sign<ptr2->next->sign){
                if(reverse)
                    condition=Greater;
                else
                    condition=Smaller;
            }
        }
        ptr1=ptr1->next;
        ptr2=ptr2->next;

    } while(ptr1!=NULL&&ptr1!=NULL);
    return condition;
}

void NewNumber(Number **num){
    char sign;
    Number*ptr;
    *num=(Number*)malloc(sizeof(struct Number));
    ptr=*num;
    while(1){
        sign = int(getchar());
        if(sign=='\n'||sign=='\0'||sign==' ')
            break;
        Insert(*ptr, sign);
        ptr=ptr->next;
    }
}

void Print(Number *num){
    Number* ptr=NULL;
    if(num->next!=NULL)
        ptr=num->next;
    while(ptr!=NULL){
        std::cout << (char)ptr->sign;
        ptr=ptr->next;
    }
        std::cout << std::endl;
}

void BubbleSort(Number **num, int numberOfElements){
    Number *ptr;
    for(int i=0; i<numberOfElements; i++){
        for(int j=0; j<numberOfElements-i-1; j++){
            if(Compare(num[j], num[j+1])==Greater){
                ptr=num[j];
                num[j]=num[j+1];
                num[j+1]=ptr;
            }

        }
    }
}


int Partition(Number **num, int left, int right){
    Number *ptr=num[left];
    int leftNew = left - 1;
    int rightNew = right + 1;
    while(1){
        while(1){
            leftNew++;
            if(Compare(num[leftNew], ptr)==Equal||Compare(num[leftNew], ptr)==Greater)
                break;
        }
        while(1){
            rightNew--;
            if(Compare(num[rightNew], ptr)==Equal||Compare(num[rightNew], ptr)==Smaller)
                break;
        }
        if(leftNew<rightNew){
            ptr=num[leftNew];
            num[leftNew]=num[rightNew];
            num[rightNew]=ptr;
        }
        else return rightNew;
    }
}

void QuickSort(Number **num, int left, int right){
    if(left<right){
        int newRight = Partition(num, left, right);
        QuickSort(num, left, newRight);
        QuickSort(num, newRight+1, right);
    }
}

//void FreeMem(Number **num, int numberOfElements){
//    Number*ptr;
//    for(int i=0; i<numberOfElements; i++){
//        ptr=num[i];
//        do{
//        free
//        } while(ptr->next!=NULL)'
//    }
//}

int main(int argc, const char * argv[]) {
    //GetNumber
    int numberOfElements;
    std::cin >> numberOfElements;
    Number **number = (Number**)malloc(numberOfElements*sizeof(struct Number*));
    getchar();
    for(int i=0; i<numberOfElements; i++)
        NewNumber(&number[i]);

    BubbleSort(number, numberOfElements);
    for(int i=0; i<numberOfElements; i++)
        Print(number[i]);


    return 0;
}
//
//30
//1276643
//1971115
//3751878
//3783092
//2030136
//2119971
//3302997
//2793979
//1791297
//5342003
//2631133
//2521708
//3949466
//2313055
//2367996
//3777657
//3060795
//1885485
//9439238
//1007870
//1799659
//2562403
//2949036
//3403173
//7763742
//1676884
//2458367
//2459500
//2367833
//2868662
