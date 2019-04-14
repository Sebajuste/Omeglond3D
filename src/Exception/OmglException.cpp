#include "OmglException.hpp"

#include "../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace EXCP
    {
        OMGLException::OMGLException(const std::string &message) throw() : _message(message)
        {
        }

        OMGLException::~OMGLException() throw()
        {
        }

        const char* OMGLException::What() const throw()
        {
            return _message.c_str();
        }

        const char* OMGLException::what() const throw()
        {
            return _message.c_str();
        }
    }
}
