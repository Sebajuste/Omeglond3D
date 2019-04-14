#ifndef _DEF_OMEGLOND3D_OGL3BUFFERVERTEX_HPP
#define _DEF_OMEGLOND3D_OGL3BUFFERVERTEX_HPP

#include "../../Core/IBufferBase.hpp"

#include <GL/gl.h>

namespace OMGL3D
{
    namespace OGL3
    {
        class OGL3BufferVertex : public CORE::IBufferBase
        {

        public:

            OGL3BufferVertex(unsigned int size, unsigned int stride);

            ~OGL3BufferVertex();

            unsigned char * Lock(unsigned int offset, unsigned int size);

            const unsigned char * ConstLock(unsigned int offset, unsigned int size) const;

            void Unlock() const;

            const unsigned char * GetBuffer() const;


        private:

            unsigned char * _datas;
        };
    }
}

#endif
