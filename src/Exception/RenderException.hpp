#ifndef _DEF_OMEGLOND3D_RENDEREXCEPTION_HPP
#define _DEF_OMEGLOND3D_RENDEREXCEPTION_HPP

#include "OmglException.hpp"

namespace OMGL3D
{
    namespace EXCP
    {
        class RenderException : public OMGLException
        {

        public:

            RenderException(const std::string &message) throw() : OMGLException(message)
            {
            }
        };
    }
}

#endif
