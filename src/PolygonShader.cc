#include "PolygonShader.hh"

#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <OpenGL/gl.h>

int PolygonShader::load() {
    this->programId = glCreateProgram();
    // create the vertex shader.
    int vertexShader = loadFromFile("test/shader/plain.glvs", GL_VERTEX_SHADER);
    if (!vertexShader) {
        glDeleteProgram(this->programId);
        this->programId = 0;
        return false;
    }
    glAttachShader(this->programId, vertexShader);
    // create the fragment shader.
    int fragmentShader = loadFromFile("test/shader/plain.glfs", GL_FRAGMENT_SHADER);
    if (!fragmentShader) {
        glDeleteShader(vertexShader);
        glDeleteProgram(this->programId);
        this->programId = 0;
        return false;
    }
    glAttachShader(this->programId, fragmentShader);
    glLinkProgram(this->programId);
    // find errors.
    int compiled;
    glGetProgramiv(this->programId, GL_LINK_STATUS, &compiled);
    if (compiled != GL_TRUE) {
        std::cerr << "Error linking program: " << this->programId << std::endl;
        this->printProgramLog(this->programId);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(this->programId);
        this->programId = 0;
        return false;
    }
    // clean up. these are not needed once linked apparantly.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}
