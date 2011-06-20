#ifndef _BRUNODEA_CAMERA_HPP_
#define _BRUNODEA_CAMERA_HPP_

#include "math/matrix_functions.hpp"

class Camera
{
public:
    Camera(const math::Vector3 &eye, const math::Vector3 &target, const math::Vector3 &up)
        : m_vEye3(eye), m_vTarget3(target), m_vUp3(up)
    {
        adjustAxes();
        m_fSpeed = 1.f;
    }

    void moveForward() { m_vEye3 -= m_vDirection3*m_fSpeed; }
    void moveBackwards() { m_vEye3 += m_vDirection3*m_fSpeed; }
    void moveLeft() { m_vEye3 -= m_vRight3*m_fSpeed; }
    void moveRight() { m_vEye3 += m_vRight3*m_fSpeed; }
    void moveUp() { m_vEye3 += m_vUp3*m_fSpeed; }
    void moveDown() { m_vEye3 -= m_vUp3*m_fSpeed; }

    math::Vector3 eye() { return m_vEye3; }
    math::Vector3 target() { return m_vTarget3; }
    math::Vector3 up() { return m_vUp3; }

    void setSpeed(float speed) { m_fSpeed = speed; }
    float getSpeed() { return m_fSpeed; }

private:
    void adjustAxes()
    {
        m_vDirection3 = math::normalize(m_vTarget3 - m_vEye3);
        m_vRight3 = math::normalize(m_vUp3.crossProduct(m_vDirection3));
        m_vUp3 = m_vDirection3.crossProduct(m_vRight3);
    }

private:
    math::Vector3 m_vEye3;
    math::Vector3 m_vTarget3;
    math::Vector3 m_vUp3;
    math::Vector3 m_vDirection3;
    math::Vector3 m_vRight3;

    float m_fSpeed;

}; //end of class Camera.
#endif
