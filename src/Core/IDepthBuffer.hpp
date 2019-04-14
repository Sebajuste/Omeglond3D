#ifndef _DEF_OMEGLOND3D_IDEPTHBUFFER_HPP
#define _DEF_OMEGLOND3D_IDEPTHBUFFER_HPP

#include "IFrameBuffer.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        enum DepthFunc
        {
            OMGL_DEPTH_LESS,
            OMGL_DEPTH_EQUAL,
        };

        class IDepthBuffer : public IFrameBuffer
        {

        public:

            IDepthBuffer(const std::string &name) : IFrameBuffer(name) {}

            virtual ~IDepthBuffer() {}

            virtual void Clear()=0;

            virtual void Lock()=0;

            virtual void Unlock()=0;

            virtual void SetDepth(const DepthFunc &depth)=0;
        };
    }
}

#endif
