#ifndef _BRUNODEA_PISTAO_HPP_
#define _BRUNODEA_PISTAO_HPP_

#include <vector>
#include "math/matrix_functions.hpp"
#include "model/Box.hpp"
#include "glfw.h"

namespace model
{
    class Pistao
    {
    public:
        Pistao(const math::Vector3 &basePoint, const math::Vector3 &mobilePoint)
            : m_FixedPartBox(1.f,2.f), m_MobilePartBox(.5f,1.7f), 
              m_BasePoint(basePoint), m_MobilePoint(mobilePoint), m_fMaxLength(3.f)
        {
        }

        void drawInWireframe()
        {
            glBegin(GL_LINES);
                glVertex3f(m_BasePoint[0],m_BasePoint[1],m_BasePoint[2]);
                glVertex3f(m_MobilePoint[0],m_MobilePoint[1],m_MobilePoint[2]);
            glEnd();
        }
        
        void setMaxLength(float mlen) { m_fMaxLength = mlen; }
        float getMaxLength() { return m_fMaxLength; }

        math::Vector3 basePoint() { return m_BasePoint; }
        void setBasePoint(const math::Vector3 &p) { m_BasePoint = p; }

        math::Vector3 mobilePoint() { return m_MobilePoint; }
        void setMobilePoint(const math::Vector3 &p){ m_MobilePoint = p; }

        
    private:
        
        bool canMoveUp()
        {
            return (math::distance(m_BasePoint,m_MobilePoint) <= m_fMaxLength);
        }
        bool canMoveDown()
        {
            return !(math::distance(m_BasePoint,m_MobilePoint) <= 0.05f);
        }
    private:
        Box m_FixedPartBox;
        Box m_MobilePartBox;
        
        math::Vector3 m_BasePoint;
        math::Vector3 m_MobilePoint;

        float m_fMaxLength;

    }; //end of class Pistao.
} //end of namespace model.

#endif
