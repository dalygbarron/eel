#ifndef BUCKET_H
#define BUCKET_H

/**
 * A linked list of key value pairs.
 */
struct Bucket {
    /**
     * The key by which the value is known. should not be const as it should
     * be a copy
     */
    char *key;

    /** The value stored */
    void *value;

    /** the next item in the list */
    struct Bucket *next;
};

#endif
