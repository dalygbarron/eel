#ifndef LIST_H
#define LIST_H

#include "model/Node.h"

/**
 * Pushes a new node onto the front of a linked list.
 * @param item  is the content to add.
 * @param front is a pointer to the current front of the list.
 * @return a pointer to the new front of the list.
 */
struct Node *list_pushFront(void *item, struct Node *front);

/**
 * Deletes all the nodes in a list.
 * @param front is the first node in the list.
 */
void list_delete(struct Node *front);

#endif
