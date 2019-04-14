#ifndef _DEF_OMEGLOND3D_OGLCUBEMAP_HPP
#define _DEF_OMEGLOND3D_OGLCUBEMAP_HPP

#include "../../Core/CCubeMap.hpp"

#include <map>
#include <GL/gl.h>

namespace OMGL3D
{
    namespace OGL
    {
        class OGLCubeMap : public CORE::CCubeMap
        {

        public:

            OGLCubeMap(const std::string &name);

            ~OGLCubeMap();

            void SetTexture(const CORE::CubeMapOrientation &orient, const CORE::CPicture &picture) const;

            void Enable(unsigned int position=0, const CORE::TextureEnvironement &texEnv=CORE::OMGL_TEXENV_STANDART) const;

            void Disable(unsigned int position=0) const;

            void GenerateTexCoord(unsigned int position, const CORE::TexCoordPlane *planes, std::size_t size);


        private:

            GLuint _id_name;

            typedef std::map<unsigned int, unsigned int> TexGenMap;
            TexGenMap _texgenmap;
        };
    }
}

#endif
