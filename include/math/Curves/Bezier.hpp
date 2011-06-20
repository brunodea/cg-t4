#ifndef _BRUNODEA_BEZIER_HPP_
#define _BRUNODEA_BEZIER_HPP_

#include "math/matrix_functions.hpp"
#include "math/Curves/math_aux.hpp"
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

namespace math
{
    class Bezier
    {
    public:
        Bezier() : m_vControlPoints() {}

        void addControlPoints(const std::vector<math::Vector3> &ps) { m_vControlPoints.push_back(ps); }

        math::Vector3 point(float u, float v)
        {
            math::Vector3 p(0);

            unsigned int n = m_vControlPoints.size();
            unsigned int m = n;

            for(unsigned int i = 0; i < n; i++)
            {
                for(unsigned int j = 0; j < m; j++)
                    p += m_vControlPoints.at(i).at(j)*blend(m-1,j,v)*blend(n-1,i,u);
            }
            return p;
        }

        float blend(int n, int i, float u)
        {
            return (float)((float)factorial(n)/(float)(factorial(i)*factorial(n-i)))*pow(u,i)*pow(1-u,n-i);
        }

        void drawControlPointsInPoints()
        {
            glBegin(GL_POINTS);
                for(unsigned int i = 0; i < m_vControlPoints.size(); i++)
                {
                    for(unsigned int j = 0; j < m_vControlPoints.size(); j++)
                    {
                        math::Vector4 p = math::toVector4f(m_vControlPoints.at(i).at(j));
                        glVertex2f(p[0], p[1]);
                    }
                }
            glEnd();
        }

        void adjustControlPointY(float val, unsigned int row, unsigned int col)
        {
            if(row < 0 || row >= m_vControlPoints.size() || col < 0 || col >= m_vControlPoints.size())
                return;
            m_vControlPoints.at(row).at(col)[1] = val;
        }

        void drawControlPointsInLines()
        {
            glBegin(GL_LINES);
                for(unsigned int i = 0; i < m_vControlPoints.size()-1; i++)
                {
                    for(unsigned int j = 0; j < m_vControlPoints.at(i).size()-1; j++)
                    {
                        math::Vector4 p = math::toVector4f(m_vControlPoints.at(i).at(j));
                        math::Vector4 p2 = math::toVector4f(m_vControlPoints.at(i+1).at(j));
                        math::Vector4 p4 = math::toVector4f(m_vControlPoints.at(i).at(j+1));

                        glVertex2f(p[0], p[1]);
                        glVertex2f(p2[0], p2[1]);
                        glVertex2f(p[0], p[1]);
                        glVertex2f(p4[0], p4[1]);

                        if(i == m_vControlPoints.size()-2)
                        {
                            math::Vector4 p3 = math::toVector4f(m_vControlPoints.at(i+1).at(j+1));
                            
                            glVertex2f(p2[0], p2[1]);
                            glVertex2f(p3[0], p3[1]);
                        }
                        if(j == m_vControlPoints.size()-2)
                        {
                            math::Vector4 p3 = math::toVector4f(m_vControlPoints.at(i+1).at(j+1));

                            glVertex2f(p4[0], p4[1]);
                            glVertex2f(p3[0], p3[1]);
                        }
                    }
                }
            glEnd();
        }

    private:
        std::vector<std::vector<math::Vector3>> m_vControlPoints;

    }; //end of class Bezier.
} //end of namespace math.

#endif
