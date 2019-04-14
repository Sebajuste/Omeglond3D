#ifndef _DEF_OMEGLOND3D_OGLBUFFERVERTEX_HPP
#define _DEF_OMEGLOND3D_OGLBUFFERVERTEX_HPP

#include "../../Core/IBufferBase.hpp"

#include <GL/gl.h>

namespace OMGL3D
{
    namespace OGL
    {
        class OGLBufferVertex : public CORE::IBufferBase
        {

        public:

            OGLBufferVertex(unsigned int size, unsigned int stride);

            ~OGLBufferVertex();

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
