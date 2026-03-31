#include <stdio.h>
#include <stdlib.h>

int* a[1000];
int n, m;

void input(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        a[i] = (int*)malloc(sizeof(int)*(m+1));
        for(int j = 1; j <= m; j++){
            scanf("%d", &a[i][j]);
        }
    }
}

int cmp(int i, int j){
    for(int k = 1; k <= m; k++){
        if(a[i][k] < a[j][k]) return -1;
        else if(a[i][k] > a[j][k]) return 1;
    }
    return 0;
}

void swap(int i, int j){
    int* tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void heapify(int i, int n){
    int L = 2*i, R = 2*i + 1, max = i;
    if(L <= n && cmp(max, L) < 0) max = L;
    if(R <= n && cmp(max, R) < 0) max = R;
    if( max != i){
        swap(max, i);
        heapify(max, n);
    }
}

void building(){
    for(int i = n/2; i>=1; i--){
        heapify(i, n);
    }
}

void heapSort(){
    building();
    for(int i = n; i > 1; i--){
        swap(i, 1);
        heapify(1, i-1);
    }
}

void print(){
    for(int i = 1; i<= n; i++){
        for(int j = 1; j <= m; j++){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main(){
    input();
    heapSort();
    print();
    return 0;
}