#ifndef _DEF_OMEGLOND3D_CFRAMEBUFFERRENDER_HPP
#define _DEF_OMEGLOND3D_CFRAMEBUFFERRENDER_HPP

#include "IFrameBufferRender.hpp"

#include "../Utils/Ptr/SmartPtr.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class CFrameBufferRender : public IFrameBufferRender
        {

        public:

            CFrameBufferRender(const std::string & name, int width, int height);

            virtual ~CFrameBufferRender();

            virtual void Clear()=0;

            virtual void Lock()=0;

            virtual void Unlock()=0;

            virtual void Enable()=0;

            virtual void Disable()=0;

            ITexture * GetColorTexture();

            ITexture * GetDepthTexture();

            void SetTexture(ITexture * color, ITexture * depth);


        protected:

            int _width, _height;

            UTILS::ptr<ITexture>::ResourcePtr _color_texture, _depth_texture;

        private:

            virtual void AttachTexture()=0;
        };
    }
}

#endif
