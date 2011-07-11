/**
    Classe que eh a representacao de um pistao. Um pistao eh composto de dois cilindros.
    Um que representa a base do pistao (de tamanho fixo) e o outro que varia de tamanho,
    dando a ilusao de como ocorre no mundo real.
 **/
#ifndef _BRUNODEA_PISTAO_HPP_
#define _BRUNODEA_PISTAO_HPP_

#include <vector>
#include "math/matrix_functions.hpp"
#include "model/Cylinder.hpp"
#include "glfw.h"

namespace model
{
    class Pistao
    {
    public:
        Pistao(const math::Vector3 &basePoint, const math::Vector3 &mobilePoint)
            : m_BaseCylinder(.5f,2.5f), m_MovCylinder(.25f,3.f),
              m_BasePoint(basePoint), m_MobilePoint(mobilePoint)
        {
        }

        void draw(bool wireframe)
        {
            glPushMatrix();

                math::Vector3 v = m_MobilePoint-m_BasePoint;

                float ang = math::radToDegree(math::angle(v, math::vector3f(0.f,1.f,0.f)));
                if(v[0] > 0)
                    ang *= -1;

                math::Vector3 pos = m_BasePoint;
                glTranslatef(pos[0],pos[1],pos[2]);

                glRotatef(ang,0.f,0.f,1.f);

                m_BaseCylinder.draw(wireframe);

                glColor4f(1.f,0.f,0.f,1.f);
                m_MovCylinder.draw(wireframe);
            glPopMatrix();
        }
        math::Vector3 basePoint() { return m_BasePoint; }
        void setBasePoint(const math::Vector3 &p) { m_BasePoint = p; adjustCylinders(); }

        math::Vector3 mobilePoint() { return m_MobilePoint; }
        void setMobilePoint(const math::Vector3 &p){ m_MobilePoint = p; adjustCylinders(); }

        void setBaseCylinderHeight(float h) { m_BaseCylinder.setHeight(h); }
    private:
        void adjustCylinders()
        {
            float d = math::distance(m_BasePoint, m_MobilePoint);
            m_MovCylinder.setHeight(d);
        }

    private:
        Cylinder m_BaseCylinder;
        Cylinder m_MovCylinder; //cilindro movimentavel.
        
        math::Vector3 m_BasePoint;
        math::Vector3 m_MobilePoint;
    }; //end of class Pistao.
} //end of namespace model.

#endif
