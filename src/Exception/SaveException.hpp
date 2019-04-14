#ifndef _DEF_OMEGLOND3D_SAVEEXCEPTION_HPP
#define _DEF_OMEGLOND3D_SAVEEXCEPTION_HPP

#include "OmglException.hpp"

namespace OMGL3D
{
    namespace EXCP
    {
        class SaveException : public OMGLException
        {

        public:

            SaveException(const std::string &message) throw() : OMGLException(message)
            {
            }
        };
    }
}

#endif
