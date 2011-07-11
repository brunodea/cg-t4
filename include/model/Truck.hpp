/**
    eh simplesmente um modelo de um caminhao que carrega na sua cacamba um MunckMunk(a estrutura
    com os bracos).
 **/
#ifndef _BRUNODEA_TRUCK_HPP_
#define _BRUNODEA_TRUCK_HPP_

#include "math/matrix_functions.hpp"
#include "model/DirectedObject.hpp"
#include "model/MunckMunk.hpp"
#include "model/Box.hpp"
#include "model/Cylinder.hpp"

namespace model
{
    class Truck : public DirectedObject
    {
    public:
        Truck()
            : DirectedObject(math::vector3f(0.f,0.f,0.f),1.5f), m_MunckMunk(),
              m_FrontBox(1.f,1.f),m_CabinBox(.5f,.3f),m_BodyBox(.5f,.2f)
        {
            setDirection(math::vector3f(-1.f,0.f,0.f));
        }

        void draw(bool wireframe)
        {
            glPushMatrix();
                glTranslatef(pos()[0],pos()[1],pos()[2]);
                
                glRotatef(math::radToDegree(m_fRoll) ,1.f,0.f,0.f);
                glRotatef(math::radToDegree(m_fYaw)  ,0.f,1.f,0.f);
                glRotatef(math::radToDegree(m_fPitch),0.f,0.f,1.f);

                glScalef(2.f,2.f,3.f);
                glTranslatef(.5f,.5f,0.f);
                glTranslatef(-3.f,0.f,0.f);
                m_FrontBox.draw(wireframe);
                glPushMatrix();
                    glScalef(1.f,2.f,2.f);
                    glTranslatef(.5f,1.f,0.f);
                    m_CabinBox.draw(wireframe);
                    
                    glPushMatrix();
                        glColor4f(0.f,0.f,1.f,1.f);
                        glScalef(5.f,1.f,1.3f);
                        glTranslatef(.6f,-1.f,0.f);
                        m_BodyBox.draw(wireframe);
                    glPopMatrix();
                glPopMatrix();
                glPushMatrix();
                    glScalef(.2f,.2f,.2f);
                    glTranslatef(17.f,4.f,0.f);
                    m_MunckMunk.draw(wireframe);
                glPopMatrix();
            glPopMatrix();
        }

        MunckMunk *munckMunk() { return &m_MunckMunk; }

    private:
        MunckMunk m_MunckMunk;
        Box m_FrontBox;
        Box m_CabinBox;
        Box m_BodyBox;
    }; //end of class Truck.
} //end of namespace model.
#endif
