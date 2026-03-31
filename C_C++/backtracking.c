#include <stdio.h>

int n = 3, M = 5;
int X[20];
int T = 0;

void solution(){
    for(int i = 1; i <= n; i++){
        printf("%d", X[i]);
    }
    printf("\n");
}

int check(int v, int k){
    if(k < n) return 1;
    else return v + T == M;
}

void Try(int k){
    for(int v = 1; v <= M - T - (n - k); v++){
        if(check(v, k)){
            X[k] = v;
            T += v;
            if(k == n) solution();
            else Try(k + 1);
            T -= v;
        }
    }
}

int main(){
    Try(1);
    return 0;
}