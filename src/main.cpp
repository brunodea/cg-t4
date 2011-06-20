#include "glfw.h"
#include <cstdlib>

#include "macros.h"

/*
 * Callback functions
 */
void GLFWCALL keyEventCallback(int key, int state)
{
}

void GLFWCALL mousePosCallback(int x, int y)
{
}

void GLFWCALL mouseButtonCallback(int button, int action)
{
}

void GLFWCALL handleResize(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.f,(float)width/(float)height,0.1,5000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setCallBacks()
{
    glfwSetKeyCallback(keyEventCallback);
    glfwSetMousePosCallback(mousePosCallback);
    glfwSetMouseButtonCallback(mouseButtonCallback);

    glfwSetWindowSizeCallback(handleResize);
}

void initOpenGL()
{
    handleResize(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.f, 0.f, 0.f, 1.f);
}

int main()
{
    if(!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    if(!glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 8, 8, 8, 8, 8, 8, GLFW_WINDOW))
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    initOpenGL();
    setCallBacks();

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
