#ifndef _DEF_OMEGLOND3D_LOADEXCEPTION_HPP
#define _DEF_OMEGLOND3D_LOADEXCEPTION_HPP

#include "OmglException.hpp"

namespace OMGL3D
{
    namespace EXCP
    {
        class LoadException : public OMGLException
        {
            public:
            LoadException(const std::string &message) throw() : OMGLException(message)
            {
            }
        };
    }
}

#endif
