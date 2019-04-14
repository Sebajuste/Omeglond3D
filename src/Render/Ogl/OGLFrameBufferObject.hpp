#ifndef _DEF_OMEGLOND3D_OBJFRAMEBUFFEROBJECT_HPP
#define _DEF_OMEGLOND3D_OBJFRAMEBUFFEROBJECT_HPP

#include "../../Core/CFrameBufferRender.hpp"

#include <GL/gl.h>

namespace OMGL3D
{
    namespace OGL
    {
        class OGLFrameBufferObject : public CORE::CFrameBufferRender
        {

        public:

            OGLFrameBufferObject(const std::string & name, int width, int height);

            ~OGLFrameBufferObject();

            void Clear();

            void Lock();

            void Unlock();

            void Enable();

            void Disable();

            void AttachTexture();


        private:

            GLuint _id;

            GLuint _id_fbo;
            GLuint _id_depth;

            //GLuint _id_texture;
            //CORE::ColorBufferType _texture_type;
        };
    }
}

#endif
