#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct node {
    char inf[256];        
    int  priority;        
    struct node* next;   
};

struct node* head = NULL, * last = NULL, * f = NULL;
int dlinna = 0;

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];
    int pr;

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    if (scanf_s("%s", s, (unsigned)sizeof(s)) != 1 || *s == 0) {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }
    strcpy_s((*p).inf, sizeof((*p).inf), s);

    printf("Введите приоритет (1 — самый важный): ");
    scanf_s("%d", &pr);
    (*p).priority = pr;

    (*p).next = NULL;
    return p;
}

void push(void)
{
    struct node* p = get_struct();
    if (p == NULL) return;


    if (head == NULL || (*p).priority < (*head).priority) {
        (*p).next = head;
        head = p;
        if (last == NULL) last = p;
    }
        else {
            struct node* curr = head;
            while ((*curr).next != NULL && (*(*curr).next).priority <= (*p).priority)
                curr = (*curr).next;
            (*p).next = (*curr).next;
            (*curr).next = p;
            if ((*p).next == NULL) last = p;
        }
    dlinna++;
}

void pop(void)
{
    if (head == NULL) {
        printf("Очередь пуста\n");
        return;
    }
    struct node* temp = head;
    printf("Извлечён: %s (приоритет: %d)\n", (*temp).inf, (*temp).priority);
    head = (*head).next;
    if (head == NULL) last = NULL;
    free(temp);
    dlinna--;
}

void print_list(void)
{
    struct node* curr = head;
    if (curr == NULL) {
        printf("Очередь пуста.\n");
        return;
    }
    printf("\nПриоритетная очередь (1 = самый важный) ---\n");
    while (curr != NULL) {
        printf("[Приоритет: %d] %s\n", (*curr).priority, (*curr).inf);
        curr = (*curr).next;
    }
    printf("Всего элементов: %d\n", dlinna);
}


struct node* find(char* name)
{
    struct node* struc = head;
    if (head == NULL) { printf("Список пуст\n"); return NULL; }
    while (struc) {
        if (strcmp(name, (*struc).inf) == 0) return struc;
        struc = (*struc).next;
    }
    printf("Элемент не найден\n");
    return NULL;
}


void del(char* name)
{
    struct node* struc = head, * prev = NULL;
    if (head == NULL) { printf("Список пуст\n"); return; }
    while (struc) {
        if (strcmp(name, (*struc).inf) == 0) {
            if (prev == NULL) {
                head = (*struc).next;
                if (head == NULL) last = NULL;
            }
            else {
                (*prev).next = (*struc).next;
                if ((*struc).next == NULL) last = prev;
            }
            free(struc);
            dlinna--;
            printf("Элемент \"%s\" удалён\n", name);
            return;
        }
        prev = struc;
        struc = (*struc).next;
    }
    printf("Элемент не найден\n");
}

int main(void)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice = 0;
    char text[256];

    while (1) {
        printf("\n______________________________\n"
            "Приоритетная очередь\n"
            "1. Добавить (push)\n"
            "2. Извлечь приоритетный (pop)\n"
            "3. Показать очередь\n"
            "4. Найти\n"
            "5. Удалить\n"
            "0. Выход\nВыбор: ");
        if (scanf_s("%d", &choice) != 1) break;
        getchar();
        if (choice == 0) 
            break;
        system("cls");
        switch (choice) {
        case 1:
            push(); break;
        case 2: 
            pop(); break;
        case 3: 
            print_list(); break;
        case 4:
            printf("Введите имя для поиска: ");
            scanf_s("%s", text, (unsigned)sizeof(text));
            f = find(text);
            if (f) printf("Найден: %s (приоритет %d)\n", (*f).inf, (*f).priority);
            break;
        case 5:
            printf("Введите имя для удаления: ");
            scanf_s("%s", text, (unsigned)sizeof(text));
            del(text);
            break;
        }
    }
    return 0;
}