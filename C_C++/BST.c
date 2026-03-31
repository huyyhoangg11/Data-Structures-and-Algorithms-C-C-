#include <stdio.h>
#include <string.h>

typedef struct Node{
    int key;
    struct Node* left;
    struct Node* right;
}Node;

Node* makeNode(int k){
    Node* p = (Node*)malloc(sizeof(Node));
    p->key = k;
    p->right = NULL;
    p->left = NULL;
    return p;
}

Node* find(Node* r, int k){
    if(r == NULL) return NULL;
    if(r->key == k) return r;
    if(r->key < k) return find(r->right,k);
    else return find(r->left, k);
}

Node* insert(Node* r, int k){
    if(r == NULL) return makeNode(k);
    if(r->key == k) return r;
    if(r->key < k) r->right = insert(r->right, k);
    else r->left = insert(r->left, k);
    return r; 
}

Node* removeRoot(Node* r){
    if(r == NULL) return NULL;
    Node* tmp = r;

    if(r->right == NULL){
        r = r->left;
        free(tmp);
        return r;
    }

    Node* p = r->right;
    Node* pp = r;

    if(p->left == NULL){
        r->key = p->key;
        tmp = p;
        r->right = p->right;
        free(tmp);
        return r;
    }

    while(p->left != NULL){
        pp = p;
        p = p->left;
    }

    r->key = p->key;
    pp->left = p->right;
    free(p);

    return r;
}

Node* remove(Node* r, int k){
    if(r == NULL) return NULL;
    if(r->key == k) return removeRoot(r);
    if(r->key < k) r->right = remove(r->right, k);
    else r->left = remove(r->left, k);
    return r;
}