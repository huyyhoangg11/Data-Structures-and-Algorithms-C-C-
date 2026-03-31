#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student{
    char id[10];
    int grade;
    int pos;
} danhsach;

danhsach s[10000];
int n;

void input(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%s %d", s[i].id, &s[i].grade);
    }
}

void swap(int i, int j){
    danhsach tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
}

void heapify(int i, int n){
    int L = 2*i, R = 2*i+ 1, max =i;
    if(L <= n && s[L].grade > s[max].grade) max = L;
    if(R <= n && s[R].grade > s[max].grade) max = R;
    if(max != i){
        swap(max, i);
        heapify(max, n);
    }
}

void building(){
    for(int i = n/2; i >=1; i--){
        heapify(i, n);
    }
}

void heapSort(){
    building();
    for(int i = n; i>= 2; i--){
        swap(i, 1);
        heapify(1, i-1);
    }
}

void heapify2(int i, int n){
    int L = 2*i, R = 2*i+ 1, max =i;
    if(L <= n && strcmp(s[max].id, s[L].id) < 0) max = L;
    if(R <= n && strcmp(s[max].id, s[R].id) < 0) max = R;
    if(max != i){
        swap(i, max);
        heapify2(max, n);
    }
}

void building2(){
    for(int i = n/2; i>=1; i--){
        heapify2(i, n);
    }
}

void heapSort2(){
    building2();
    for(int i = n; i >= 2; i--){
        swap(i, 1);
        heapify2(1, i-1);
    }
}

void print(){
    for(int i =1 ; i <= n; i++){
        printf("%s %d\n", s[i].id, s[i].pos);
    }
}

int main(){
    input();
    heapSort();
    for(int i = 1; i <= n; i++){
        s[i].pos = i-1;
    }
    heapSort2();
    printf("Ket qua la:\n");
    print();
    return 0;
}