#ifndef SIGNAL_H
#define SIGNAL_H

/**
 * A signal that can be sent.
 */
class Signal {
public:
    constexpr static int const TYPE_KEY = 0;
    constexpr static int const TYPE_MOUSE = 1;
    constexpr static int const TYPE_SCENE = 2;
    constexpr static int const TYPE_TIMED = 3;

    int type;
    union {
        class {
            int code;
        } key;
        class {
            int x;
            int y;
            int button;
        } mouse;
        class {
            int value;
        } scene;
        class {
            int time;
        } timed;
    } content;
};

#endif
