//Przy pomocy https://www.geeksforgeeks.org/trie-insert-and-search/
#include <iostream>
#define SIZE 26
using namespace std;

class Node{
public:
    char key = NULL;
    Node *children[SIZE];
    bool end = false;
    char translate[SIZE];
    Node(){
    for(int i = 0; i<SIZE; i++)
        children[i]=NULL;
    }
};

void Add(Node *root, char* key, char *translate){
    Node *tmp = root;
    int index;
    int i=0;
    while (key[i]!='\0'){
        index = key[i] - 'a';
        if(tmp->children[index] == NULL){
            tmp->children[index] = new Node();
            tmp->children[index]->key = key[i];
        }
        tmp = tmp->children[index];
        i++;
    }
    tmp->end = true;
    for(int i=0; i<SIZE; i++)
        tmp->translate[i]=translate[i];
}

char *Search(Node *root, char* key){
    Node *tmp = root;
    int i=0;
    int index;
    while (key[i]!='\0'){
        index = key[i] - 'a';
        if(tmp->children[index] == NULL){
            key[0] = '-';
            key[1] = '\0';
            return key;
        }
        tmp = tmp->children[index];
        i++;
    }
    if(tmp->end)
        return tmp->translate;
    else {
        key[0] = '-';
        key[1] = '\0';
        return key;
    }
}

Node* GoToNode(Node* root, char* key){
    Node *tmp = root;
    int i=0;
    int index;
    while (key[i]!='\0'){
        index = key[i] - 'a';
        if(tmp->children[index] == NULL){
            return NULL;
        }
        tmp = tmp->children[index];
        i++;
    }
    return tmp;
}

void All(Node *root){
    Node *tmp = root;
    if(root->end)
        cout << root->translate << endl;
    for(int i=0; i<SIZE; i++)
        if(tmp->children[i]){
            All(tmp->children[i]);
        }
}

void Clear(Node *root){
    Node *tmp = root;
    for(int i=0; i<SIZE; i++)
        if(tmp->children[i]){
            Clear(tmp->children[i]);
            tmp->children[i] = NULL;
        }
    delete root;
}

int main(int argc, const char * argv[]) {

    char key[16];
    char translate[16];
    char command;
    Node *root = new Node();

    while(cin >> command){

        if(command == '+'){
            cin >> key >> translate;
            Add(root, key, translate);
        }
        else if(command == '?'){
            cin >> key;
            cout << Search(root, key) << endl;
        }
        else if (command == '*' ){
            cin >> key;
            Node* start = GoToNode(root, key);
            if(start != NULL)
                All(start);
            else
                cout << '-' << endl;
        }
    }
    Clear(root);
    return 0;
}
