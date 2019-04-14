#include "OGL3FrameBufferObject.hpp"

#include "OGL3Extention.hpp"
#include "OGL3Texture.hpp"

#include "../../Utils/Logger/ILogger.hpp"

using namespace std;

namespace OMGL3D
{
    namespace OGL3
    {
        OGL3FrameBufferObject::OGL3FrameBufferObject(const std::string & name, int width, int height) : CORE::CFrameBufferRender(name, width, height)
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            ext.glGenFramebuffers(1, &_id_fbo);
            ext.glBindFramebuffer(GL_FRAMEBUFFER_EXT, _id_fbo);

            ext.glGenRenderbuffers(1, &_id_depth);
            ext.glBindRenderbuffer(GL_RENDERBUFFER_EXT, _id_depth);
            ext.glRenderbufferStorage(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, width, height);
            ext.glBindRenderbuffer(GL_RENDERBUFFER_EXT, 0);
            ext.glFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _id_depth);

            ext.glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);

            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "Frame Buffer Object created: id = " << _id_fbo << "  id_depth = " << _id_depth << UTILS::OMGL_LOGGER_FLUSH;

        }

        OGL3FrameBufferObject::~OGL3FrameBufferObject()
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            ext.glDeleteFramebuffers(1, &_id_fbo);
            ext.glDeleteRenderbuffers(1, &_id_depth);
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "Frame Buffer Object deleted: id = " << _id_fbo << "  id_depth = " << _id_depth << UTILS::OMGL_LOGGER_FLUSH;
        }

        void OGL3FrameBufferObject::Clear()
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            ext.glBindFramebuffer(GL_FRAMEBUFFER_EXT, _id_fbo);
            ext.glBindRenderbuffer(GL_RENDERBUFFER_EXT, _id_depth);
            glClear(GL_DEPTH_BUFFER_BIT);
            //glClearDepth(10.0f);
            ext.glBindRenderbuffer(GL_RENDERBUFFER_EXT, 0);
            ext.glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
        }

        void OGL3FrameBufferObject::Lock()
        {
        }

        void OGL3FrameBufferObject::Unlock()
        {
        }

        void OGL3FrameBufferObject::Enable()
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            ext.glBindFramebuffer(GL_FRAMEBUFFER_EXT, _id_fbo);
            glPushAttrib(GL_VIEWPORT_BIT);
            glViewport(0, 0, _width, _height);

            glPolygonOffset(0.8f, 2.0f);
            glEnable(GL_POLYGON_OFFSET_FILL);
        }

        void OGL3FrameBufferObject::Disable()
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();


            glPopAttrib();

            ext.glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
            glDisable(GL_POLYGON_OFFSET_FILL);
        }

        void OGL3FrameBufferObject::AttachTexture()
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            OGL3Texture * ogl_colortexture = dynamic_cast<OGL3Texture*>( _color_texture.GetPtr() );
            OGL3Texture * ogl_depthtexture = dynamic_cast<OGL3Texture*>( _depth_texture.GetPtr() );

            ext.glBindFramebuffer(GL_FRAMEBUFFER_EXT, _id_fbo);


            ext.glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, ogl_colortexture->GetId(), 0);
            ext.glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, ogl_depthtexture->GetId(), 0);

            glBindTexture(GL_TEXTURE_2D, ogl_depthtexture->GetId());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
            glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);
            glBindTexture(GL_TEXTURE_2D, 0);


            GLenum status = ext.glCheckFramebufferStatus(GL_FRAMEBUFFER_EXT);


            switch (status)
            {
                case GL_FRAMEBUFFER_COMPLETE_EXT:
                    //UTILS::ILogger::getLogger(UTILS::OMGL_LOGGER_RENDERER) << "[FBO] " << _id << " ready to be rendered" << UTILS::OMGL_LOGGER_FLUSH;
                    break;

                case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
                    UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[FBO] " << _id << " Wrong texture format" << UTILS::OMGL_LOGGER_FLUSH;
                    break;

                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
                    UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[FBO] " << _id << " Incomplete attachment" << UTILS::OMGL_LOGGER_FLUSH;
                    break;

                case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
                    UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[FBO] " << _id << " Dimensions are wrong" << UTILS::OMGL_LOGGER_FLUSH;
                    break;

                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
                    UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[FBO] " << _id << " No image is attached" << UTILS::OMGL_LOGGER_FLUSH;
                    break;

                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
                    UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[FBO] " << _id << " Incomplete buffer" << UTILS::OMGL_LOGGER_FLUSH;
                    break;

                case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
                    UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[FBO] " << _id << " Formats incompleted" << UTILS::OMGL_LOGGER_FLUSH;
                    break;

                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
                    UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[FBO] " << _id << " Draw buffer incompleted" << UTILS::OMGL_LOGGER_FLUSH;
                    break;

                default :
                    //UTILS::ILogger::getLogger(UTILS::OMGL_LOGGER_RENDERER) << "[FBO] " << _id << " ready to be rendered" << UTILS::OMGL_LOGGER_FLUSH;
                    break;
            }

            ext.glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
        }
    }
}
