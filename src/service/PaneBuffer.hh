#ifndef PANE_BUFFER_H
#define PANE_BUFFER_H

#include "model/Pane.hh"
#include <SFML/Graphics.hpp>

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
         * Sorts the panes by whatever is the currently configured method. If
         * you want it to sort less often then call this method less often.
         */
        void update();

        /**
         * Render all of the panes with the given texture.
         * @param target  is the render target to render to.
         * @param texture is the texture to render with.
         */
        void render(
            sf::RenderTarget &target,
            sf::Texture const &texture
        ) const;

    private:
        int top;
        sf::Vertex *vertices;
        sf::VertexBuffer vertexBuffer;
        Pane *panes;

        /**
         * Sorts the panes in the buffer so that they are rendered in order of
         * being down the page (according to their origin point).
         * Obviously that is a bit of a specific way to sort but that is the
         * way I need, I can make it more general if and when needed (never).
         * @return the start and end of the dirty part of the data, with
         *         x being the start and y being the end, unless they are equal
         *         in which case there is nothing dirty and no need for update.
         */
        sf::Vector2u sort();
};

#endif
