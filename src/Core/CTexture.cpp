#include "CTexture.hpp"

#include "../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        CTexture::CTexture(const std::string &name, unsigned int bpp, unsigned int width, unsigned int height) : ITexture(name), _bpp(bpp), _width(width), _height(height)
        {
        }

        CTexture::~CTexture()
        {
        }

        unsigned int CTexture::GetBpp() const
        {
            return _bpp;
        }

        unsigned int CTexture::GetWidth() const
        {
            return _width;
        }

        unsigned int CTexture::GetHeight() const
        {
            return _height;
        }
    }
}
