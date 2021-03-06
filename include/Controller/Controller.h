/*
    Classe que controla todo o esquema de loop (update+renderizacao). Alem do que vai ser mostrado.
 */
#ifndef _BRUNODEA_CONTROLLER_H_
#define _BRUNODEA_CONTROLLER_H_

#include "math/Curves/BezierSurface.h"
#include "Controller/Camera.hpp"
#include "model/MunckMunk.hpp"
#include "model/Truck.hpp"

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
    void rotateCamera();

    void munckMunkOnKeyPress();

private:
    static Controller *m_sInstance;
    bool m_bRunning;

    math::BezierSurface m_BezierSurface;
    model::Truck m_Truck;

    Camera m_FreeCamera;
    Camera m_SideTruckCamera; //camera ligada ao caminhao.
    Camera m_BehindTruckCamera;
    Camera *m_pCurrentCamera;

    bool m_bWireframeScene;

}; //end of class Controller

#endif
