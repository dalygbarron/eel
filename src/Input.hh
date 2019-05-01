#ifndef INPUT_H
#define INPUT_H

/**
 * Contains input access.
 */
namespace Input {
    const int BUTTON_UP = 0;
    const int BUTTON_LEFT = 1;
    const int BUTTON_RIGHT = 2;
    const int BUTTON_DOWN = 3;
    const int BUTTON_FIRE = 4;
    const int BUTTON_STRAFE = 5;
    const int BUTTON_BOMB = 6;
    const int BUTTON_PAUSE = 7;
    const int BUTTON_N = 8;

    /**
     * Processes the current lot of SDL events.
     * @return false when a quit event has occurred and the game should close.
     */
    int process();

    /**
     * tells you if a given button is pressed right now.
     * @param button is the button that we are checking.
     */
    int isDown(int button);

    /**
     * Tells you if a given button went down this cycle.
     * @param button is the button we are checking.
     */
    int isRecentlyDown(int button);
}

#endif
