#include <stdio.h>
#define N 100
int n;
int X[N];
int a[N];
int markR[N];
int markD1[200];
int markD2[200];
int cnt;

int check(int v, int k){
    if(markR[v]) return 0;
    if(markD1[v + k]) return 0;
    if(markD2[n + k - v]) return 0;
    return 1;
}

void Try(int k){
    if(X[k] > 0){
        if(k == n) cnt++;
        else Try(k + 1);
        return;
    }
    for(int r = 1; r <= n; r++){
        if(check(r, k)){
            X[k] = r;
            markR[r] = 1;
            markD1[r + k] = 1;
            markD2[n + k - r] = 1;
            if( k == n) cnt++;
            else Try(k + 1);
            X[k] = 0;
            markR[r] = 0;
            markD1[r + k] = 0;
            markD2[n + k - r] = 0;
        }
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= N; i++) markR[i] = 0;
    for(int i = 1; i <= 200; i++){
        markD1[i] = 0;
        markD2[i] = 0;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int e;
            scanf("%d", &e);
            if(e){
                X[j] = i;
                markR[i] = 1;
                markD1[i + j] = 1;
                markD2[n + j - i] = 1;
            }
        }
    }
    cnt = 0;
    Try(1);
    printf("%d", cnt);
    return 0;
}