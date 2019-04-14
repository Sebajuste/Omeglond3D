#ifndef _DEF_OMEGLOND3D_OGLFONTSYSTEM_HPP
#define _DEF_OMEGLOND3D_OGLFONTSYSTEM_HPP

#include "../../Font/IFont.hpp"
#include <GL/gl.h>

namespace OMGL3D
{
    namespace OGL
    {
        class OGLFontSystem : public FONT::IFont
        {

        public:

            OGLFontSystem(const std::string & name);

            ~OGLFontSystem();

            void LoadFont(const std::string & font_name, unsigned int size=12, bool bold=false, bool italic=false);

            void Draw(const std::string & text, const CORE::CColor & color=CORE::CColor::White);

        private:

            GLint _base;
        };
    }
}

#endif
