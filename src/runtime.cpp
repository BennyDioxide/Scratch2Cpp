#include "runtime.h"


std::string getFileContents(fs::path filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in)
    {
        std::cerr << "Error: " << filename << " Not Found\n";
        glfwTerminate();
        throw(errno);
    }   
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
}

// ------------------------Shader----------------------------------

Shader::Shader(fs::path vertexFile, fs::path fragmentFile)
{
    // Read the vertex file and fragment file and store the strings
    std::string vertexCode = getFileContents(vertexFile);
    std::string fragmentCode = getFileContents(fragmentFile);

    // Convert the shader source strings into character array
    const char * vertexSource = vertexCode.c_str();
    const char * fragmentSource = fragmentCode.c_str();

    // Create Vertex Shader object and get its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader object
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);

    // Create Fragment Shader object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Vertex Shader object
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    // Compile the Fragment Shader into machine code
    glCompileShader(fragmentShader);

    // Create Shader Program and get its reference
    this->ID = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(this->ID);

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(this->ID);
}

GLuint Shader::getID()
{
    return this->ID;
}

void Shader::activate()
{
    glUseProgram(this->ID);
}

//---------------------------VAO----------------------------------

VAO::VAO()
{
    glGenVertexArrays(1, &this->ID);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &this->ID);
}

GLuint VAO::getID()
{
    return this->ID;
}

void VAO::linkAttrib(VBO * VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void * offset)
{
    VBO->bind();
    // Configures the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    // Enable the Vertex Attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(layout);
    VBO->unbind();
}

void VAO::bind()
{
    // Make the VAO the current by binding it
    glBindVertexArray(this->ID);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

//---------------------------VBO----------------------------------

VBO::VBO(GLfloat * vertices, GLsizeiptr size)
{
    glGenBuffers(1, &this->ID);
    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    this->bind();
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &this->ID);
}

GLuint VBO::getID()
{
    return this->ID;
}

void VBO::bind()
{
    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//---------------------------EBO----------------------------------

EBO::EBO(GLuint * indices, GLsizeiptr size)
{
    glGenBuffers(1, &this->ID);
    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    this->bind();
    // Introduce the vertices into the VBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

EBO::~EBO()
{
    glDeleteBuffers(1, &this->ID);
}

GLuint EBO::getID()
{
    return this->ID;
}

void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}

void EBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}