#ifndef _DEF_OMEGLOND3D_OGL3TEXTURE_HPP
#define _DEF_OMEGLOND3D_OGL3TEXTURE_HPP

#include <string>
#include <map>
#include <GL/gl.h>

#include "../../Core/CTexture.hpp"

namespace OMGL3D
{
    namespace CORE {
        class Picture;
    }

    namespace OGL3
    {
        class OGL3Texture : public CORE::CTexture
        {

        public:

            OGL3Texture(const std::string &name, unsigned int bpp, unsigned int width, unsigned int height);

            ~OGL3Texture();

            void Enable(unsigned int position, const CORE::TextureEnvironement &texEnv=CORE::OMGL_TEXENV_STANDART) const;

            void Disable(unsigned int position) const;

            void SetEmptyImage(const CORE::ColorBufferType & type, bool mipmap=true);

            void SetImage(const CORE::CPicture & images, bool mipmap=true);

            void SetImage(const CORE::CPicture * images, std::size_t size);

            void GenerateTexCoord(unsigned int position, const CORE::TexCoordPlane *planes, std::size_t size);

            GLuint GetId() const;

            CORE::ColorBufferType GetType() const;


        private:

            GLuint _id_name;
            CORE::ColorBufferType _type;

            typedef std::map<unsigned int, std::size_t> TexGenMap;
            TexGenMap _texgenmap;
        };
    }
}

#endif

