#ifndef _BRUNODEA_BOX_HPP_
#define _BRUNODEA_BOX_HPP_

#include <vector>
#include "math/matrix_functions.hpp"
#include "glfw.h"

namespace model
{
    class Box
    {
    public:
        Box(float width, float height)
            : m_fWidth(width), m_fHeight(height), m_vVertices()
        {
            initVertices();
        }

        void drawInWireframe()
        {
            glTranslatef(0.f,m_fHeight,0.f);
            glBegin(GL_LINES);
                
                math::Vector3 v = m_vVertices.at(0);
                math::Vector3 v2 = m_vVertices.at(1);
                math::Vector3 v3 = m_vVertices.at(2);
                math::Vector3 v4 = m_vVertices.at(3);

                math::Vector3 v5 = m_vVertices.at(4);
                math::Vector3 v6 = m_vVertices.at(5);
                math::Vector3 v7 = m_vVertices.at(6);
                math::Vector3 v8 = m_vVertices.at(7);
                
                glVertex3f(v[0],v[1],v[2]);
                glVertex3f(v2[0],v2[1],v2[2]);
                
                glVertex3f(v2[0],v2[1],v2[2]);
                glVertex3f(v3[0],v3[1],v3[2]);
                
                glVertex3f(v3[0],v3[1],v3[2]);
                glVertex3f(v4[0],v4[1],v4[2]);
                
                glVertex3f(v4[0],v4[1],v4[2]);
                glVertex3f(v[0],v[1],v[2]);

                glVertex3f(v5[0],v5[1],v5[2]);
                glVertex3f(v[0],v[1],v[2]);
                
                glVertex3f(v5[0],v5[1],v5[2]);
                glVertex3f(v6[0],v6[1],v6[2]);
                
                glVertex3f(v6[0],v6[1],v6[2]);
                glVertex3f(v2[0],v2[1],v2[2]);

                glVertex3f(v6[0],v6[1],v6[2]);
                glVertex3f(v7[0],v7[1],v7[2]);
                
                glVertex3f(v7[0],v7[1],v7[2]);
                glVertex3f(v3[0],v3[1],v3[2]);

                glVertex3f(v7[0],v7[1],v7[2]);
                glVertex3f(v8[0],v8[1],v8[2]);

                glVertex3f(v8[0],v8[1],v8[2]);
                glVertex3f(v4[0],v4[1],v4[2]);
                
                glVertex3f(v8[0],v8[1],v8[2]);
                glVertex3f(v5[0],v5[1],v5[2]);

            glEnd();
        }

        float width() { return m_fWidth; }
        float height() { return m_fHeight; }
        void setHeight(float height) { m_fHeight = height; adjustVertices(); }
    private:
        void adjustVertices()
        {
            m_vVertices.clear();
            initVertices();
        }
        void initVertices()
        {
            float w = m_fWidth;
            float h = m_fHeight;
            
            math::Vector3 v1 = math::vector3f(-w,-h,-w);
            math::Vector3 v2 = math::vector3f(-w,-h,w);
            math::Vector3 v3 = math::vector3f(w,-h,w);
            math::Vector3 v4 = math::vector3f(w,-h,-w);

            math::Vector3 v5 = math::vector3f(-w,h,-w);
            math::Vector3 v6 = math::vector3f(-w,h,w);
            math::Vector3 v7 = math::vector3f(w,h,w);
            math::Vector3 v8 = math::vector3f(w,h,-w);
            
            m_vVertices.push_back(v1);
            m_vVertices.push_back(v2);
            m_vVertices.push_back(v3);
            m_vVertices.push_back(v4);

            m_vVertices.push_back(v5);
            m_vVertices.push_back(v6);
            m_vVertices.push_back(v7);
            m_vVertices.push_back(v8);
        }
    private:
        float m_fWidth;
        float m_fHeight;

        std::vector<math::Vector3> m_vVertices;

    }; //end of class Box.
} //end of namespace model.

#endif
