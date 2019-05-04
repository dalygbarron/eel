#ifndef POLYGON_SHADER_H
#define POLYGON_SHADER_H

#include "Shader.hh"

class PolygonShader: public Shader {
    int time = 0;

public:
    int load();

    /**
     * Updates the time.
     * @param time is the current time in seconds.
     */
    void update(float time);
};

#endif
