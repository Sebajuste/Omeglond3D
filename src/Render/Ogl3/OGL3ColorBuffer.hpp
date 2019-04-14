#ifndef _DEF_OMEGLOND3D_OGL3COLORBUFFER_HPP
#define _DEF_OMEGLOND3D_OGL3COLORBUFFER_HPP

#include "../../Core/IColorBuffer.hpp"

namespace OMGL3D
{
    namespace OGL3
    {
        class OGL3ColorBuffer : public CORE::IColorBuffer
        {

        public:

            OGL3ColorBuffer();

            ~OGL3ColorBuffer();

            void Clear();

            void Lock();

            void Unlock();
        };
    }
}

#endif

