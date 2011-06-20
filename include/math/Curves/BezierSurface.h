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
        enum DrawType
        {
            DRAW_LINES = 0,
            DRAW_POINTS
        };

    public:
        BezierSurface(unsigned int degree)
            : m_Bezier(), m_vPatch(), m_iDegree(degree)
        {
            init(); 
        }

        void draw(DrawType dt=DRAW_LINES)
        {
            switch(dt)
            {
            case DRAW_LINES:
                drawWireframe();
                break;
            case DRAW_POINTS:
                drawCloud();
                break;
            default:
                drawWireframe();
                break;
            }
        }

        void drawWireframe()
        {
            glBegin(GL_LINES);
                for(unsigned int i = 0; i < m_PatchLen-1; i++)
                {
                    for(unsigned int j = 0; j < m_PatchLen-1; j++)
                    {
                        math::Vector4 p = math::toVector4f(m_vPatch.at((i*m_PatchLen)+j));
                        math::Vector4 p2 = math::toVector4f(m_vPatch.at(((i+1)*m_PatchLen)+j));
                        math::Vector4 p4 = math::toVector4f(m_vPatch.at((i*m_PatchLen)+j+1));
                        
                        glVertex2f(p[0], p[1]);
                        glVertex2f(p2[0], p2[1]);
                        glVertex2f(p[0], p[1]);
                        glVertex2f(p4[0], p4[1]);

                        if(i == m_PatchLen-2)
                        {
                            math::Vector4 p3 = math::toVector4f(m_vPatch.at(((i+1)*m_PatchLen)+j+1));
                            
                            glVertex2f(p2[0], p2[1]);
                            glVertex2f(p3[0], p3[1]);
                        }
                        if(j == m_PatchLen-2)
                        {
                            math::Vector4 p3 = math::toVector4f(m_vPatch.at(((i+1)*m_PatchLen)+j+1));

                            glVertex2f(p4[0], p4[1]);
                            glVertex2f(p3[0], p3[1]);
                        }
                    }
                }
            glEnd();
        }

        void drawCloud()
        {
            glBegin(GL_POINTS);
                for(unsigned int i = 0; i < m_vPatch.size(); i++)
                {
                    math::Vector4 p = math::toVector4f(m_vPatch.at(i));
                    glVertex2f(p[0], p[1]);
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
                    float x = i;
                    float y = rand()%10*pow(-1.f,(rand()%2)+1);
                    float z = j;
                    vs.push_back(math::vector3f(x,y,z));
                }
                m_Bezier.addControlPoints(vs);
            }
            updatePatches(0.0415f); //0.0415f melhor precisao.
        }

    private:
        Bezier m_Bezier;
        std::vector<math::Vector3> m_vPatch;
        unsigned int m_iDegree;
        int m_PatchLen;
    }; //end of class BezierSurface.
} //end of namespace math.


#endif
