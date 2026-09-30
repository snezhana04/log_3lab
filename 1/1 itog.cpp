#include<stdio.h>
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


void insert_by_priority(struct node* p);
void pause_and_clear(void);

void pause_and_clear(void)
{
    printf("\nНажмите Enter для возврата в меню");
    getchar();
    system("cls");
}

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

void insert_by_priority(struct node* p)
{
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

void push(void)
{
    struct node* p = get_struct();
    if (p == NULL) return;
    insert_by_priority(p);
    printf("Элемент \"%s\" (приоритет %d) добавлен.\n", (*p).inf, (*p).priority);
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

void find(char* name)
{
    struct node* struc = head;
    struct node* prev = NULL;
    int count = 0;
    int pick = 1;
    int idx = 0;

    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }

    printf("\nНайдены элементы с именем \"%s\":\n", name);
    while (struc) {
        if (strcmp(name, (*struc).inf) == 0) {
            count++;
            printf("  %d) [Приоритет: %d]\n", count, (*struc).priority);
        }
        struc = (*struc).next;
    }

    if (count == 0) {
        printf("Элемент не найден\n");
        return;
    }

    if (count > 1) {
        printf("Какой изменить? Введите номер (1-%d): ", count);
        if (scanf_s("%d", &pick) != 1) {
            while (getchar() != '\n');
            printf("Неверный ввод\n");
            return;
        }
        getchar();
        if (pick < 1 || pick > count) {
            printf("Неверный номер\n");
            return;
        }
    }

    struc = head;
    prev = NULL;
    while (struc) {
        if (strcmp(name, (*struc).inf) == 0) {
            idx++;
            if (idx == pick) break;
        }
        prev = struc;
        struc = (*struc).next;
    }

    printf("Выбран: %s (текущий приоритет: %d)\n", (*struc).inf, (*struc).priority);

    int new_pr;
    printf("Введите новый приоритет (1 — самый важный): ");
    scanf_s("%d", &new_pr);
    getchar();

    if (new_pr == (*struc).priority) {
        printf("Приоритет не изменился.\n");
        return;
    }


    if (prev == NULL) {
        head = (*struc).next;
        if (head == NULL) last = NULL;
    }
    else {
        (*prev).next = (*struc).next;
        if ((*struc).next == NULL) last = prev;
    }
    dlinna--;


    (*struc).priority = new_pr;
    (*struc).next = NULL;
    insert_by_priority(struc);

    printf("Приоритет элемента \"%s\" изменён на %d.\n", (*struc).inf, new_pr);
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

    system("cls");

    while (1) {
        printf("\n______________________________\n"
            "Приоритетная очередь\n"
            "1. Добавить (push)\n"
            "2. Извлечь приоритетный (pop)\n"
            "3. Показать очередь\n"
            "4. Найти и изменить приоритет\n"
            "5. Удалить\n"
            "0. Выход\nВыбор: ");
        if (scanf_s("%d", &choice) != 1) break;
        getchar();
        if (choice == 0) break;

        system("cls");

        switch (choice) {
        case 1:
            push();
            pause_and_clear();
            break;
        case 2:
            pop();
            pause_and_clear();
            break;
        case 3:
            print_list();
            pause_and_clear();
            break;
        case 4:
            printf("Введите имя для поиска: ");
            scanf_s("%s", text, (unsigned)sizeof(text));
            getchar();
            system("cls");
            find(text);
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
    printf("Выход. До свидания!\n");
    return 0;
}