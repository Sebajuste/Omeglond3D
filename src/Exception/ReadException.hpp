#ifndef _DEF_OMEGLOND3D_READEXCEPTION_HPP
#define _DEF_OMEGLOND3D_READEXCEPTION_HPP

#include "OmglException.hpp"

namespace OMGL3D
{
    namespace EXCP
    {
        class ReadException : public OMGLException
        {

        public:

            ReadException(const std::string &message) throw() : OMGLException(message)
            {
            }
        };
    }
}

#endif
