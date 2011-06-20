#include "glfw.h"
#include <cstdlib>

#include "macros.h"
#include "Controller/Controller.h"

/*
 * Callback functions
 */
void GLFWCALL keyEventCallback(int key, int state)
{
    CONTROLLER->onKeyPressed(key, state);
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
    glfwSetWindowSizeCallback(handleResize);
}

void initOpenGL()
{
    handleResize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.f, 0.f, 0.f, 1.f);
}

void clear()
{
    delete CONTROLLER;
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

    CONTROLLER->run();

    clear();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

