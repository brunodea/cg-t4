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
            /*glPushMatrix();
                glTranslatef(m_BasePoint[0],m_BasePoint[1],m_BasePoint[2]);
                m_BaseCylinder.draw();
                math::Vector3 p = m_MobilePoint/2.f;
                glTranslatef(p[0],p[1],p[2]);
                m_MovCylinder.draw();
            glPopMatrix();*/
        }
        math::Vector3 basePoint() { return m_BasePoint; }
        void setBasePoint(const math::Vector3 &p) { m_BasePoint = p; adjustCylinders(); }

        math::Vector3 mobilePoint() { return m_MobilePoint; }
        void setMobilePoint(const math::Vector3 &p){ m_MobilePoint = p; adjustCylinders(); }
    private:
        void adjustCylinders()
        {
            float d = math::distance(m_BasePoint, m_MobilePoint);
            m_BaseCylinder.setHeight(d/2.f);
            m_MovCylinder.setHeight(d/2.f);
        }

    private:
        Cylinder m_BaseCylinder;
        Cylinder m_MovCylinder; //cilindro movimentavel.
        
        math::Vector3 m_BasePoint;
        math::Vector3 m_MobilePoint;
    }; //end of class Pistao.
} //end of namespace model.

#endif
