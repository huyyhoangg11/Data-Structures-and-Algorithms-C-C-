#include <stdio.h>
int a[10000];
int n;

//HeapSort
void swap(int i, int j){
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void heapify(int i, int n){
    int L = 2*i, R = 2*i + 1, max = i;
    if(L <= n && a[L] > a[max]) max = L;
    if(R <= n && a[R] > a[max]) max = R;
    if(max != i){
        swap(i, max);
        heapify(max, n);
    }
}

void buildHeap(){
    for(int i = n/2; i >= 1; i--) heapify(i, n);
}

void heapSort(){
    buildHeap();
    for(int i = n; i>=2; i--){
        swap(1, i);
        heapify(1, i-1);
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    heapSort();
    for(int i = 1; i <= n; i++){
        printf("%d ", a[i]);
    }
    return 0;
}