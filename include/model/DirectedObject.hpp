#ifndef _BRUNODEA_DIRECTED_OBJECT_HPP_
#define _BRUNODEA_DIRECTED_OBJECT_HPP_

#include "math/matrix_functions.hpp"
#include "model/Object.hpp"


namespace model
{
    class DirectedObject : public Object
    {
    public:
        DirectedObject(const math::Vector3 &pos, float speed)
            : Object(pos), m_fSpeed(speed), m_Direction(math::vector3f(0.f,0.f,1.f)),
              m_fRoll(0.f), m_fYaw(0.f), m_fPitch(0.f)
        {}

        void moveForward() 
        { 
            math::Vector3 p = pos();
            p += (m_Direction*m_fSpeed);
            setPos(p); 
        }
        void moveBackwards() 
        { 
            math::Vector3 p = pos();
            p -= (m_Direction*m_fSpeed);
            setPos(p); 
        }

        void rotate(float roll, float yaw, float pitch)
        {
            math::Matrix4 m = math::rotateZ(pitch)*math::rotateY(yaw)*math::rotateX(roll);
            math::Vector4 aux = math::toVector4f(m_Direction);
            aux = m*aux;
            m_Direction = math::toVector3f(aux);

            m_fRoll += roll;
            m_fYaw += yaw;
            m_fPitch += pitch;
        }

        virtual void draw(bool wireframe) = 0;

        void setDirection(const math::Vector3 &dir) { m_Direction = dir; }
        math::Vector3 direction() { return m_Direction; }

    protected:
        float m_fRoll;
        float m_fYaw;
        float m_fPitch;

    private:
        math::Vector3 m_Direction;
        float m_fSpeed;
    };

} //end of namespace model.
#endif
