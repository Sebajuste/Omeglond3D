#ifndef _DEF_OMEGLOND3D_OGL3FONTSYSTEM_HPP
#define _DEF_OMEGLOND3D_OGL3FONTSYSTEM_HPP

#include "../../Font/IFont.hpp"
#include <GL/gl.h>

namespace OMGL3D
{
    namespace OGL3
    {
        class OGL3FontSystem : public FONT::IFont
        {

        public:

            OGL3FontSystem(const std::string & name);

            ~OGL3FontSystem();

            void LoadFont(const std::string & font_name);

            void Draw(const std::string & text, const CORE::CColor & color=CORE::CColor::White);

        private:

            GLint _base;
        };
    }
}

#endif
