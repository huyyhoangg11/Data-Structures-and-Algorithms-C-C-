#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 901

typedef struct Node{
    int x;
    int y;
    struct Node* next;
}Node;

Node* head;
Node* tail;

int visit[MAX][MAX];
int level[MAX][MAX];
int ans = -1;
int cap_a, cap_b, target_c;

Node* makeNode(int x, int y){
    Node* p = (Node*)malloc(sizeof(Node));
    p->x = x;
    p->y = y;
    p->next =NULL;
    return p;
}

int queueEmpty(){
    return head == NULL;
}

void push(int x, int y){
    Node* p = makeNode(x, y);
    if(queueEmpty()){
        head = p;
        tail = p;
        return;
    }
    tail->next = p;
    tail = p;
}

Node* pop(){
    if(queueEmpty()) return NULL;

    Node* tmp = head;
    head = head->next;
    return tmp;
}

int goal(int x, int y){
    return (x == target_c || y == target_c);
}

int process(int nx, int ny, int cur_x, int cur_y){
    if(visit[nx][ny]) return 0;

    visit[nx][ny] = 1;
    level[nx][ny] = level[cur_x][cur_y] + 1;
    push(nx, ny);

    if(goal(nx, ny)){
        ans = level[nx][ny];
        return 1;
    }
    return 0;
}

void solve(){
    head = NULL;
    tail = NULL;
    for(int i = 0; i <= cap_a; i++){
        for(int j = 0; j <= cap_b; j++){
            visit[i][j] = 0;
        }
    }

    push(0, 0);
    visit[0][0] = 1;
    level[0][0] = 0;

    if( target_c == 0){
        ans = 0;
        return;
    }

    while(!queueEmpty()){
        Node* current = pop();
        int x = current->x;
        int y = current->y;
        free(current);

        //1. Do day A
        if(process(cap_a, y, x, y)) break;

        //2. Do day B
        if(process(x, cap_b, x, y)) break;

        //3. Do het A
        if(process(0, y, x, y)) break;

        //4. Do het B
        if(process(x, 0, x, y)) break;

        //5. A sang B
        int nx, ny;
        if(x + y > cap_b){
            nx = x + y - cap_b;
            ny = cap_b;
        }
        else{
            nx = 0;
            ny = x + y;
        }
        if(process(nx, ny, x, y)) break;

        //6. B sang A
        if(x + y > cap_a){
            nx = cap_a;
            ny = x + y - cap_a;
        }
        else{
            nx = x + y;
            ny = 0;
        }
        if(process(nx, ny, x, y)) break;
    }
}

int main(){
    if(scanf("%d %d %d", &cap_a, &cap_b, &target_c) != 3) return 1;
    solve();
    printf("%d", ans);
    return 0;
}