#ifndef _DEF_OMEGLOND3D_CCOLOR_HPP
#define _DEF_OMEGLOND3D_CCOLOR_HPP

namespace OMGL3D
{
    namespace CORE
    {
        class CColor
        {

        public:

            CColor();

            CColor(const float & r, const float & g, const float & b, const float & a=0);

            void SetColor(const float & r, const float & g, const float & b, const float & a=0);

            const float * operator *() const;

            static CColor Black;
            static CColor Blue;
            static CColor Green;
            static CColor Grey;
            static CColor Red;
            static CColor White;
            static CColor Yellow;


        private:

            float _color[4];
        };


    }
}

#endif
