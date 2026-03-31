#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    unsigned freq;
    struct Node *left, *right;
} Node;

typedef struct List {
    Node* treeNode;      // Con trỏ trỏ đến Node cây
    struct List* next;   // Con trỏ trỏ đến phần tử List tiếp theo
} List;

Node* makeNode(char data, unsigned freq) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->left = p->right = NULL;
    p->data = data;
    p->freq = freq;
    return p;
}

// Hàm chèn vào danh sách (Priority Queue)
List* insert(List* head, Node* node) {
    List* newElement = (List*)malloc(sizeof(List));
    newElement->treeNode = node;
    newElement->next = NULL;

    // Nếu list rỗng hoặc node mới nhỏ hơn đầu list
    if (head == NULL || head->treeNode->freq > node->freq) {
        newElement->next = head;
        return newElement; // Trả về đầu mới
    }

    // Tìm chỗ chèn vào giữa/cuối
    List* cur = head;
    while (cur->next != NULL && cur->next->treeNode->freq < node->freq) {
        cur = cur->next;
    }
    
    newElement->next = cur->next;
    cur->next = newElement;
    return head;
}

// Hàm lấy phần tử đầu ra (Pop)
Node* pop(List** head) {
    if (*head == NULL) return NULL;
    List* temp = *head;
    *head = (*head)->next;
    Node* n = temp->treeNode;
    free(temp);
    return n;
}

// 3. Thuật toán Huffman (Gọn hơn rất nhiều)
Node* buildHuffman(char data[], int freq[], int size) {
    List* head = NULL;
    
    // B1: Tạo rừng cây
    for (int i = 0; i < size; ++i)
        head = insert(head, makeNode(data[i], freq[i]));

    // B2: Lặp gộp cây
    while (head && head->next) { // Còn ít nhất 2 phần tử
        Node* left = pop(&head);
        Node* right = pop(&head);

        // Tạo nút cha '$' với tổng tần suất
        Node* parent = makeNode('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        head = insert(head, parent);
    }
    return pop(&head); // Trả về gốc
}

// 4. In mã hóa
void printCode(Node* root, char code[], int top) {
    if (!root) return;
    
    if (!root->left && !root->right) { // Là nút lá
        code[top] = '\0';
        printf("%c: %s\n", root->data, code);
        return;
    }
    
    if (root->left) {
        code[top] = '0';
        printCode(root->left, code, top + 1);
    }
    if (root->right) {
        code[top] = '1';
        printCode(root->right, code, top + 1);
    }
}

// Hàm main
int main() {
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(arr) / sizeof(arr[0]);

    Node* root = buildHuffman(arr, freq, size);

    char code[100];
    printf("Huffman Codes:\n");
    printCode(root, code, 0);

    return 0;
}