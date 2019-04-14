#ifndef _DEF_OMEGLOND3D_ICUBEMAP_HPP
#define _DEF_OMEGLOND3D_ICUBEMAP_HPP

#include "CResource.hpp"

#include "ECoreEnum.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class CPicture;


        struct CubeMapDeclaration {
            CubeMapOrientation orient;
            std::string name;
        };

        class ICubeMap : public CResource
        {

        public:

            ICubeMap(const std::string &name) : CResource(name) {}

            virtual ~ICubeMap() {}

            virtual unsigned int GetBpp() const=0;

            virtual unsigned int GetWidth() const=0;

            virtual unsigned int GetHeight() const=0;

            virtual void SetTexture(const CubeMapOrientation & orient, const std::string & picture_name) const=0;

            virtual void SetTexture(const CubeMapOrientation &orient, const CPicture &picture) const=0;

            virtual void Enable(unsigned int position=0, const TextureEnvironement &texEnv=OMGL_TEXENV_STANDART) const=0;

            virtual void Disable(unsigned int position=0) const=0;

            virtual void GenerateTexCoord(unsigned int position, const TexCoordPlane *planes, std::size_t size)=0;

            template <std::size_t Size> void GenerateTexCoord(unsigned int position, const TexCoordPlane (&planes)[Size]);
        };

        template <std::size_t Size> void ICubeMap::GenerateTexCoord(unsigned int position, const TexCoordPlane (&planes)[Size])
        {
            GenerateTexCoord(position, planes, Size);
        }
    }
}

#endif
