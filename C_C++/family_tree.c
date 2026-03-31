#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Khai bao cau truc cay
typedef struct Node{
    char name[256];
    struct Node* MostChild; // Con trái nhất (Left-Most Child)
    struct Node* Sibling;   // Anh em phải (Right Sibling)
} Node;

Node* root = NULL; // Khoi tao root la NULL

// Tao mot node moi
Node* makeNode(char* name){
    Node* p = (Node*)malloc(sizeof(Node));
    strcpy(p->name, name);
    p->MostChild = NULL;
    p->Sibling = NULL;
    return p;
}

// Tim kiem
Node* find(Node* r, char* name){
    if(r == NULL) return NULL;
    if(strcmp(r->name, name) == 0) return r;
    
    Node* p = r->MostChild;
    while(p != NULL){
        Node* q = find(p, name);
        if(q != NULL) return q;
        p = p->Sibling;
    }
    return NULL; // QUAN TRỌNG: Trả về NULL nếu tìm hết đám con mà không thấy
}

// Them anh em (vào cuối danh sách anh em)
Node* addLast(Node* p, char* name){
    if(p == NULL) return makeNode(name);
    p->Sibling = addLast(p->Sibling, name);
    return p;
}

// Them con
void addChild(char* name, char* child){
    Node* r = find(root, name);
    if(r == NULL) {
        printf("Cannot add child. Parent %s not found.\n", name);
        return;
    }
    r->MostChild = addLast(r->MostChild, child);
    printf("Added %s as child of %s\n", child, name);
}

// Ham tinh chieu cao (Code ban thieu ham nay)
int height(Node* p) {
    if (p == NULL) return 0;
    int maxH = 0;
    Node* q = p->MostChild;
    while (q != NULL) {
        int h = height(q);
        if (h > maxH) maxH = h;
        q = q->Sibling;
    }
    return maxH + 1;
}

// In cay ra man hinh (Pre-order traversal)
void printTree(Node* r){
    if(r == NULL) return;
    
    printf("%s: ", r->name);
    Node* p = r->MostChild;
    while(p != NULL){
        printf("%s ", p->name);
        p = p->Sibling;
    }
    printf("\n");
    
    // Goi de quy cho cac con
    p = r->MostChild;
    while(p != NULL){
        printTree(p); // Sua lai ten ham cho dung
        p = p->Sibling;
    }
}

// Ghi cay ra file (Dung cho ham Store)
void printTreeF(Node* r, FILE* f){
    if(r == NULL) return;
    fprintf(f, "%s ", r->name);
    Node* p = r->MostChild;
    while(p != NULL){
        fprintf(f, "%s ", p->name);
        p = p->Sibling;
    }
    fprintf(f, " $\n"); // Dau hieu ket thuc dong nhu trong PDF
    
    p = r->MostChild;
    while(p != NULL){
        printTreeF(p, f);
        p = p->Sibling;
    }
}

// Nhap ten tim kiem name
void processFind(){
    char name[256];
    scanf("%s", name);
    Node* p = find(root, name);
    if(p == NULL) printf("Not found %s\n", name);
    else printf("Found %s\n", name);
}

// Nhap ten tim kiem con cua name
void processFindChildren(){
    char name[256];
    scanf("%s", name);
    Node* p = find(root, name);
    if(p == NULL) printf("Not Found %s\n", name);
    else{
        printf("Found %s with children: ", name);
        Node* q = p->MostChild;
        while(q != NULL){
            printf("%s ", q->name);
            q = q->Sibling;
        }
        printf("\n");
    }
}

// Bac cua name
void processHeight(){
    char name[256];
    scanf("%s", name);
    Node* p = find(root, name);
    if(p == NULL) printf("Not Found %s\n", name);
    else{
        // Sua %s thanh %d vi height tra ve so nguyen
        printf("Found %s having height = %d\n", name, height(p)); 
    }
}

// So thanh vien
int count(Node* r){
    if(r == NULL) return 0;
    int cnt = 1;
    Node* q = r->MostChild;
    while(q != NULL){
        cnt += count(q);
        q = q->Sibling;
    }
    return cnt;
}

void processCount(){
    printf("Number of members is %d\n", count(root));
}

void processStore(){
    char filename[256];
    scanf("%s", filename);
    FILE* f = fopen(filename, "w");
    if (f == NULL) return;
    printTreeF(root, f); // Dung ham in ra file rieng
    fprintf(f, "$$");
    fclose(f);
    printf("Stored to %s\n", filename);
}

void processAddChild() {
    char name[256], child[256];
    scanf("%s %s", name, child);
    addChild(name, child);
}

void processPrint() {
    printTree(root);
}

// QUAN TRỌNG: Hàm FreeTree đúng chuẩn
void freeTree(Node* r){
    if(r == NULL) return;
    Node* p = r->MostChild;
    while(p != NULL){
        Node* sp = p->Sibling; // Luu lai dia chi nguoi em
        freeTree(p);           // Xoa de quy nhanh con cua p truoc
        p = sp;                // Chuyen sang nguoi em tiep theo
    } 
    printf("free node %s\n", r->name);
    free(r);
}

// Giả lập hàm Load (để code chạy được, bạn cần viết logic đọc file ở đây)
void processLoad() {
    if (root != NULL) freeTree(root);
    root = makeNode("David");
    addChild("David", "James");
    addChild("David", "Peter");
    addChild("David", "John");
    addChild("Peter", "Mary");
    addChild("Peter", "Daisy");
    printf("Loaded sample tree (David -> James, Peter, John...)\n");
}

int main(){
    while(1){
        char cmd[256];
        printf("Enter command: ");
        scanf("%s", cmd);
        if(strcmp(cmd, "Quit") == 0) break;
        else if(strcmp(cmd,"Load")==0) processLoad();
        else if(strcmp(cmd,"Print")==0) processPrint();
        else if(strcmp(cmd,"Find")==0) processFind();
        else if(strcmp(cmd,"FindChildren")==0) processFindChildren();
        else if(strcmp(cmd,"Height")==0) processHeight();
        else if(strcmp(cmd,"Count")==0) processCount();
        else if(strcmp(cmd,"AddChild")==0) processAddChild();
        else if(strcmp(cmd,"Store")==0) processStore();
    }
    freeTree(root);
    return 0;
}