#ifndef _DEF_OMEGLOND3D_WRITEEXCEPTION_HPP
#define _DEF_OMEGLOND3D_WRITEEXCEPTION_HPP

#include "OmglException.hpp"

namespace OMGL3D
{
    namespace EXCP
    {
        class WriteException : public OMGLException
        {

        public:

            WriteException(const std::string &message) throw() : OMGLException(message)
            {
            }
        };
    }
}

#endif
