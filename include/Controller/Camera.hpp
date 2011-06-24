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

    void rotate(float roll_angle, float yaw_angle, float pitch_angle)
    {
        math::Matrix4 m = math::rotateZ(pitch_angle)*math::rotateY(yaw_angle)*math::rotateX(roll_angle);
        transform(m);
    }

    void moveForward() { m_vEye3 += m_vDirection3*m_fSpeed; }
    void moveBackwards() { m_vEye3 -= m_vDirection3*m_fSpeed; }
    void moveLeft() { m_vEye3 += m_vRight3*m_fSpeed; }
    void moveRight() { m_vEye3 -= m_vRight3*m_fSpeed; }
    void moveUp() { m_vEye3 -= m_vUp3*m_fSpeed; }
    void moveDown() { m_vEye3 += m_vUp3*m_fSpeed; }
    
    math::Vector3 eye() { return m_vEye3; }
    void setEye(const math::Vector3 &eye) { m_vEye3 = eye; }

    math::Vector3 target() { return m_vTarget3; }
    void setTarget(const math::Vector3 &target) { m_vTarget3 = target; }

    math::Vector3 up() { return m_vUp3; }
    void setUp(const math::Vector3 &up) { m_vUp3 = up; }

    math::Vector3 direction() { return m_vDirection3; }
    void setDirection(const math::Vector3 &direction) { m_vDirection3 = direction; }

    math::Vector3 right() { return m_vRight3; }
    void setRight(const math::Vector3 &right) { m_vRight3 = right; }

    void setSpeed(float speed) { m_fSpeed = speed; }
    float getSpeed() { return m_fSpeed; }

    void adjustAxes()
    {
        m_vDirection3 = math::normalize(m_vTarget3 - m_vEye3);
        m_vRight3 = math::normalize(m_vUp3.crossProduct(m_vDirection3));
        m_vUp3 = m_vDirection3.crossProduct(m_vRight3);
    }
private:
    void transform(const math::Matrix4 &mat)
    {
        math::Matrix4 m = mat;

        math::Vector4 dir = math::toVector4f(m_vDirection3);
        dir = m*dir;
        m_vDirection3 = math::normalize(math::toVector3f(dir));

        math::Vector4 up = math::toVector4f(m_vUp3);
        up = m*up;
        m_vUp3 = math::normalize(math::toVector3f(up));

        math::Vector4 right = math::toVector4f(m_vRight3);
        right = m*right;
        m_vRight3 = math::normalize(math::toVector3f(right));
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
