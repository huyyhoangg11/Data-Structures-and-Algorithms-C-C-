#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SinhVien {
    int stt;
    char mssv[20];
    char ten[20];
    char sdt[20];
    struct SinhVien *next;
} SinhVien;

typedef struct Lop {
    char tenLop[20];
    SinhVien *danhSach;
    struct Lop *next;
} Lop;

Lop *root = NULL;

int min(int a, int b) {
    return (a < b) ? a : b;
}

int soSanhChuoi(char s1[], char s2[]) {
    for (int i = 0; i < min(strlen(s1), strlen(s2)); i++) {
        if (s1[i] < s2[i]) return -1;
        if (s1[i] > s2[i]) return 1;
    }
    if (strlen(s1) < strlen(s2)) return -1;
    if (strlen(s1) > strlen(s2)) return 1;
    return 0;
}

SinhVien *taoSinhVien(int stt, char mssv[], char ten[], char sdt[]) {
    SinhVien *sv = (SinhVien *)malloc(sizeof(SinhVien));
    sv->stt = stt;
    strcpy(sv->mssv, mssv);
    strcpy(sv->ten, ten);
    strcpy(sv->sdt, sdt);
    sv->next = NULL;
    return sv;
}

SinhVien *themSinhVienSapXep(SinhVien *head, int stt, char mssv[], char ten[], char sdt[]) {
    if (head == NULL) return taoSinhVien(stt, mssv, ten, sdt);
    if (soSanhChuoi(ten, head->ten) < 0) {
        SinhVien *sv = taoSinhVien(stt, mssv, ten, sdt);
        sv->next = head;
        return sv;
    }
    head->next = themSinhVienSapXep(head->next, stt, mssv, ten, sdt);
    return head;
}

SinhVien *xoaSinhVien(SinhVien *head, char ten[]) {
    if (head == NULL) return NULL;
    if (strcmp(head->ten, ten) == 0) {
        SinhVien *tmp = head->next;
        free(head);
        return tmp;
    }
    head->next = xoaSinhVien(head->next, ten);
    return head;
}

void inDanhSach(SinhVien *head) {
    SinhVien *p = head;
    while (p != NULL) {
        printf("%d %s %s %s\n", p->stt, p->mssv, p->ten, p->sdt);
        p = p->next;
    }
}

void giaiPhongSinhVien(SinhVien *head) {
    while (head != NULL) {
        SinhVien *tmp = head;
        head = head->next;
        free(tmp);
    }
}

Lop *taoLop(char tenLop[]) {
    Lop *lop = (Lop *)malloc(sizeof(Lop));
    strcpy(lop->tenLop, tenLop);
    lop->danhSach = NULL;
    lop->next = NULL;
    return lop;
}

Lop *themLop(Lop *root, char tenLop[]) {
    if (root == NULL) return taoLop(tenLop);
    root->next = themLop(root->next, tenLop);
    return root;
}

Lop *timLop(Lop *root, char tenLop[]) {
    Lop *p = root;
    while (p != NULL) {
        if (strcmp(p->tenLop, tenLop) == 0) return p;
        p = p->next;
    }
    return NULL;
}

void giaiPhongTatCa(Lop *root) {
    while (root != NULL) {
        giaiPhongSinhVien(root->danhSach);
        Lop *tmp = root;
        root = root->next;
        free(tmp);
    }
}

int main() {
    int luaChon;

    while (1) {
        printf("\n===== MENU =====\n");
        printf("1. Nhap sinh vien\n");
        printf("2. In danh sach sinh vien theo lop\n");
        printf("3. Xoa sinh vien theo ten\n");
        printf("4. In toan bo cac lop\n");
        printf("Nhap lua chon (1-4, khac de thoat): ");

        if (scanf("%d%*c", &luaChon) != 1 || luaChon < 1 || luaChon > 4) break;

        if (luaChon == 1) {
            printf("Nhap: stt mssv ten sdt lop (nhap '#' de thoat)\n");
            while (1) {
                int stt;
                char mssv[20], ten[20], sdt[20], lop[20];
                int n = scanf("%d %19s %19s %19s %19s", &stt, mssv, ten, sdt, lop);
                if (n < 5) {
                    break;
                }

                Lop *l = timLop(root, lop);
                if (l == NULL) {
                    root = themLop(root, lop);
                    l = timLop(root, lop);
                }
                l->danhSach = themSinhVienSapXep(l->danhSach, stt, mssv, ten, sdt);
            }
        }

        else if (luaChon == 2) {
            char tenLop[20];
            printf("Nhap ten lop can in: ");
            scanf("%19s", tenLop);
            Lop *l = timLop(root, tenLop);
            if (l == NULL) printf("Khong tim thay lop!\n");
            else inDanhSach(l->danhSach);
        }

        else if (luaChon == 3) {
            char tenLop[20], ten[20];
            printf("Nhap lop can xoa sinh vien: ");
            scanf("%19s", tenLop);
            Lop *l = timLop(root, tenLop);
            if (l == NULL) {
                printf("Khong tim thay lop!\n");
            } else {
                printf("Nhap ten sinh vien muon xoa: ");
                scanf("%19s", ten);
                l->danhSach = xoaSinhVien(l->danhSach, ten);
            }
        }

        else if (luaChon == 4) {
            Lop *l = root;
            while (l != NULL) {
                printf("\nLop %s:\n", l->tenLop);
                inDanhSach(l->danhSach);
                l = l->next;
            }
        }
    }

    giaiPhongTatCa(root);
    printf("\nDa thoat chuong trinh.\n");
    return 0;
}
