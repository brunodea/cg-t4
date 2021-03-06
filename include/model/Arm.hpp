/**
    classe que representa um braco do MunckMunk.
 **/
#ifndef _BRUNODEA_ARM_HPP_
#define _BRUNODEA_ARM_HPP_

#include "math/matrix_functions.hpp"
#include "math/math_aux.hpp"
#include "model/Object.hpp"
#include "model/Box.hpp"
#include "model/Pistao.hpp"
#include "glfw.h"

namespace model
{
    class Arm : public Object
    {
    public:
        Arm(const math::Vector3 &position, float length)
            : Object(position), m_MobilePoint(math::vector3f(0.f,length,0.f)), 
              m_Box(length/7.f,length/2.f), m_fLength(length)
        {
            m_fRoll = 0.f;
            m_fYaw = 0.f;
            m_fPitch = 0.f;
        }

        void draw(bool wireframe)
        {
            glPushMatrix();
                glRotatef(m_fRoll,  1.f,0.f,0.f);
                glRotatef(m_fYaw,   0.f,1.f,0.f);
                glRotatef(m_fPitch, 0.f,0.f,1.f);

                m_Box.draw(wireframe);
            glPopMatrix();
        }

        void rotate(float roll, float yaw, float pitch)
        {
            math::Vector4 aux;
            aux = (math::rotateZ(pitch)*math::rotateY(yaw)*math::rotateX(roll))*math::toVector4f(m_MobilePoint);
            m_MobilePoint = math::toVector3f(aux);

            m_fRoll += math::radToDegree(roll);
            m_fYaw += math::radToDegree(yaw);
            m_fPitch += math::radToDegree(pitch);
        }
        
        void setMobilePoint(const math::Vector3 &v) 
        { 
            m_MobilePoint = v;
            m_Box.setHeight(math::distance(math::vector3f(0.f,0.f,0.f),m_MobilePoint)/2.f);
        }
        math::Vector3 getMobilePoint() { return m_MobilePoint; }
        float length() { return m_fLength; }
    private:
        math::Vector3 m_MobilePoint;
        float m_fRoll;
        float m_fYaw;
        float m_fPitch;

        Box m_Box;

        float m_fLength;

    }; //end of class Arm.
} //end of namespace model.

#endif
