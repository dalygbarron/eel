#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

/**
 * Takes care of the lifecycle of picture grams and storing them all on
 * the GPU and sorting them etc.
 */
class FrameManager {
    public:
        FrameManager(int n);

        ~FrameManager();

        void clear();

        /**
         * Creates a new frame and returns it to you.
         * @return a new frame which is guaranteed to be valid, but beware, it
         *         might return null if there is free space to make mroe
         *         frames.
         */
        Frame *makeFrame();
};

#endif
