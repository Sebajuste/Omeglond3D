#ifndef _DEF_OMEGLOND3D_ICOLORBUFFER_HPP
#define _DEF_OMEGLOND3D_ICOLORBUFFER_HPP

#include "IFrameBuffer.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class IColorBuffer : public IFrameBuffer
        {

        public:

            IColorBuffer(const std::string &name) : IFrameBuffer(name) {}

            virtual ~IColorBuffer() {}

            virtual void Clear()=0;

            virtual void Lock()=0;

            virtual void Unlock()=0;
        };
    }
}

#endif
