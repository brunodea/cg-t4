#ifndef _BRUNODEA_ARM_HPP_
#define _BRUNODEA_ARM_HPP_

#include "math/matrix_functions.hpp"
#include "math/math_aux.hpp"
#include "model/Object.hpp"
#include "model/Cylinder.hpp"
#include "model/Pistao.hpp"
#include "glfw.h"

namespace model
{
    class Arm : public Object
    {
    public:
        Arm(const math::Vector3 &position, float length)
            : Object(position), m_MobilePoint(math::vector3f(0.f,length,0.f)), 
              m_Cylinder(0.7f,length), m_Pistao(position,position)
        {
            m_fRoll = 0.f;
            m_fYaw = 0.f;
            m_fPitch = 0.f;
        }

        void drawWireframe()
        {
            glPushMatrix();
                glPushMatrix();
                    glBegin(GL_LINES);
                        glVertex3f(0.f,0.f,0.f);
                        glVertex3f(m_MobilePoint[0],m_MobilePoint[1],m_MobilePoint[2]);
                    glEnd();
                glPopMatrix();

                glRotatef(m_fRoll,  1.f,0.f,0.f);
                glRotatef(m_fYaw,   0.f,1.f,0.f);
                glRotatef(m_fPitch, 0.f,0.f,1.f);

                m_Cylinder.draw();

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
        
        math::Vector3 getMobilePoint() { return m_MobilePoint+pos(); }

    private:
        math::Vector3 m_MobilePoint;
        float m_fRoll;
        float m_fYaw;
        float m_fPitch;

        Cylinder m_Cylinder;
        Pistao m_Pistao;

    }; //end of class Arm.
} //end of namespace model.

#endif
