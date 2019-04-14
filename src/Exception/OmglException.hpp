#ifndef _DEF_OMEGLOND3D_OMGLEXCEPTION_HPP
#define _DEF_OMEGLOND3D_OMGLEXCEPTION_HPP

 #include <exception>
 #include <string>

namespace OMGL3D
{
    namespace EXCP
    {
        class OMGLException : public std::exception
        {

        public:

            OMGLException(const std::string &message) throw();

            virtual ~OMGLException() throw();

            virtual const char* What() const throw();

            virtual const char* what() const throw();


        private:

            std::string _message;
        };
    }
}

#endif
