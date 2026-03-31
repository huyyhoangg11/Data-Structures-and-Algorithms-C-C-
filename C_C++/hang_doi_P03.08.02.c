#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int value;
    struct Node* next;
}Node;

Node* head;
Node* tail;

Node* makeNode(int v){
    Node* p = (Node*)malloc(sizeof (Node));
    p->value = v;
    p->next = NULL;
    return p;
}

//Kiem tra hang doi rong
int queueEmpty(){
    return (head == NULL) && (tail == NULL);
}

//Day 1 phan tu vao cuoi queue
void push(int x){
    Node*p = makeNode(x);
    if(queueEmpty()){
        head = p;
        tail = p;
        return;
    }
    tail->next = p;
    tail = p;
}

//Lay 1 phan tu o dau queue
int pop(){
    if(queueEmpty()){
        return -1;
    }
    Node* tmp = head;
    int v = tmp->value;
    head = head->next;
    if(head == NULL) tail = NULL;
    free(tmp);
    return v;
}

int main(){
    head = NULL;
    tail = NULL;
    char cmd[50];
    while(1){
        scanf("%s", cmd);
        if(strcmp(cmd, "#") == 0) break;

        else if(strcmp(cmd, "PUSH") == 0){
            int v;
            scanf("%d", &v);
            push(v);
        }

        else if(strcmp(cmd, "POP") == 0){
            if(queueEmpty()){
                printf("NULL\n");
            }
            else{
                int v = pop();
                printf("%d\n", v);
            }
        }
    }
    return 0;
}