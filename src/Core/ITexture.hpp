#ifndef _DEF_OMEGLOND3D_ITEXTURE_HPP
#define _DEF_OMEGLOND3D_ITEXTURE_HPP

#include "CResource.hpp"

#include "ECoreEnum.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class CPicture;

        class ITexture : public CResource
        {

        public:

            ITexture(const std::string &name) : CResource(name) { }

            virtual ~ITexture() {}

            virtual unsigned int GetBpp() const=0;

            virtual unsigned int GetWidth() const=0;

            virtual unsigned int GetHeight() const=0;

            virtual void Enable(unsigned int position=0, const TextureEnvironement &texEnv=OMGL_TEXENV_STANDART) const=0;

            virtual void Disable(unsigned int position=0) const=0;

            virtual void SetImage(const CPicture & image, bool mipmap=true)=0;

            virtual void SetImage(const CPicture * images, std::size_t size)=0;

            template <std::size_t Size> void GenerateTexCoord(unsigned int position, const TexCoordPlane(&p)[Size]);

            virtual void GenerateTexCoord(unsigned int position, const TexCoordPlane *planes, std::size_t size)=0;
        };

        template <std::size_t Size> void ITexture::GenerateTexCoord(unsigned int position, const TexCoordPlane(&p)[Size])
        {
            GenerateTexCoord(position, p, Size);
        }
    }
}

#endif
