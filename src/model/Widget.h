#ifndef CONTROL_H
#define CONTROL_H

/**
 * Represents a gui control.
 */
struct Control {
    /** Points to the control's first child */
    struct Control *child;

    /** Forms a linked list of child controls */
    struct Control *sibling;

    /** The type of control that this is */
    int type;

    /** Type specific control content */
    union {
        // TODO: add some stuff.
    } content;
};

#endif
