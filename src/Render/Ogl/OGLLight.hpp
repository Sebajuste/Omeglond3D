#ifndef _DEF_OMEGLOND3D_OGLLIGHT_HPP
#define _DEF_OMEGLOND3D_OGLLIGHT_HPP

#include "../../Core/CLight.hpp"
#include <GL/gl.h>

namespace OMGL3D
{
    namespace OGL
    {
        class OGLLight : public CORE::CLight
        {

        public:

            OGLLight(const std::string & name);

            ~OGLLight();

            void Enable(unsigned int canal);

            void Disable(unsigned int canal);


        private:

            static GLint _max_lights;
        };
    }
}

#endif
