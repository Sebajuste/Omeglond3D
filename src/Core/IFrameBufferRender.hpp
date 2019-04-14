#ifndef _DEF_OMEGLOND3D_IFRAMEBUFFERRENDER_HPP
#define _DEF_OMEGLOND3D_IFRAMEBUFFERRENDER_HPP

#include "IFrameBuffer.hpp"
#include "ITexture.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class IFrameBufferRender : public IFrameBuffer
        {

        public:

            IFrameBufferRender(const std::string & name) : IFrameBuffer(name) {}

            virtual ~IFrameBufferRender() {}

            virtual void Clear()=0;

            virtual void Lock()=0;

            virtual void Unlock()=0;

            virtual void Enable()=0;

            virtual void Disable()=0;

            virtual ITexture * GetColorTexture()=0;

            virtual ITexture * GetDepthTexture()=0;

            virtual void SetTexture(ITexture * color, ITexture * depth)=0;


        private:

            virtual void AttachTexture()=0;
        };
    }
}

#endif
