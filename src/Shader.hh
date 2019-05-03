#ifndef SHADER_HH
#define SHADER_HH

#include <OpenGL/gl.h>


/**
 * A glsl shader program that renders stuff hell yeah.
 */
class Shader {
protected:
    int programId = 0;

    /**
     * Outputs logging not to do with the shader itself.
     * @param program is the program to log about.
     */
    void printProgramLog(int program);

    /**
     * Outputs logging from a shader.
     * @param shader is the shader to log about.
     */
    void printShaderLog(int shader);

public:
    /**
     * Deletes the shader object and frees it's junk.
     */
    ~Shader();

    /**
     * Loads a shader program in to the shader.
     * @return true iff successful.
     */
    virtual int load() = 0;

    /**
     * Loads a shader from a file.
     * @param path       is the file to get it from.
     * @param shaderType is which type of shader like fragment or vertex.
     */
    int loadFromFile(char const *path, GLenum shaderType);

    /**
     * Frees the current shader program in the shader object.
     */
    virtual void free();

    /**
     * Binds this shader to opengl.
     * @return true iff successful.
     */
    int bind();

    /**
     * Unbinds this shader from opengl.
     */
    void unbind();

    /**
     * Gives you the gpu shader id.
     * @return the id if one exists otherwise you get 0.
     */
    int getId();
};

#endif
