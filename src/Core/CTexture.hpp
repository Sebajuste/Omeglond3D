#ifndef _DEF_OMEGLOND3D_CTEXTURE_HPP
#define _DEF_OMEGLOND3D_CTEXTURE_HPP

#include "ITexture.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class CTexture : public ITexture
        {

        public:

            CTexture(const std::string &name, unsigned int bpp, unsigned int width, unsigned int height);

            virtual ~CTexture();

            unsigned int GetBpp() const;

            unsigned int GetWidth() const;

            unsigned int GetHeight() const;

            virtual void Enable(unsigned int position=0, const TextureEnvironement &texEnv=OMGL_TEXENV_STANDART)const=0;

            virtual void Disable(unsigned int position=0)const=0;

            virtual void SetImage(const CPicture & images, bool mipmap=true)=0;

            virtual void SetImage(const CPicture * images, std::size_t size)=0;


        protected:

            virtual void GenerateTexCoord(unsigned int position, const TexCoordPlane *planes, std::size_t size)=0;

            unsigned int _bpp, _width, _height;
        };
    }
}

#endif
