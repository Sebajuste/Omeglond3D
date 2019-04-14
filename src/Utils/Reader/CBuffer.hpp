#ifndef _DEF_OMEGLOND3D_CBUFFER_HPP
#define _DEF_OMEGLOND3D_CBUFFER_HPP

#include <string>

namespace OMGL3D
{
    namespace UTILS
    {
        class CBuffer
        {

        public:

            CBuffer();

            CBuffer(const std::string & name);

            CBuffer(const CBuffer & buffer);

            CBuffer(const std::string & name, const std::string & buffer);

            ~CBuffer();

            std::string GetName() const;

            std::string GetBuffer() const;


        private:

            std::string _name, _buffer;
        };
    }
}

#endif
