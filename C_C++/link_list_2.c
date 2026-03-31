#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int n;

typedef struct Node{
    char id[10];
    int grade;
    int pos;
}ds;

ds a[10000];

void input(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%s %d", a[i].id, &a[i].grade);
    }
}

void swap(int i, int j){
    ds tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void heapify(int i, int n){
    int L = 2*i, R = 2*i + 1, max = i;
    if(L <= n && a[L].grade > a[max].grade) max = L;
    if(R <= n && a[R].grade > a[max].grade) max = R;
    if(max != i){
        swap(i, max);
        heapify(max, n);
    }
}

void building(){
    for(int i = n/2; i >= 1; i--){
        heapify(i, n);
    }
}

void heapSort(){
    building();
    for(int i = n; i > 1; i--){
        swap(i, 1);
        heapify(1, i - 1);
    }
}

void heapify2(int i, int n){
    int L = 2*i, R = 2*i + 1, max = i;
    if(L <= n && strcmp(a[L].id, a[max].id) > 0) max = L;
    if(R <= n && strcmp(a[R].id, a[max].id) > 0) max = R;
    if(max != i){
        swap(max, i);
        heapify2(max, n);
    }
}

void building2(){
    for(int i = n/2; i >= 1; i--){
        heapify2(i, n);
    }
}

void heapSort2(){
    building2();
    for(int i = n; i > 1; i--){
        swap(i, 1);
        heapify2(1, i-1);
    }
}

void print(){
    printf("Input:\n");
    for(int i = 1; i <= n; i++){
        printf("%s %d\n", a[i].id, a[i].pos);
    }
}

int main(){
    input();
    heapSort();
    for(int i = 1; i <= n; i++){
        a[i].pos = i - 1;
    }
    heapSort2();
    print();
    return 0;
}