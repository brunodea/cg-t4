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

void initOpenGLLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat mat_env[] = {1.f,1.f,1.f,1.f}; //material ambiente.
    GLfloat mat_dif[] = {.7f,.4f,.0f,1.f}; //material difusa.
    GLfloat mat_spe[] = {1.f,1.f,1.f,1.f}; //material especular.
    GLfloat mat_shi = 30.f; //material brilho.

    GLfloat light_pos[] = {10.f,10.f,10.f,1.f}; //posicao da luz.
    GLfloat light_env[] = {.1f,.1f,.1f,1.f}; //luz ambiente.
    GLfloat light_dif[] = {1.f,1.f,1.f,1.f}; //luz difusa.
    GLfloat light_spe[] = {1.f,1.f,1.f,1.f}; //luz especular.

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_env);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spe);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shi);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_env);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_spe);
}

void initOpenGL()
{
    handleResize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_DEPTH_TEST);
    initOpenGLLighting();
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

