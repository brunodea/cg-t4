/*
    Classe abstrata que representa um simples objeto. Que pode ser desenhado e tem uma
    posicao no mundo.
 */
#ifndef _BRUNODEA_OBJECT_HPP_
#define _BRUNODEA_OBJECT_HPP_

#include "math/matrix_functions.hpp"

namespace model
{
    class Object
    {
    public:
        Object(const math::Vector3 &pos) 
            : m_Position(pos)
        {}

        virtual void draw(bool wireframe) = 0;

        void setPos(const math::Vector3 &pos) { m_Position = pos; }
        math::Vector3 pos() { return m_Position; }

    protected:
        math::Vector3 m_Position;

    }; //end of class Object.
} //end of namespace model.

#endif
