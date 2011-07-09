#ifndef _BRUNODEA_MUNCK_MUNK_HPP_
#define _BRUNODEA_MUNCK_MUNK_HPP_

#include "math/matrix_functions.hpp"
#include "model/Object.hpp"
#include "model/Arm.hpp"
#include "model/Box.hpp"

#include <vector>

namespace model
{
    class MunckMunk : public Object
    {
    public:
        MunckMunk()
            : Object(math::vector3f(0.f,0.f,0.f)), m_Body(5.f,2.f), m_Arms(), m_iCurrArm(-1)
        {
            addArm();
            addArm();
            addArm();
            currentArm_next(true);
        }
        MunckMunk(const math::Vector3 &pos)
            : Object(pos), m_Body(5.f,2.f), m_Arms(), m_iCurrArm(-1)
        {
            addArm();
            addArm();
            addArm();
            currentArm_next(true);
        }
        MunckMunk(const math::Vector3 &pos, float body_width, float body_height)
            : Object(pos), m_Body(body_width,body_height), m_Arms(), m_iCurrArm(-1)
        {
            addArm();
            addArm();
            addArm();
            currentArm_next(true);
        }

        void addArm()
        {
            m_Arms.push_back(Arm(math::vector3f(0.f,0.f,0.f), 5.f));
        }
        void currentArm_next(bool up)
        {
            int dir = (up ? 1 : -1);
            unsigned int size = m_Arms.size();
            if(size > 0)
                m_iCurrArm = (m_iCurrArm + dir) % size;
            else
                m_iCurrArm = -1;
        }

        void rotateCurrArm(float roll, float yaw, float pitch)
        {
            for(unsigned int i = m_iCurrArm; i < m_Arms.size(); i++)
            {
                Arm *a = &m_Arms.at(i);
                a->rotate(roll,yaw,pitch);
            }
        }

        void drawWireframe()
        {
            glPushMatrix();
                m_Body.drawInWireframe();
                glTranslatef(0.f,m_Body.height(),0.f);
                drawArmsWireframe();
            glPopMatrix();
        }
    private:
        void drawArmsWireframe()
        {
            glPushMatrix();
                unsigned int size = m_Arms.size();
                    
                if(size > 0)
                {
                    Arm aux = m_Arms.at(0);
                    if(m_iCurrArm != 0)
                        glColor4f(1.f,1.f,1.f,1.f);
                    else
                        glColor4f(0.f,1.f,0.f,1.f);
                    
                    aux.drawWireframe();
                    math::Vector3 lastPt;
                    for(unsigned int i = 1; i < size; i++)
                    {
                        lastPt = aux.getMobilePoint();
                        aux = m_Arms.at(i);
                        if(i != m_iCurrArm)
                            glColor4f(1.f/(i*2),1.f/(i*3.f),1.f/(i*6.f),1.f);
                        else
                            glColor4f(0.f,1.f,0.f,1.f);
                        glTranslatef(lastPt[0],lastPt[1],lastPt[2]);
                        aux.drawWireframe();
                    }
                }
            glPopMatrix();
        }

    private:
        Box m_Body;
        std::vector<model::Arm> m_Arms;
        int m_iCurrArm;
    }; //end of class MunckMunk.
} //end of namespace model.

#endif
