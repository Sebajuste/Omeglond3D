#include "CColor.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        CColor::CColor()
        {
            _color[0] = 0.0f;
            _color[1] = 0.0f;
            _color[2] = 0.0f;
            _color[3] = 0.0f;
        }

        CColor::CColor(const float & r, const float & g, const float & b, const float & a)
        {
            _color[0] = r;
            _color[1] = g;
            _color[2] = b;
            _color[3] = a;
        }

        void CColor::SetColor(const float & r, const float & g, const float & b, const float & a)
        {
            _color[0] = r;
            _color[1] = g;
            _color[2] = b;
            _color[3] = a;
        }

        const float * CColor::operator*() const
        {
            return &_color[0];
        }

        CColor CColor::Black = CColor(0, 0, 0);
        CColor CColor::Blue = CColor(0, 0, 1.0f);
        CColor CColor::Green = CColor(0, 1.0f, 0);
        CColor CColor::Grey = CColor(0.5f, 0.5f, 0.5f);
        CColor CColor::Red = CColor(1.0f, 0, 0);
        CColor CColor::White = CColor(1.0f, 1.0f, 1.0f);
        CColor CColor::Yellow = CColor(1.0f, 1.0f, 0);
    }
}
