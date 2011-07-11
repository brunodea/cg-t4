#ifndef _BRUNODEA_BEZIER_SURFACE_HPP_
#define _BRUNODEA_BEZIER_SURFACE_HPP_

#include "glfw.h"
#include "math/matrix_functions.hpp"
#include "math/Curves/Bezier.hpp"

#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

namespace math
{
    class BezierSurface
    {
    public:
        BezierSurface(unsigned int degree)
            : m_Bezier(), m_vPatch(), m_iDegree(degree)
        {
            init(); 
        }

        void draw(bool wireframe)
        {
            if(wireframe)
            {
                glBegin(GL_LINES);
                drawVertices();
            }
            else
            {
                glBegin(GL_QUADS);
                drawQuads();
            }

            glEnd();
        }

        void adjustControlPoint(float val_y, unsigned int cp_row, unsigned int cp_col)
        {
            m_Bezier.adjustControlPointY(val_y, cp_row, cp_col);
            updatePatches(0.0415f);
        }
        
        void updatePatches(float precision)
        {
            m_vPatch.clear();
            for(float u = 0; u < 1.f; u += precision)
            {
                for(float v = 0; v < 1.f; v += precision)
                {
                    math::Vector3 vec = m_Bezier.point(u,v);
                    m_vPatch.push_back(vec);
                }
            }
            m_PatchLen = (int)sqrt((float)m_vPatch.size());
        }

        void randomControlPoints()
        {
            srand((unsigned int)time(0));
            for(unsigned int i = 0; i < m_iDegree; i++)
            {
                for(unsigned int j = 0; j < m_iDegree; j++)
                    m_Bezier.adjustControlPointY((rand()%10)*pow(-1.f,rand()%2),i,j);
            }
            updatePatches(0.0415f); //0.0415f melhor precisao.
        }

        void flatSurface()
        {
            for(unsigned int i = 0; i < m_iDegree; i++)
            {
                for(unsigned int j = 0; j < m_iDegree; j++)
                    m_Bezier.adjustControlPointY(0,i,j);
            }
            updatePatches(0.0415f); //0.0415f melhor precisao.
        }
        math::Vector3 length()
        {
            unsigned int size = m_Bezier.controlPoints()->size();
            math::Vector3 p1 = m_Bezier.controlPoints()->at(0).at(0);
            math::Vector3 p2 = m_Bezier.controlPoints()->at(0).at(size-1);
            return p1-p2;
        }

        Bezier getBezier() { return m_Bezier; }

    private:
        void init()
        {
            srand((unsigned int)time(0));
            for(unsigned int i = 0; i < m_iDegree; i++)
            {
                std::vector<math::Vector3> vs;
                for(unsigned int j = 0; j < m_iDegree; j++)
                {
                    float x = (float)i;
                    float y = (float)(rand()%10*pow(-1.f,(rand()%2)+1));
                    float z = (float)j;
                    vs.push_back(math::vector3f(x,y,z));
                }
                m_Bezier.addControlPoints(vs);
            }
            updatePatches(0.0415f); //0.0415f melhor precisao.
        }

        void drawQuads()
        {
            for(int i = 0; i < m_PatchLen-1; i++)
            {
                for(int j = 0; j < m_PatchLen-1; j++)
                {
                    math::Vector4 p = math::toVector4f(m_vPatch.at((i*m_PatchLen)+j));
                    math::Vector4 p2 = math::toVector4f(m_vPatch.at(((i+1)*m_PatchLen)+j));
                    math::Vector4 p3 = math::toVector4f(m_vPatch.at(((i+1)*m_PatchLen)+j+1));
                    math::Vector4 p4 = math::toVector4f(m_vPatch.at((i*m_PatchLen)+j+1));

                    math::Vector3 normal = math::toVector3f(math::normalize(p2.crossProduct(p4)));

                    glNormal3f(normal[0],normal[1],normal[2]);
                    glVertex3f(p[0], p[1], p[2]);
                    glVertex3f(p2[0], p2[1], p2[2]);
                    glVertex3f(p3[0], p3[1], p3[2]);
                    glVertex3f(p4[0], p4[1], p4[2]);
                }
            }
        }

        void drawVertices()
        {
            for(int i = 0; i < m_PatchLen-1; i++)
            {
                for(int j = 0; j < m_PatchLen-1; j++)
                {
                    math::Vector4 p = math::toVector4f(m_vPatch.at((i*m_PatchLen)+j));
                    math::Vector4 p2 = math::toVector4f(m_vPatch.at(((i+1)*m_PatchLen)+j));
                    math::Vector4 p3 = math::toVector4f(m_vPatch.at(((i+1)*m_PatchLen)+j+1));
                    math::Vector4 p4 = math::toVector4f(m_vPatch.at((i*m_PatchLen)+j+1));

                    math::Vector3 normal = math::toVector3f(math::normalize(p.crossProduct(p3)));
                    
                    glNormal3f(normal[0],normal[1],normal[2]);
                    glVertex3f(p[0], p[1], p[2]);
                    glVertex3f(p2[0], p2[1], p2[2]);
                    glVertex3f(p[0], p[1],p[2]);
                    glVertex3f(p4[0], p4[1], p4[2]);

                    if(i == m_PatchLen-2)
                    {
                        glVertex3f(p2[0], p2[1], p2[2]);
                        glVertex3f(p3[0], p3[1], p3[2]);
                    }
                    if(j == m_PatchLen-2)
                    {                           
                        glVertex3f(p4[0], p4[1], p4[2]);
                        glVertex3f(p3[0], p3[1], p3[2]);
                    }
                }
            }
        }

    private:
        Bezier m_Bezier;
        std::vector<math::Vector3> m_vPatch;
        unsigned int m_iDegree;
        int m_PatchLen;
    }; //end of class BezierSurface.
} //end of namespace math.


#endif
