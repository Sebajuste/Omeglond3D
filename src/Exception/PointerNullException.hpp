#ifndef _DEF_OMEGLOND3D_POINTERNULLEXCEPTION_HPP
#define _DEF_OMEGLOND3D_POINTERNULLEXCEPTION_HPP

#include "OmglException.hpp"

namespace OMGL3D
{
    namespace EXCP
    {
        class PointerNullException : public OMGLException
        {

        public:

            PointerNullException(const std::string &message) throw() : OMGLException(message)
            {
            }
        };
    }
}

#endif
