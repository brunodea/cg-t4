#include "Controller/Controller.h"
#include <iostream>

#include "glfw.h"
#include "macros.h"

Controller *Controller::m_sInstance = NULL;

Controller::Controller()
    : m_bRunning(true),  m_BezierSurface(13), m_FreeCamera(math::vector3f(0,0,-1),math::vector3f(0,0,0),math::vector3f(0,1,0))
{
    m_pCurrentCamera = &m_FreeCamera;
}

Controller *Controller::instance()
{
    if(m_sInstance == NULL)
        m_sInstance = new Controller();
    return m_sInstance;
}

void Controller::run()
{
    double last_render = 0;
    double last_update = 0;

    double frame_interval = 1.f/60.f;
    double update_interval = 1.f/90.f;

    double cur_time = 0;
    while(m_bRunning)
    {
        cur_time = glfwGetTime();
        if(cur_time - last_render > frame_interval) 
        {
            last_render = glfwGetTime();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            onRender();
            glfwSwapBuffers();
        }
        if(cur_time - last_update > update_interval)
        {
            onUpdate();
            last_update = glfwGetTime();
        }
        glfwSleep(update_interval - (cur_time + glfwGetTime()));
    }
}

void Controller::onUpdate()
{
    if(m_bRunning)
        m_bRunning = !glfwGetWindowParam(GLFW_OPENED) == 0;
    cameraOnKeyPress();

    if(m_pCurrentCamera == &m_FreeCamera)
        m_pCurrentCamera->setTarget(m_pCurrentCamera->direction()+m_pCurrentCamera->eye());
}

void Controller::onRender()
{
    math::Vector3 eye = m_pCurrentCamera->eye();
    math::Vector3 target = m_pCurrentCamera->target();
    math::Vector3 up = m_pCurrentCamera->up();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eye[0],eye[1],eye[2], target[0],target[1],target[2], up[0],up[1],up[2]);

    glPushMatrix();
        glColor4f(1.f,1.f,1.f,1.f);
        //glScalef(30.f,30.f,30.f);
        m_BezierSurface.drawWireframe();
    glPopMatrix();
}

void Controller::onKeyPressed(int key, int state)
{
    if(key == GLFW_KEY_ESC)
        m_bRunning = false;
}

void Controller::cameraOnKeyPress()
{
    if(glfwGetKey('S') == GLFW_PRESS)
        m_pCurrentCamera->moveBackwards();
    else if(glfwGetKey('W') == GLFW_PRESS)
        m_pCurrentCamera->moveForward();

    if(glfwGetKey('A') == GLFW_PRESS)
        m_pCurrentCamera->moveLeft();
    else if(glfwGetKey('D') == GLFW_PRESS)
        m_pCurrentCamera->moveRight();

    if(glfwGetKey('Z') == GLFW_PRESS)
        m_pCurrentCamera->moveUp();
    else if(glfwGetKey('X') == GLFW_PRESS)
        m_pCurrentCamera->moveDown();
}
