#ifndef _DEF_OMEGLOND3D_OGLDEPTHBUFFER_HPP
#define _DEF_OMEGLOND3D_OGLDEPTHBUFFER_HPP

#include "../../Core/IDepthBuffer.hpp"

namespace OMGL3D
{
    namespace OGL
    {
        class OGLDepthBuffer : public CORE::IDepthBuffer
        {

        public:

            OGLDepthBuffer();

            ~OGLDepthBuffer();

            void Clear();

            void Lock();

            void Unlock();

            void SetDepth(const CORE::DepthFunc &depth);
        };
    }
}

#endif
