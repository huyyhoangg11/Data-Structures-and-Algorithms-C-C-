#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define m 1000

typedef struct Node{
    char key[1000];
    struct Node* left;
    struct Node* right;
}Node;

Node* T[1000];

Node* makeNode(char* k){
    Node* p = (Node*)malloc(sizeof(Node));
    strcpy(p->key, k);
    p->left = NULL;
    p->right = NULL;
    return p;
}

int h(char* k){
    int c = 0;
    for(int i = 0; i < strlen(k); i++){
        c = (c*256 + k[i]) % m;
    }
    return c;
}

Node* findBST(Node* r, char* k){
    if(r == NULL) return NULL;
    int c = strcmp(r->key, k);
    if(c == 0) return r;
    if(c < 0) return findBST(r->right, k);
    else return findBST(r->left, k);
}

Node* insertBST(Node* r, char* k){
    if(r == NULL) return makeNode(k);
    if(strcmp(r->key, k) < 0){
        r->right = insertBST(r->right, k);
    }
    else{
        r->left = insertBST(r->left, k);
    }
    return r;
}

int find(char* k){
    int i = h(k);
    Node* p = findBST(T[i], k);
    if(p == NULL) return 0;
    else return 1;
}

int insert(char* k){
    int i = h(k);
    Node* p = findBST(T[i], k);
    if(p != NULL) return 0;
    T[i] = insertBST(T[i], k);
    return 1;
}

int main(){
    char k[1000], cmd[20];
    while(1){
        scanf("%s", k);
        if(strcmp(k, "*") == 0) break;
        insert(k);
    }
    while(1){
        scanf("%s", cmd);
        if(strcmp(cmd, "find") == 0){
            scanf("%s", k);
            int ans = find(k);
            printf("%d\n", ans);
        }
        else if(strcmp(cmd, "insert") == 0){
            scanf("%s", k);
            int ans = insert(k);
            printf("%d\n", ans);
        }
        else if(strcmp(cmd, "***") == 0) break;
    }
    return 0;
}