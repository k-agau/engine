#ifndef SHADER_H
#define SHADER_H

#include "glad.h" // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // the program ID
    unsigned int ID, rvertex, rfrag;

    //uses default paths
    Shader();
    // constructor reads with custom paths
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    ~Shader();
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

private:
    const char* ACORN_FRAGMENT_SHADER_PATH = "C:\\Users\\ksilv\\Github\\engine\\AcornEngine\\Shaders\\fragment_shader.glsl";
    const char* ACORN_VERTEX_SHADER_PATH = "C:\\Users\\ksilv\\Github\\engine\\AcornEngine\\Shaders\\vertex_shader.glsl";
    void checkCompileErrors(unsigned int shader, std::string type);
    void createGLShaders(const char* vertexPath, const char* fragmentPath);
};

#endif