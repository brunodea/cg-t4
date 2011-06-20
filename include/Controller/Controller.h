#ifndef _BRUNODEA_CONTROLLER_H_
#define _BRUNODEA_CONTROLLER_H_

#include "math/Curves/BezierSurface.h"
#include "Controller/Camera.hpp"

class Controller
{
public:
    static Controller *instance();

    void run();

    void onKeyPressed(int key, int state);

private:
    Controller();

    void onUpdate();
    void onRender();
    
    void cameraOnKeyPress();

private:
    static Controller *m_sInstance;
    bool m_bRunning;

    math::BezierSurface m_BezierSurface;
    Camera m_FreeCamera;
    Camera *m_pCurrentCamera;

}; //end of class Controller

#endif
