#ifndef ITEM_H
#define ITEM_H

/**
 * An item that can be picked up and kept in the player's inventory, and potentially also used and stuff. This class
 * is meant to represent a single "kind" of item, with specific instances of an item simply being pointers to the
 * original record here.
 */
class Item {
public:
    char const *name = "?";
    char const *description = "Unknown item.";
    char const *icon;
    char const *action;
    int stacking;
};

#endif
