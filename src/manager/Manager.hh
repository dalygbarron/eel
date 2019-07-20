#ifndef MANAGER_H
#define MANAGER_H

/**
 * Manages large groups of some model and runs their logic and stuff.
 * The models should be true and no private state.
 */
template <class T> class Manager {
public:

private:
    union Item {
        struct {
            int alive;
            T actual;
        } live;
        struct {
            int alive;
            T *next;
        } dead;
    };
    Item *items;

    /**
     * Creates the manager.
     * @param n is the number of items to dynamically allocate for it's use.
     */
    Manager(int n);
};

#endif
