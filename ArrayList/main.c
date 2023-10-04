#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

typedef struct {
    int* data;
    int size;
    int capacity;
} ArrayList;

void initialize(ArrayList* list) {
    list->data = (int*)malloc(sizeof(int) * INITIAL_CAPACITY);
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
}

void add(ArrayList* list, int item) {
    if (list->size >= list->capacity) {

        list->capacity *= 2;
        list->data = (int*)realloc(list->data, sizeof(int) * list->capacity);
    }
    list->data[list->size] = item;
    list->size++;
}

void insert(ArrayList* list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Invalid index.\n");
        return;
    }
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->data = (int*)realloc(list->data, sizeof(int) * list->capacity);
    }
    for (int i = list->size; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = item;
    list->size++;
}

int size(ArrayList* list) {
    return list->size;
}

void removeItem(ArrayList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index.\n");
        return;
    }
    for (int i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
}

void set(ArrayList* list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index.\n");
        return;
    }
    list->data[index] = item;
}

int get(ArrayList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index.\n");
        return -1;
    }
    return list->data[index];
}

void cleanup(ArrayList* list) {
    free(list->data);
    list->size = 0;
    list->capacity = 0;
}
void printArray(ArrayList* list){
    for (int i = 0; i < size(list); i++) {
        printf("%d ", get(list, i));
    }
    printf("\n");
}

int main() {
    ArrayList list;
    initialize(&list);

    add(&list, 1);
    add(&list, 2);
    add(&list, 3);
    printf("Start array: ");
    printArray(&list);

    insert(&list, 1, 4);
    printf("Array after insert: ");
    printArray(&list);

    set(&list, 2, 5);
    printf("Array after set: ");
    printArray(&list);

    removeItem(&list, 0);
    printf("Array after remove: ");
    printArray(&list);

    printf("Array size: %d\n", size(&list));
    cleanup(&list);
    return 0;
}

