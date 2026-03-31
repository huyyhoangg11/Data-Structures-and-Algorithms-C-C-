#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char s[1000000];

typedef struct Node{
    char value;
    struct Node* next;
}Node;

Node* top;

Node* makeNode(char x){
    Node* p = (Node*)malloc(sizeof(Node));
    p->value = x;
    p->next = NULL;
    return p;
}

int match(char a, char b){
    if(a == '(' && b == ')') return 1;
    if(a == '[' && b == ']') return 1;
    if(a == '{' && b == '}') return 1;
    return 0;
}

int stackEmpty(){
    return top == NULL;
}

void push(char x){
    Node* p = makeNode(x);
    p->next = top;
    top = p;
}

char pop(){
    if(stackEmpty()) return ' ';
    char x = top->value;
    Node* tmp = top;
    top = top->next;
    free(tmp);
    return x;
}

int check(char s[], int c){
    for(int i = 0; i < c; i++){
        if(s[i] == '(' || s[i] == '[' || s[i] =='{') push(s[i]);
        else{
            if(stackEmpty()) return 0;
            char open = pop();
            if(!match(open, s[i])) return 0;
        }
    }
    if(stackEmpty()) return 1;
    return 0;
}

int main(){
    scanf("%s", s);
    int c = strlen(s);
    printf("%d", check(s, c));
    return 0;
}