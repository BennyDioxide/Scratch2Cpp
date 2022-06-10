#ifndef RUNTIME_H
#define RUNTIME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include "scratch.h"

namespace fs = std::filesystem;

// Reads a text file and outputs a string with everything in it
std::string getFileContents(fs::path filename);

class Shader
{
private:
    // Reference ID of the shader program
    GLuint ID;
    // Checks if the different shaders have compiled properly
    void compileErrors(unsigned int shader, const char * type);
public:
    // Build the shader program from 2 given file names
    Shader(fs::path vertexFile, fs::path fragmentFile);
    ~Shader();
    // Get the ID of the shader program
    GLuint getID();
    // Activates the shader program
    void activate();
};

class VBO
{
private:
    // Reference ID of the vertex buffer object
    GLuint ID;
public:
    // Generates a vertex buffer object and link it to vertices
    VBO(GLfloat * vertices, GLsizeiptr size);
    ~VBO();
    // Get the ID of the VBO
    GLuint getID();
    // Binds the VBO
    void bind();
    // Unbinds the VBO
    void unbind();
};

class EBO
{
private:
    // Reference ID of the element buffer object
    GLuint ID;
public:
    // Generates a element buffer object and link it to indices
    EBO(GLuint * indices, GLsizeiptr size);
    ~EBO();
    // Get the ID of the EBO
    GLuint getID();
    // Binds the EBO
    void bind();
    // Unbinds the EBO
    void unbind();
};

class VAO
{
private:
    // Reference ID of the vertex array object
    GLuint ID;
public:
    // Generates a vertex array object
    VAO();
    ~VAO();
    // Get the ID of the VAO
    GLuint getID();
    // Links a VBO attribute to the VAO using a certain layout
    void linkAttrib(VBO * VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void * offset);
    // Binds the VAO
    void bind();
    // Unbinds the VAO
    void unbind();
};

#endif