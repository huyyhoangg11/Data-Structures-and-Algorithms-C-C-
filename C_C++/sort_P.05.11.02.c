#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* s[100000];
int n;

void input(){
    scanf("%d", &n);
    char str[1000];
    for(int i = 1; i <= n; i++){
        scanf("%s", str);
        s[i] = (char*)malloc(strlen(str)+1);
        strcpy(s[i], str);
    }
}

void swap(int i, int j){
    char* t = s[i];
    s[i] = s[j];
    s[j] = t;
}

void heapify(int i, int n){
    int L = 2*i, R = 2*i + 1, max = i;
    if(L <= n && strcmp(s[max], s[L]) < 0) max = L;
    if(R <= n && strcmp(s[max], s[R]) < 0) max = R;
    if(max != i){
        swap(max, i);
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
    for(int i = n; i >= 2; i--){
        swap(i, 1);
        heapify(1, i-1);
    }
}

int main(){
    input();
    heapSort();
    for(int i = 1; i<= n; i++){
        printf("%s ", s[i]);
    }
    return 0;
}