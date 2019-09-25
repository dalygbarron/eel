#ifndef ITEM_H
#define ITEM_H

/**
 * An item that can be picked up and kept in the player's inventory, and
 * potentially also used and stuff. This class is meant to represent a single
 * "kind" of item, with specific instances of an item simply being pointers to
 * the original record here.
 */
class Item {
    public:
        char const * const name;
        char const * const description;
        char const * const icon;
        char const * const action;
        int const stacking;

        /**
         * Creates the item by giving it the stuff that it needs.
         */
        Item(char const *name, char const *description, char const *icon);
};

#endif
