#include "runtime.h"

// Vertices coordinates
GLfloat vertices[] = 
{
    //              COORDINATES                       //        COLORS       //
    -0.5f,  -0.5f * float(sqrt(3)) / 3,         0.0f,   0.8f, 0.3f,  0.02f,  // Lower left corner
    0.5f,   -0.5f * float(sqrt(3)) / 3,         0.0f,   0.8f, 0.3f,  0.02f,  // Lower right corner
    0.0f,    0.5f * float(sqrt(3)) * 2 / 3,     0.0f,   1.0f, 0.6f,  0.32f, // Upper corner
    -0.25f,  0.5f * float(sqrt(3)) / 6,         0.0f,   0.9f, 0.45f, 0.17f,  // Inner left
    0.25f,   0.5f * float(sqrt(3)) / 6,         0.0f,   0.9f, 0.45f, 0.17f,  // Inner right
    0.0f,   -0.5f * float(sqrt(3)) / 3,         0.0f,   0.8f, 0.3f,  0.02f   // Inner down 
};

GLuint indices[] =
{
    0, 3, 5,    // Lower left triangle
    3, 2, 4,    // Lower right triangle
    5, 4, 1     // Upper triangle
};


int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        glfwTerminate();
        return -1;
    }

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using the OpenGL version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the Core profile
    // So that we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Create a GLFW window object of 800x800 pixels, naming it "Scratch"
    GLFWwindow *window = glfwCreateWindow(800, 800, "Scratch", nullptr, nullptr);
    // Error check if the window fails to create
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures OpenGL
    if (!gladLoadGL())
    {
        std::cerr << "Failed to load GLAD\n";
        glfwTerminate();
        return -1;
    }
    // Specify the viewpoint of OpenGL in the window
    // In this case the viewport goes from x=0, y=0 to x=800, y=800
    glViewport(0, 0, 800, 800);


    // Generates the shader program using the triangle.vert and triangle.frag files
    Shader * shaderProgram = new Shader("../../shaders/triangle.vert", "../../shaders/triangle.frag");

    // Generates the vertex array object and binds it
    VAO * VAO1 = new VAO;
    VAO1->bind();

    // Generates the vertex buffer object and link it to vertices
    VBO * VBO1 = new VBO(vertices, sizeof(vertices));
    // Generates the element buffer object and link it to indices
    EBO * EBO1 = new EBO(indices, sizeof(indices));

    // Links VBO attributes such as coordinates and colors  VAO
    VAO1->linkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), nullptr);
    VAO1->linkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    // Unbinds all to prevent accidentally modifying them
    VAO1->unbind();
    VBO1->unbind();
    EBO1->unbind();

    // Gets ID of uniform called "scale"
    GLuint uniID = glGetUniformLocation(shaderProgram->getID(), "scale");

    // Main while loop
    while (!(glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Tell OpenGL which Shader Program we want to use
        shaderProgram->activate();
        // Assigns a value to the uniform; NOTE: Must always be done after activating the shader program
        glUniform1f(uniID, 0.5f);
        // Bind the VAO so OpenGL knows to use it
        VAO1->bind();

        // Draw the triangle using GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // Swap the buffers
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete all the objects we created
    delete VAO1, VBO1, EBO1, shaderProgram;

    // Delete the window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}