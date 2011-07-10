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
            : Object(math::vector3f(0.f,0.f,0.f)), m_Body(5.f,2.f), m_Arms(), m_iCurrArm(-1), m_Pistoes()
        {
            m_fMaxAngle = PI-(PI/10.f);
            m_fMinAngle = PI/10.f;
            addArm();
            addArm();
            addArm();
            addArm();
            addArm();
            currentArm_next(true);
        }

        void addArm()
        {
            Arm a = Arm(math::vector3f(0.f,0.f,0.f), 5.f);
            m_Arms.push_back(a);
            unsigned int size = m_Arms.size();
            if(size > 1)
            {
                Arm *pa = &m_Arms.at(size-1);
                pa->rotate(0.f,0.f,(m_fMinAngle*1.05f)*(size-1));
                math::Vector3 base;
                if(m_Pistoes.size() > 1)
                    base = m_Pistoes.at(m_Pistoes.size()-1).mobilePoint();
                else
                    base = math::vector3f(0.f,0.f,0.f);
                m_Pistoes.push_back(Pistao(base, a.pos()+(a.getMobilePoint()/2.f)));
            }
        }
        void currentArm_next(bool up)
        {
            int dir = (up ? 1 : -1);
            unsigned int size = m_Arms.size();
            if(size > 0)
            {
                int v = m_iCurrArm + dir;
                v = (v < 0 ? size-1 : v);
                m_iCurrArm = v % size;
            }
            else
                m_iCurrArm = -1;
        }
        void growCurrentArm(bool up)
        {
            Arm *a = &m_Arms.at(m_iCurrArm);
            math::Vector3 mp = a->getMobilePoint();
            if(up)
                mp *= 1.05;
            else
            {
                if(math::distance(mp, math::vector3f(0.f,0.f,0.f)) <= 1.f)
                    return;
                mp *= .95;
            }
            a->setMobilePoint(mp);
        }

        void rotateCurrArm(float roll, float yaw, float pitch)
        {
            if(m_iCurrArm == 0) //primeiro braco eh fixo.
                return;
            for(unsigned int i = m_iCurrArm; i < m_Arms.size(); i++)
            {
                Arm *a = &m_Arms.at(i);
                a->rotate(roll,yaw,pitch);
                float angle = math::angle(a->getMobilePoint(), m_Arms.at(i-1).getMobilePoint());
                if(angle >= m_fMaxAngle || angle < m_fMinAngle)
                {
                    a->rotate(-roll,-yaw,-pitch);
                    break;
                }
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
                    Arm *aux = &m_Arms.at(0);
                    if(m_iCurrArm != 0)
                        glColor4f(1.f,1.f,1.f,1.f);
                    else
                        glColor4f(0.f,1.f,0.f,1.f);
                    
                    aux->drawWireframe();
                    math::Vector3 lastPt;
                    Pistao *pistao;
                    for(unsigned int i = 1; i < size; i++)
                    {
                        lastPt = aux->getMobilePoint();
                        aux = &m_Arms.at(i);
                        aux->setPos(lastPt);

                        if(i != m_iCurrArm)
                            glColor4f(1.f/(i*1.05f),1.f/(i*1.2f),1.f/(i*1.32f),1.f);
                        else
                            glColor4f(0.f,1.f,0.f,1.f);
                        glTranslatef(lastPt[0],lastPt[1],lastPt[2]);
                        aux->drawWireframe();

                        glPushMatrix();
                            math::Vector3 pos = math::vector3f(0.f,0.f,0.f);
                            for(unsigned int j = 0; j < i; j++)
                            {
                                pos += m_Arms.at(i).pos();
                                glTranslatef(-lastPt[0],-lastPt[1],-lastPt[2]);
                            }
                            pistao = &m_Pistoes.at(i-1);
                            if(i > 1)
                                pistao->setBasePoint(pos-(m_Arms.at(i-1).getMobilePoint()/2.f));
                            pistao->setMobilePoint(pos+(aux->getMobilePoint()/2.f));

                            glColor4f(0.f,0.f,1.f,1.f);
                            pistao->drawInWireframe();
                        glPopMatrix();

                    }
                }
            glPopMatrix();
        }

    private:
        Box m_Body;
        std::vector<Arm> m_Arms;
        std::vector<Pistao> m_Pistoes;
        int m_iCurrArm;

        /*max/min angulo entre 2 braços.*/
        float m_fMaxAngle;
        float m_fMinAngle;

    }; //end of class MunckMunk.
} //end of namespace model.

#endif
