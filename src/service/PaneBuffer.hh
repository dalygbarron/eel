#ifndef PANE_BUFFER_H
#define PANE_BUFFER_H

/**
 * Takes care of panes and renders them all with a big vertex buffer.
 */
class PaneBuffer {
    public:
        int const n;

        /**
         * Create the buffer and set the maximum number of quads in it.
         * @param n is the number of quads.
         */
        PaneBuffer(int n);

        /**
         * Deletes stuff.
         */
        ~PaneBuffer();

        /**
         * Puts the count of currently allocated vertices back to 0.
         */
        void clear();

        /**
         * Gives you a currently unallocated pane.
         * @return a pointer to the pane unless none could be gotten in which
         *         case you get null.
         */
        Pane *claim();

        /**
         * Sorts the panes in the buffer so that they are rendered in order of
         * being down the page (according to their origin point).
         * Obviously that is a bit of a specific way to sort but that is the
         * way I need, I can make it more general if and when needed (never).
         */
        void sort();

    private:
        int top;
        sf::Vertex *vertices;
        Pane *panes;

};

#endif
