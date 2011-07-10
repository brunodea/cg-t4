#ifndef _BRUNODEA_CYLINDER_HPP_
#define _BRUNODEA_CYLINDER_HPP_

#include "math/matrix_functions.hpp"
#include "glfw.h"
#include "macros.h"
#include <vector>
#include <cmath>

namespace model
{
    class Cylinder
    {
    public:
        Cylinder(float radius, float height)
            : m_fRadius(radius), m_fHeight(height), m_vVertices()
        {
            initVertices();
        }

        void draw(bool wireframe)
        {
            glPushMatrix();
                glTranslatef(0.f,m_fHeight/2.f,0.f);
                if(wireframe)
                    glBegin(GL_LINES);
                else
                    glBegin(GL_TRIANGLE_FAN);
                drawVertices();
                glEnd();
            glPopMatrix();
        }

        void setHeight(float h) 
        {
            reloadVertices();
            m_fHeight = h; 
        }
        float getHeight() { return m_fHeight; }

    private:

        void reloadVertices()
        {
            m_vVertices.clear();
            initVertices();
        }

        void initVertices()
        {
            for(float i = 0; i <= 2*PI; i += 0.1f)
                m_vVertices.push_back(math::vector3f(m_fRadius*cos(i),-m_fHeight/2.f,m_fRadius*sin(i)));
            
            for(float i = 0; i <= 2*PI; i += 0.1f)
                m_vVertices.push_back(math::vector3f(m_fRadius*cos(i),m_fHeight/2.f,m_fRadius*sin(i)));
        }

        void drawVertices()
        {
            unsigned int size = m_vVertices.size();
            /* circulo inferior */
            for(unsigned int i = size/2; i < size-1; i++)
            {
                math::Vector3 v1 = m_vVertices.at(i);
                math::Vector3 v2 = m_vVertices.at(i+1);
                glVertex3f(v1[0],v1[1],v1[2]);
                glVertex3f(v2[0],v2[1],v2[2]);
            }

            /* circulo superior */
            for(unsigned int i = 0; i < size/2; i++)
            {
                math::Vector3 v1 = m_vVertices.at(i);
                math::Vector3 v2 = m_vVertices.at(i+1);
                glVertex3f(v1[0],v1[1],v1[2]);
                glVertex3f(v2[0],v2[1],v2[2]);
            }
                    
            /* linhas verticais */
            for(unsigned int i = 0; i < size/2; i++)
            {
                math::Vector3 v1 = m_vVertices.at(i);
                math::Vector3 v2 = m_vVertices.at((size/2)+i);
                glVertex3f(v1[0],v1[1],v1[2]);
                glVertex3f(v2[0],v2[1],v2[2]);
            }
        }

    private:
        float m_fRadius;
        float m_fHeight;

        std::vector<math::Vector3> m_vVertices;

    }; //end of class Cylinder.
} //end of namespace model.

#endif
