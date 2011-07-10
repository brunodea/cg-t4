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
            : m_BaseCylinder(.5f,1.f), m_MovCylinder(.25f,1.f),
              m_BasePoint(basePoint), m_MobilePoint(mobilePoint)
        {
        }

        void drawInWireframe()
        {
            glBegin(GL_LINES);
                glVertex3f(m_BasePoint[0],m_BasePoint[1],m_BasePoint[2]);
                glVertex3f(m_MobilePoint[0],m_MobilePoint[1],m_MobilePoint[2]);
            glEnd();
            glPushMatrix();

                math::Vector3 v = m_MobilePoint-m_BasePoint;

                float ang = math::radToDegree(math::angle(v, math::vector3f(0.f,1.f,0.f)));
                if(v[0] > 0)
                    ang *= -1;

                math::Vector3 pos = m_BasePoint;
                glTranslatef(pos[0],pos[1],pos[2]);

                glRotatef(ang,0.f,0.f,1.f);

                m_BaseCylinder.draw();

                glColor4f(1.f,0.f,0.f,1.f);
                m_MovCylinder.draw();
            glPopMatrix();
        }
        math::Vector3 basePoint() { return m_BasePoint; }
        void setBasePoint(const math::Vector3 &p) { m_BasePoint = p; adjustCylinders(); }

        math::Vector3 mobilePoint() { return m_MobilePoint; }
        void setMobilePoint(const math::Vector3 &p){ m_MobilePoint = p; adjustCylinders(); }
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
