#include "glenv.h"
#include "global.h"
#include "shader.h"
#include "shader_program.h"
#include <string>

using namespace std;

void onResize(GLFWwindow* window, int width, int height);
void processInput();

float vertices[] = {
     0.0f,   0.5f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  -0.5f,  0.0f,  0.0f,  0.0f,  1.0f
};

unsigned int indices[] = {
    0, 1, 2
};

int main()
{
    glfwInit();
    glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Global::GetInstance().MainWindow = glfwCreateWindow(1280, 720, "GL Test", NULL, NULL);
    if (Global::GetInstance().MainWindow == nullptr)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(Global::GetInstance().MainWindow);
    glfwSetFramebufferSizeCallback(Global::GetInstance().MainWindow, onResize);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        glfwTerminate();
        return -2;
    }

    if (!glIsEnabled)
    {
        glfwTerminate();
        return -3;
    }

    int maxVertAttributes = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertAttributes);
    if(maxVertAttributes < 16)
    {
        glfwTerminate();
        return -4;
    }

    Shader v(VERTEX, "shader/default.vert");
    Shader f(FRAGMENT, "shader/purecolor.frag");
    ShaderProgram sp({ v, f });
    sp.Enable();

    unsigned int VAO_key;
    glGenVertexArrays(1, &VAO_key);

    unsigned int VBO_key;
    glGenBuffers(1, &VBO_key);

    unsigned int EBO_key;
    glGenBuffers(1, &EBO_key);

    glBindVertexArray(VAO_key);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_key);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_key);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(Global::GetInstance().MainWindow))
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO_key);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(Global::GetInstance().MainWindow);

        glfwPollEvents();
        processInput();
    }

    glfwTerminate();
    return 0;
}

void onResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput()
{
    if (Global::GetInstance().MainWindow == nullptr)
        return;

    if (glfwGetKey(Global::GetInstance().MainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(Global::GetInstance().MainWindow, true);
}