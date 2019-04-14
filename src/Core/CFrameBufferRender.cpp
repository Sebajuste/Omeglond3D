#include "CFrameBufferRender.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        CFrameBufferRender::CFrameBufferRender(const std::string & name, int width, int height) : IFrameBufferRender(name), _width(width), _height(height)
        {
        }

        CFrameBufferRender::~CFrameBufferRender()
        {
        }

        ITexture * CFrameBufferRender::GetColorTexture()
        {
            return _color_texture;
        }

        ITexture * CFrameBufferRender::GetDepthTexture()
        {
            return _depth_texture;
        }

        void CFrameBufferRender::SetTexture(ITexture * color, ITexture * depth)
        {
            _color_texture = color;
            _depth_texture = depth;
            this->AttachTexture();
        }
    }
}
