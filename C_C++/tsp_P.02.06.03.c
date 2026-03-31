#include <stdio.h>
int n;
int d[100][100];
int x[100];
int mark[100];
int f, f_min;
int Cm;

void Try(int k){
    for(int v = 2; v <= n; v++){
        if(!mark[v]){
            x[k] = v;
            f = f + d[x[k-1]][v];
            mark[v] = 1;
            if(k == n){
                if(f_min > f + d[x[n]][x[1]]) f_min = f + d[x[n]][x[1]];
            }
            else{
                if( f + Cm*(n - k + 1) < f_min) Try(k + 1);
            }
            mark[v] = 0;
            f = f - d[x[k-1]][v];
        }
    }
}

int main(){
    scanf("%d", &n);
    Cm = 10000000;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            scanf("%d", &d[i][j]);
            if(i != j && d[i][j] < Cm){
                Cm = d[i][j];
            }
        }
    }
    for(int i = 1; i <= n; i++){
        mark[i] = 0;
    }
    x[1] = 1;
    mark[1] = 1;
    f = 0;
    f_min = 100000000;
    Try(2);
    printf("%d", f_min);
    return 0;
}