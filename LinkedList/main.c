#include <stdio.h>
#include <stdlib.h>

// Структура для представлення елемента списку
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Структура для представлення зв'язаного списку
typedef struct {
    Node* head; // Початковий елемент списку
    int size;   // Кількість елементів у списку
} LinkedList;

// Ініціалізація пустого списку
void initialize(LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

// Додавання елемента в кінець списку
void add(LinkedList* list, int item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

// Вставка елемента в середину списку за заданим індексом
void insert(LinkedList* list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Недійсний індекс для вставки.\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    list->size++;
}

// Кількість елементів у списку
int size(LinkedList* list) {
    return list->size;
}

// Видалення елемента за заданим індексом
void removeItem(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Недійсний індекс для видалення.\n");
        return;
    }

    if (index == 0) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
    } else {
        Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }

    list->size--;
}

// Заміна існуючого елемента за заданим індексом
void set(LinkedList* list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Недійсний індекс для заміни.\n");
        return;
    }

    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = item;
}

// Отримання значення заданого елемента за індексом
int get(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Недійсний індекс для отримання.\n");
        return -1; // Повертаємо -1 як помилку
    }

    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

// Очищення пам'яті, звільнення ресурсів
void cleanup(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}
void printList(LinkedList* list){
    for (int i = 0; i < size(list); i++) {
        printf("%d ", get(list, i));
    }
    printf("\n");
}
int main() {
    LinkedList list;
    initialize(&list);

    add(&list, 1);
    add(&list, 2);
    add(&list, 3);
    printf("Start list: ");
    printList(&list);

    insert(&list, 1, 4);
    printf("List after insert: ");
    printList(&list);

    set(&list, 2, 5);
    printf("List after set: ");
    printList(&list);

    removeItem(&list, 0);
    printf("List after remove: ");
    printList(&list);

    printf("List size: %d\n", size(&list));

    cleanup(&list);
    return 0;
}

