#ifndef _DEF_OMEGLOND3D_IFRAMEBUFFER_HPP
#define _DEF_OMEGLOND3D_IFRAMEBUFFER_HPP

#include "CResource.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class IFrameBuffer : public CResource
        {

        public:

            IFrameBuffer(const std::string &name) : CResource(name) {}

            virtual ~IFrameBuffer() {}

            virtual void Clear()=0;

            virtual void Lock()=0;

            virtual void Unlock()=0;
        };
    }
}

#endif
