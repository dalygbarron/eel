#ifndef NODE_H
#define NODE_H

/**
 * Represents a node in a linked list.
 */
struct Node {
    // The data item that the node points to.
    void *item;

    // The next node in the list, with 0 meaning this is the last item.
    struct Node *next;
};

#endif
