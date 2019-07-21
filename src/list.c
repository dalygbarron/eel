#include "list.h"

struct Node *list_pushFront(void *item, struct Node *front) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->item = item;
    newNode->next = front;
    return newNode;
}

void list_delete(struct Node *front) {
    while (front) {
        struct Node *next = front->next;
        free(front);
        front = next;
    }
}
