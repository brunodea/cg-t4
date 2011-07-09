#ifndef _BRUNODEA_ARM_HPP_
#define _BRUNODEA_ARM_HPP_

#include "math/matrix_functions.hpp"
#include "model/Object.hpp"
#include "glfw.h"

namespace model
{
    class Arm : public Object
    {
    public:
        Arm(const math::Vector3 &position, float length)
            : Object(position), m_MobilePoint(math::vector3f(0.f,length,0.f))
        {}

        void drawWireframe()
        {
            glPushMatrix();

                glTranslatef(pos()[0],pos()[1],pos()[2]);

                glBegin(GL_LINES);
                    glVertex3f(0.f,0.f,0.f);
                    glVertex3f(m_MobilePoint[0],m_MobilePoint[1],m_MobilePoint[2]);
                glEnd();

            glPopMatrix();
        }

        void rotate(float roll, float yaw, float pitch)
        {
            math::Vector4 aux;
            aux = (math::rotateZ(pitch)*math::rotateY(yaw)*math::rotateX(roll))*math::toVector4f(m_MobilePoint);
            m_MobilePoint = math::toVector3f(aux);
        }
        
        math::Vector3 getMobilePoint() { return m_MobilePoint+pos(); }

    private:
        math::Vector3 m_MobilePoint;

    }; //end of class Arm.
} //end of namespace model.

#endif
