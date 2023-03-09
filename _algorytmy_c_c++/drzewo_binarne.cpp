
#include <iostream>
using namespace std;

struct Node{
    unsigned int key = NULL;
    Node *parent = NULL;
    Node *left = NULL;
    Node *right = NULL;
};

Node* Minimum(Node*node){
    while(node->left != NULL){
        node = node->left;
    }
    return node;
}
Node* Maximum(Node*node){
    while(node->right != NULL){
        node = node->right;
    }
    return node;
}

Node* Succesor(Node *node){
    Node *tmp;
    if(node->right != NULL)
        return Minimum(node->right);
    tmp = node->parent;
    while(tmp != NULL && node == tmp->right){
        node = tmp;
        tmp = tmp->parent;
    }
    return tmp;
}

Node* Add(Node *root, Node *node, unsigned int key){
    Node *parent = NULL;
    if (root == NULL){
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    Node *tmp = root;
    while (tmp != NULL){
        parent = tmp;
        if (node->key < tmp->key)
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }
    node->parent = parent;
    if (node->key < parent->key)
        parent->left = node;
    else
        parent->right = node;
    return root;
}

Node* Remove(Node *root, Node *node){
    Node *ret = root;
    Node *toDelete;
    Node *son;
    if (node->left == NULL || node->right == NULL)
        toDelete = node;
    else
        toDelete = Succesor(node);
    if(toDelete->left != NULL)
        son = toDelete->left;
    else
        son = toDelete->right;
    if (son != NULL)
        son->parent = toDelete->parent;
    if (toDelete->parent == NULL)
        ret = son;
    else if(toDelete == toDelete->parent->left)
        toDelete->parent->left = son;
    else
        toDelete->parent->right = son;
    if(toDelete != node){
        node->key = toDelete->key;
    }
    return ret;
}

Node* Search(Node* node, unsigned int key){
    while(node!= NULL && node->key != key){
        if(key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

void Clear(Node* node){
    if(node->right != NULL)
        Clear(node->right);
    if(node->left != NULL)
        Clear(node->left);
    if(node->left == NULL && node->right == NULL){
        if(node->parent != NULL){
            if(node == node->parent->right)
                node->parent->right = NULL;
            if(node == node->parent->left)
                node->parent->left = NULL;
        }
        delete node;
    }
}

int main(int argc, const char * argv[]) {

    unsigned int key;
    char command;
    Node *root=NULL;
    Node *newNode=NULL;

    while(1){
        cin >> command;
        if(command == '+'){
            cin >> key;
            newNode = new Node;
            newNode->key = key;
            root=Add(root, newNode, key);
        }
        else if(command == '-'){
            cin >> key;
            newNode = Search(root, key);
            if(newNode != NULL){
                root=Remove(root, newNode);
            }

        }
        else if (command == '?' ){
            cin >> key;
            newNode = Search(root, key);
            if(newNode != NULL)
                cout << 1 << endl;
            else
                cout << 0 << endl;
        }
        else if(command == 'm'){
            if(root != NULL)
                cout << Minimum(root)->key;
        }
        else if(command == 'M'){
            if(root != NULL)
                cout << Maximum(root)->key;
        }
        else if(command == 'q')
            break;
    }
    Clear(root);
    return 0;
}
//+ 16 + 10 + 19 + 5 + 12 + 17 + 20 + 1 + 6 + 14 + 13 + 15
