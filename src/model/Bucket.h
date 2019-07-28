#ifndef BUCKET_H
#define BUCKET_H

/**
 * A linked list of key value pairs.
 */
struct Bucket {
    /** The key by which the value is known */
    char const *key;

    /** The value stored */
    void *value;

    /** the next item in the list */
    struct Bucket *next;
};

#endif
