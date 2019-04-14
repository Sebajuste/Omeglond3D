#ifndef _DEF_OMEGLOND3D_OGLCOLORBUFFER_HPP
#define _DEF_OMEGLOND3D_OGLCOLORBUFFER_HPP

#include "../../Core/IColorBuffer.hpp"

namespace OMGL3D
{
    namespace OGL
    {
        class OGLColorBuffer : public CORE::IColorBuffer
        {

        public:

            OGLColorBuffer();

            ~OGLColorBuffer();

            void Clear();

            void Lock();

            void Unlock();
        };
    }
}

#endif
