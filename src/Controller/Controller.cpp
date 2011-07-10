#include "Controller/Controller.h"
#include <iostream>

#include "glfw.h"
#include "macros.h"

Controller *Controller::m_sInstance = NULL;

Controller::Controller()
    : m_bRunning(true),  m_BezierSurface(13), m_MunckMunk(), 
      m_FreeCamera(math::vector3f(15,15,-15),math::vector3f(0,0,0),math::vector3f(0,1,0)),
      m_bWireframeScene(true)
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
    munckMunkOnKeyPress();

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

    rotateCamera();
    gluLookAt(eye[0],eye[1],eye[2], target[0],target[1],target[2], up[0],up[1],up[2]);

    /*glPushMatrix();
        glColor4f(1.f,1.f,1.f,1.f);
        glScalef(10.f,10.f,10.f);
        m_BezierSurface.draw(m_bWireframeScene);
    glPopMatrix();*/

    glPushMatrix();
        glLineWidth(2.f);
        //glScalef(5.f,5.f,5.f);
        glColor4f(1.f,0.f,0.f,1.f);
        m_MunckMunk.draw(m_bWireframeScene);
    glPopMatrix();
}

void Controller::onKeyPressed(int key, int state)
{
    if(state == GLFW_PRESS)
    {
        if(key == GLFW_KEY_ESC)
            m_bRunning = false;
        else if(key == GLFW_KEY_UP)
            m_MunckMunk.currentArm_next(true);
        else if(key == GLFW_KEY_DOWN)
            m_MunckMunk.currentArm_next(false);
        
        if(key == GLFW_KEY_PAGEUP)
            m_MunckMunk.addArm();
        else if(key == GLFW_KEY_PAGEDOWN)
            m_MunckMunk.removeArm();

        if(key == GLFW_KEY_F1)
            m_bWireframeScene = !m_bWireframeScene;
    }
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

    if(glfwGetKey(GLFW_KEY_RCTRL) == GLFW_PRESS)
        m_MunckMunk.growCurrentArm(true);
    else if(glfwGetKey(GLFW_KEY_LCTRL) == GLFW_PRESS)
        m_MunckMunk.growCurrentArm(false);
}

void Controller::rotateCamera()
{
    float roll = m_pCurrentCamera->getRollAngle();
    float yaw = m_pCurrentCamera->getYawAngle();
    float pitch = m_pCurrentCamera->getPitchAngle();

    float angle = (float)PI/50.f;
    if(glfwGetKey('U') == GLFW_PRESS)
        m_pCurrentCamera->rotate(angle,0.f,0.f);
    else if(glfwGetKey('O') == GLFW_PRESS)
        m_pCurrentCamera->rotate(-angle,0.f,0.f);

    if(glfwGetKey('L') == GLFW_PRESS)
        m_pCurrentCamera->rotate(0.f,angle,0.f);
    else if(glfwGetKey('J') == GLFW_PRESS)
        m_pCurrentCamera->rotate(0.f,-angle,0.f);

    if(glfwGetKey('I') == GLFW_PRESS)
        m_pCurrentCamera->rotate(0.f,0.f,angle);
    else if(glfwGetKey('K') == GLFW_PRESS)
        m_pCurrentCamera->rotate(0.f,0.f,-angle);

    glRotatef(roll ,1.f,0.f,0.f);
    glRotatef(yaw  ,0.f,1.f,0.f);
    glRotatef(pitch,0.f,0.f,1.f);
}

void Controller::munckMunkOnKeyPress()
{
    float angle = (float)PI/50.f;
    if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
        m_MunckMunk.rotateCurrArm(0.f,0.f,angle);
    else if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
        m_MunckMunk.rotateCurrArm(0.f,0.f,-angle);

    if(glfwGetKey('1') == GLFW_PRESS)
        m_MunckMunk.rotate(0.f,angle*2.f,0.f);
    else if(glfwGetKey('2') == GLFW_PRESS)
        m_MunckMunk.rotate(0.f,-angle*2.f,0.f);

    if(glfwGetKey('N') == GLFW_PRESS)
        m_MunckMunk.moveForward();
    else if(glfwGetKey('M') == GLFW_PRESS)
        m_MunckMunk.moveBackwards();
 }
