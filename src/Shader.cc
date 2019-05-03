#include "Shader.hh"

#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <fstream>
#include <OpenGL/gl.h>

Shader::~Shader() {
    this->free();
}

int Shader::loadFromFile(char const *path, GLenum shaderType) {
    int shaderId = 0;
    std::string shaderString;
    std::ifstream sourceFile(path);
    if (sourceFile) {
        // read in source.
        shaderString.assign( ( std::istreambuf_iterator< char >( sourceFile ) ), std::istreambuf_iterator< char >() );
        const char* source = shaderString.c_str();
        // compile.
        shaderId = glCreateShader(shaderType);
        glShaderSource(shaderId, 1, (const char**)&source, 0);
        glCompileShader(shaderId);
        int compiled = 0;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE) {
            std::cerr << "unable to compile shader: " << shaderId << ", source: " << source << std::endl;
            this->printShaderLog(shaderId);
            glDeleteShader(shaderId);
            shaderId = 0;
        }
    } else {
        std::cerr << "Cannot open file " << path << std::endl;
    }
    return shaderId;
}

void Shader::free() {
    glDeleteProgram(this->programId);
}

int Shader::bind() {
    glUseProgram(this->programId);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Error binding shader: " << error << std::endl;
        return false;
    }
    return true;
}

void Shader::unbind() {
    glUseProgram(0);
}

int Shader::getId() {
    return this->programId;
}

void Shader::printProgramLog(int program) {
    if (glIsProgram(program)) {
        int infoLogLength = 0;
        int maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        char *infoLog = new char[maxLength];
        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            std::cout << infoLog << std::endl;
        }
        delete[] infoLog;
    } else {
        std::cerr << program << " is not a program." << std::endl;
    }
}

void Shader::printShaderLog(int shader) {
    if (glIsShader(shader)) {
        int infoLogLength = 0;
        int maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        char *infoLog = new char[maxLength];
        glGetProgramInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            std::cout << infoLog << std::endl;
        }
        delete[] infoLog;
    } else {
        std::cerr << shader << " is not a shader." << std::endl;
    }
}
