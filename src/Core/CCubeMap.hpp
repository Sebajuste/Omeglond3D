#ifndef _DEF_OMEGLOND3D_CCUBEMAP_HPP
#define _DEF_OMEGLOND3D_CCUBEMAP_HPP

#include "ICubeMap.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class CCubeMap : public ICubeMap
        {

        public:
            CCubeMap(const std::string &name);

            virtual ~CCubeMap();

            unsigned int GetBpp() const;

            unsigned int GetWidth() const;

            unsigned int GetHeight() const;

            void SetTexture(const CubeMapOrientation & orient, const std::string & picture_name) const;

            virtual void SetTexture(const CubeMapOrientation &orient, const CPicture &picture) const=0;

            virtual void Enable(unsigned int position=0, const TextureEnvironement &texEnv=OMGL_TEXENV_STANDART) const=0;

            virtual void Disable(unsigned int position=0) const=0;

            virtual void GenerateTexCoord(unsigned int position, const TexCoordPlane *planes, std::size_t size)=0;


        private:

            unsigned int _bpp, _width, _height;
        };
    }
}

#endif
