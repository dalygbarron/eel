#ifndef SIGNAL_H
#define SIGNAL_H

/**
 * A signal that can be sent.
 */
class Signal {
public:
    constexpr static int const TYPE_KEY = 0;
    constexpr static int const TYPE_MOUSE = 1;
    constexpr static int const TYPE_TIMED = 2;
    constexpr static int const TYPE_SCENE = 3;

    int type;
    union {
        class {
        public:
            int code;
        } key;
        class {
        public:
            int x;
            int y;
            int button;
        } mouse;
        class {
        public:
            int time;
        } timed;
        class {
        public:
            int value;
        } scene;
    } content;

    /**
     * Default constructor.
     */
    Signal();

    /**
     * Create the signal with just a type.
     * @param type is the type to give it.
     */
    Signal(int type);
};

#endif
