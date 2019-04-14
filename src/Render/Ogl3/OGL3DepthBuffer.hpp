#ifndef _DEF_OMEGLOND3D_OGL3DEPTHBUFFER_HPP
#define _DEF_OMEGLOND3D_OGL3DEPTHBUFFER_HPP

#include "../../Core/IDepthBuffer.hpp"

namespace OMGL3D
{
    namespace OGL3
    {
        class OGL3DepthBuffer : public CORE::IDepthBuffer
        {

        public:

            OGL3DepthBuffer();

            ~OGL3DepthBuffer();

            void Clear();

            void Lock();

            void Unlock();

            void SetDepth(const CORE::DepthFunc &depth);
        };
    }
}

#endif

