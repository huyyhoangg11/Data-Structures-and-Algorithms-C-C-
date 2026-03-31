#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct TrieNode{
    int End;
    int count;
    struct TrieNode *children[26];
}Node;

//Ham tao nut moi
Node* makeNode(){
    Node* p = (Node*)malloc(sizeof(Node));
    p->End = 0;
    p->count = 0;
    for(int i = 0; i < 26; i++){
        p->children[i] = NULL;
    }
    return p;
}

//Ham them tu vao cay prefix
void insertWord(Node* root, char* word){
    Node* cur = root;
    for(int i = 0; word[i] != '\0'; i++){
        int index = word[i] - 'a';
        if(!cur->children[index]){
            cur->children[index] = makeNode();
        }
        cur = cur->children[index];
        cur->count++;
    }
    cur->End = 1;
}

//Ham doc doan van
void processText(Node* root, char* paragraph){
    char word[50];
    int j = 0;
    for(int i = 0; paragraph[i] != '\0'; i++){
        if(isalpha(paragraph[i])){
            word[j++] = tolower(paragraph[i]);
        }
        else if(j > 0){
            word[j++] = '\0';
            insertWord(root, word);
            j = 0;
        }
    }

    if(j > 0){
        word[j] = '\0';
        insertWord(root, word);
    }
}

//ham kiem tra tu co trong cay Prefix hay khong
int searchWord(Node* root, char* word){
    Node* cur = root;
    for(int i = 0; word[i] != '\0'; i++){
        int index = word[i] - 'a';
        if(!cur->children[index]){
            return 0;
        }
        cur = cur->children[index];
    }
    return (cur != NULL && cur->End);
}

//Ham duyet va in ra tat ca cac tu trong cay prefix word la mang chua cac ky tu o phia truoc
void traverseTrie(Node* root, char word[], int level){
    if(root->End){
        word[level] = '\0';
        printf("%s\n", word);
    }
    for(int i = 0; i < 26; i++){
        if(root->children[i]){
            word[level] = 'a' + i;
        traverseTrie(root->children[i], word, level + 1);
        }
    }
}

//Ham kiem tra tu co trong cay prefix hay khong va in ra
void printfWord(Node* root, char* word){
    Node* cur = root;
    for(int i = 0; word[i] != '\0'; i++){
        int index = word[i] - 'a';
        if(!cur->children[index]){
            return;
        }
        cur = cur->children[index];
    }
    if(cur == NULL) return;

    //Duyet va in ra tat ca cac tu trong cay prefix
    char prefixWord[50];
    strcpy(prefixWord, word);
    int level = strlen(prefixWord);

    traverseTrie(cur, prefixWord, level);
}

//Ham dem tan suat
int max = 0;

void findMax(Node* root, int k, int level, char path[]){
    if(root == NULL || level > k) return;

    if(level == k){
        if(root->count > max) max = root->count;
    }

    for(int i = 0; i < 26; i++){
        if(root->children[i]){
            findMax(root->children[i], k, level + 1, path);
        }
    }
}

void printMax(Node* root, int k, int level, char path[]){
    if(root == NULL || level > k) return;

    if(level == k){
        if(root->count == max){
            path[level] = '\0';
            printf("Prefix '%s' xuat hien %d lan\n", path, max);
        }
        return;
    }

    for(int i = 0; i < 26; i++){
        if(root->children[i]){
            path[level] = 'a' + i;
            printMax(root->children[i], k, level + 1, path);
        }
    }
}

//Ham xoa 1 tu cu the
int check(Node* root){
    for(int i = 0; i < 26; i++){
        if(root->children[i]) return 1;
    }
    return 0;
}

Node* deleteWord(Node* root, char* word, int level){
    if(root == NULL) return NULL;

    if(word[level] == '\0'){
        if(root->End) root->End = 0;
        if(!check(root)){
            free(root);
            root = NULL;
        }
        return root;
    }
    
    int index = word[level] - 'a';
    root->children[index] = deleteWord(root->children[index], word, level + 1);

    if(!check(root) && root->End == 0){
        free(root);
        root = NULL;
    }
    return root;
}

//Ham xoa toan bo cay
void freeTrie(Node* root){
    if(!root) return;
    for(int i = 0; i < 26; i++){
        freeTrie(root->children[i]);
    }
    free(root);
}

int main() {
    Node* root = makeNode();
    char doc[] = "Hello world! Hello BKHN, hello Hanoi.";
    
    processText(root, doc); // Yêu cầu 1: Đọc và chuẩn hóa
    
    // Yêu cầu 2: Tìm prefix độ dài 2 (k=2) xuất hiện nhiều nhất
    char path[50];
    findMax(root, 2, 0, path);
    printf("Cac prefix do dai 2 xuat hien nhieu nhat:\n");
    printMax(root, 2, 0, path);

    // Yêu cầu 3: Xóa từ "world"
    root = deleteWord(root, "world", 0);
    traverseTrie(root, doc ,0);
    // Yêu cầu 4: Giải phóng toàn bộ cây
    freeTrie(root);
    return 0;
}