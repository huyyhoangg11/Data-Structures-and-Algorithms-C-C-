#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node{
    int id;
    struct Node* left;
    struct Node* right;
}Node;

Node* root;

Node* makeNode(int id){
    Node*p = (Node*)malloc(sizeof(Node));

    p->id = id;
    p->left = NULL;
    p->right = NULL;
    return p;
}

Node* find(Node* r, int id){
    if(r == NULL) return r;
    if(r->id == id) return r;
    Node* p = find(r->left, id);
    if(p != NULL) return p;
    return find(r->right, id);
}

void addLeft(int u, int left){
    Node* p = find(root, u);

    if(p == NULL || p->left != NULL) return;
    p->left = makeNode(left);
}

void addRight(int u, int right){
    Node* p = find(root, u);
    
    if(p == NULL || p->right != NULL) return;
    p->right = makeNode(right);
}

void load(char* filename){
    FILE* f = fopen(filename, "r");
    root = NULL;
    while(1){
        int u;
        fscanf(f, "%d", &u);
        if(u == -2) break;
        if(root == NULL) root = makeNode(u);
        int l, r;
        fscanf(f, "%d%d", &l, &r);
        if(l > -1) addLeft(u, l);
        if(r > -1) addRight(u, r);
    }
    fclose(f);
}

void printTree(Node* r){
    if(r == NULL) return;
    printf("\n%d: ", r->id);
    if(r->left == NULL) printf("left = NULL");
    else printf("left = %d", r->left->id);
    if(r->right == NULL) printf("right = NULL");
    else printf(", right = %d", r->right->id);

    printTree(r->left);
    printTree(r->right);
}

void printFTree(Node* r, FILE* f){
    if(r == NULL) return;
    fprintf(f, "%d", r->id);
    if(r->left == NULL) fprintf(f, "-1 ");
    else fprintf(f, "%d", r->left->id);
    if(r->right == NULL) fprintf(f, "-1");
    else fprintf(f, "%d", r->right->id);
    fprintf(f, "\n");

    printFTree(r->left, f);
    printFTree(r->right, f);
}

void processLoad(){
    char filename[256];
    scanf("%s", filename);
    load(filename);
}

void processFind(){
    int id;
    scanf("%d", &id);
    Node* p = find(root, id);
    if(p == NULL) return;
    else{
        printf("co");
        if(p->left == NULL) printf(" Node %d does not has leftChild",p->id);
        else printf(", LeftChild = %d",p->left->id);
        if(p->right == NULL) printf(" Node %d does not has rightChild\n",p->id);
        else printf(", RightChild = %d\n",p->right->id);
    }
}

void processPrint(){
    printTree(root);
}

void processAddLeft(){
    int id, u;
    scanf("%d %d", &id, &u);
    addLeft(id, u);
}

void processAddRight(){
    int id, u;
    scanf("%d %d", &id, &u);
    addRight(id, u);
}

int height(Node* p){
    if(p == NULL) return 0;
    int max = 0;
    int hl = height(p->left);
    if(max < hl) max = hl;
    int hr = height(p->right);
    if(max < hr) max = hr;
    return max + 1;
}

void processHeight(){
    int id;
    scanf("%d", &id);
    Node* p = find(root, id);
    if(p == NULL) return;
    else printf("%d", height(p));
}

int count(Node* p){
    if(p == NULL) return 0;
    return 1 + count(p->left) + count(p->right);
}

void printLeaves(Node* p){
    if(p == NULL) return;
    if(p->left == NULL && p->right == NULL) printf("%d", p->id);

    printLeaves(p->left);
    printLeaves(p->right);
}

void processLeaves(){
    printLeaves(root);
    printf("\n");
}

void processCount(){
    printf("%d", count(root));
}

void processStore(){
    char filename[256];
    scanf("%s", filename);
    FILE* f = fopen(filename, "w");
    printFTree(root, f);
    fprintf(f, "-2");
    fclose(f);
}

void freeTree(Node* r){
    if(r == NULL) return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
    r = NULL;
}

Node* findLCA(Node* r, int id1, int id2){
    if(r == NULL) return NULL;

    if(r->id == id1 || r->id == id2) return r;

    Node* leftLCA = findLCA(r->left, id1, id2);
    Node* rightLCA = findLCA(r->right, id1, id2);

    if(leftLCA->id != NULL && rightLCA->id != NULL) return r;
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

int main(){
    while(1){
    char cmd[256]; // representing the input command
    printf("Enter a command: ");
    scanf("%s",cmd);
    if(strcmp(cmd,"Quit") == 0) break;
    else if(strcmp(cmd,"Load")==0) processLoad();
    else if(strcmp(cmd,"Print")==0) processPrint();
    else if(strcmp(cmd,"Find")==0) processFind();
    else if(strcmp(cmd,"Height")==0) processHeight();
    else if(strcmp(cmd,"Count")==0) processCount();
    else if(strcmp(cmd,"FindLeaves")==0) processLevaves();
    else if(strcmp(cmd,"AddLeftChild")==0) processAddLeft();
    else if(strcmp(cmd,"AddRightChild")==0) processAddRight();
    else if(strcmp(cmd,"Store")==0) processStore();
    }
    freeTree(root);
}