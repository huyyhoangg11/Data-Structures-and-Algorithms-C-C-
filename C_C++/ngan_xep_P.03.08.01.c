#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int value;
    struct Node* next;
}Node;

Node* top;

//Tao phan tu moi
Node* makeNode(int x){
    Node* p = (Node*)malloc(sizeof(Node));
    p->value = x;
    p->next = NULL;
    return p;
}

void initStack(){
    top = NULL;
}

//Kiem tra ngan xep rong
int stackEmpty(){
    return top == NULL;
}

//Day 1 phan tu vao
void Push(int x){
    Node* p = makeNode(x);
    p->next = top;
    top = p;
}

//Lay 1 phan tu ra
int Pop(){
    if(stackEmpty()) return ' ';
    int x = top->value;
    Node*p = top; top = top->next;
    free(p);
    return x;
}

int main(){
    char cmd[0];
    while(1){
        scanf("%s", cmd);
        if(strcmp(cmd, "#") == 0) break;
        
        else if(strcmp(cmd, "PUSH") == 0){
            int v;
            scanf("%d", &v);
            Push(v);
        }

        else if(strcmp(cmd, "POP") == 0){
            if(stackEmpty()){
                printf("NULL\n");
            }else{
                int v = Pop();
                printf("%d\n", v);
            }
        }
    }
    return 0;
}