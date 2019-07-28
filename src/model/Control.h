#ifndef CONTROL_H
#define CONTROL_H

struct Control {
    struct Control *child;
    struct Control *sibling;
};

#endif
