#ifndef RENDERER_H
#define RENDERER_H

#include "Stage.hh"

/**
 * Renders a stage onto the screen.
 * Does not set up the screen so you must do that first.
 */
class Renderer {
public:
    /**
     * Creates the renderer and sets up any stuff that it needs to set up.
     */
    Renderer();

    /**
     * Renders a screen.
     * @param stage is the description of what should appear on the screen.
     */
    void render(Stage const *stage);
};

#endif
