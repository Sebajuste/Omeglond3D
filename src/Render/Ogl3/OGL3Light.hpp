#ifndef _DEF_OMEGLOND3D_OGLLIGHT_HPP
#define _DEF_OMEGLOND3D_OGLLIGHT_HPP

#include "../../Core/CLight.hpp"
#include <GL/gl.h>

namespace OMGL3D
{
    namespace OGL3
    {
        class OGL3Light : public CORE::CLight
        {

        public:

            OGL3Light(const std::string & name);

            ~OGL3Light();

            void Enable(unsigned int canal);

            void Disable(unsigned int canal);


        private:

            static GLint _max_lights;
        };
    }
}

#endif
