#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct node {
    char inf[256];
    struct node* next;
};

struct node* head = NULL, * last = NULL, * f = NULL;
int dlinna = 0;

void pause_and_clear(void)
{
    printf("\nНажмите Enter для возврата в меню...");
    getchar();
    system("cls");
}

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];

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
    (*p).next = NULL;
    return p;
}

void push(void)
{
    struct node* p = get_struct();
    if (p == NULL) return;

    if (head == NULL) {
        head = last = p;
    }
    else {
        (*last).next = p;
        last = p;
    }
    dlinna++;
    printf("Элемент \"%s\" встал в очередь.\n", (*p).inf);
}

void pop(void)
{
    if (head == NULL) {
        printf("Очередь пуста\n");
        return;
    }
    struct node* temp = head;
    printf("Извлечён из очереди: %s\n", (*temp).inf);
    head = (*head).next;
    if (head == NULL) last = NULL;
    free(temp);
    dlinna--;
}

void print_list(void)
{
    struct node* curr = head;
    if (curr == NULL) { printf("Очередь пуста.\n"); return; }
    printf("\nОчередь FIFO\n");
    while (curr != NULL) {
        printf("[%s] -> ", (*curr).inf);
        curr = (*curr).next;
    }
    printf("NULL\n");
    printf("Всего элементов: %d\n", dlinna);
}

struct node* find(char* name)
{
    struct node* struc = head;
    if (head == NULL) { printf("Очередь пуста\n"); return NULL; }
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
    if (head == NULL) { printf("Очередь пуста\n"); return; }
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

    system("cls");

    while (1) {
        printf("\n______________________________\n"
            "Очередь FIFO\n"
            "1. Встать в очередь (push)\n"
            "2. Выйти из очереди (pop)\n"
            "3. Показать очередь\n"
            "4. Найти\n"
            "5. Удалить\n"
            "0. Выход\nВыбор: ");
        if (scanf_s("%d", &choice) != 1) break;
        getchar();
        if (choice == 0) break;

        system("cls");

        switch (choice) {
        case 1:
            push();   pause_and_clear(); break;
        case 2: 
            pop();    pause_and_clear(); break;
        case 3: 
            print_list(); pause_and_clear(); break;
        case 4:
            printf("Введите имя для поиска: ");
            scanf_s("%s", text, (unsigned)sizeof(text));
            getchar();
            system("cls");
            f = find(text);
            if (f) printf("Найден: %s\n", (*f).inf);
            pause_and_clear();
            break;
        case 5:
            printf("Введите имя для удаления: ");
            scanf_s("%s", text, (unsigned)sizeof(text));
            getchar();
            system("cls");
            del(text);
            pause_and_clear();
            break;
        default:
            printf("Неверный пункт меню\n");
            pause_and_clear();
        }
    }

    system("cls");

    return 0;
}