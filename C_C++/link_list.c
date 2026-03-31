#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int elementtype;

//node trong danh sach lien ket
typedef struct node_t{
    elementtype element;
    struct node_t* next;
} Node;

Node* root = NULL;

//Tao node moi
Node* makeNewNode(elementtype e){
    Node* newN = (Node*)malloc(sizeof(Node));
    newN->element = e;
    newN->next = NULL;
    return newN;
}

//Tim phan tu trong danh sach
Node* find(Node* root, elementtype e){
    Node* p;
    for(p = root; p != NULL; p = p->next){
        if(p->element == e) return p;
    }
    return NULL;
}

//Chen vao cuoi danh sach(khong de quy);
void insertAtTail(elementtype e){
    Node* newN = makeNewNode(e);
    if(root == NULL){
        root = newN;
        return;
    }
    Node* p = root;
    while(p->next != NULL) p = p->next;
    p->next = newN;
}

//Chen vao cuoi danh sach co de quy
Node* insertLastRecursive(Node* r, elementtype e){
    if(r == NULL) return makeNewNode(e);
    r->next = insertLastRecursive(r->next, e);
    return r;
}

//Chen vao dau danh sach
void insertAtHead(elementtype e){
    Node* newN = makeNewNode(e);
    newN->next = root;
    root = newN;
}

//Xoa phan tu e de quy
Node* removeNodeRecursive(Node* r, elementtype e){
    if(r == NULL) return NULL;

    if(r->element == e){
        Node* tmp = r;
        r = r->next;
        free(tmp);
        return r;
    }

    r->next = removeNodeRecursive(r->next, e);
    return r;
}

//giai phong danh sach
void freeList(){
    Node* p = root;
    while(p != NULL){
        Node* nxt = p->next;
        free(p);
        p = nxt;
    }
}

//Chen u vao truoc v
Node* addBefore(Node* r, elementtype u, elementtype v){
    if(r == NULL) return NULL;

    if(r->element == v){
        Node* q = makeNewNode(u);
        q->next = r;
        return q;
    }

    r->next = addBefore(r->next, u, v);
    return r;
}

//Chen u vao sau v
Node* addAfter(Node* r, elementtype u, elementtype v){
    if(r == NULL) return NULL;
    
    if(r->element == v){
        Node* q = makeNewNode(u);
        q->next = r->next;
        r->next = q;
        return r;
    }

    r->next = addAfter(r->next, u, v);
    return r;
}

//Dao nguoc danh sach
Node* reverse(Node* root){
    Node* nxt = NULL;
    Node* prev = NULL;
    Node* p = root;

    while(p != NULL){
        nxt = p->next;
        p->next = prev;
        prev = p;
        p = nxt;
    }
    return prev;
}

//in danh sach
void traverseList(Node* root){
    Node* p = root;
    while(p != NULL){
        printf("%d ", p->element);
        p = p->next;
    }
    printf("\n");
}

void solve(){
    int n;
    scanf("%d", &n);

    for(int i = 1; i <= n; i++){
        int k;
        scanf("%d", &k);
        root = insertLastRecursive(root, k);
    }

    while(1){
        char cmd[256];
        scanf("%s", cmd);

        if(strcmp(cmd, "#") == 0) break;

        if(strcmp(cmd, "addlast") == 0){
            int k;
            scanf("%d", &k);
            if(find(root, k) == NULL){
                root = insertLastRecursive(root, k);
            }
        }

        else if(strcmp(cmd, "addfirst") == 0){
            int k;
            scanf("%d", &k);
            if(find(root, k) == NULL){
                insertAtHead(k);
            }
        }

        else if(strcmp(cmd,"addafter") == 0){
            int u, v;
            scanf("%d %d", &u, &v);
            if(find(root, u) == NULL && find(root, v) != NULL){
                root = addAfter(root, u, v);
            }
        }

        else if(strcmp(cmd, "addbefore") == 0){
            int u, v;
            scanf("%d %d", &u, &v);
            if(find(root, u) == NULL && find(root, v) != NULL){
                root = addBefore(root, u, v);
            }
        }

        else if(strcmp(cmd, "remove") == 0){
            int k;
            scanf("%d", &k);
            if(find(root, k) != NULL){
                root = removeNodeRecursive(root, k);
            }
        }

        else if(strcmp(cmd, "reverse") == 0){
            root = reverse(root);
        }
    }
}

int main(){
    solve();
    traverseList(root);
    freeList();
    return 0;
}