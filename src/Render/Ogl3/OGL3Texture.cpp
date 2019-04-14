#include "OGL3Texture.hpp"

#define GL3_PROTOTYPES 1

#include <GL3/gl3.h>
//#include <GL/glu.h>

#include "OGL3Extention.hpp"

#include "../../Core/CPicture.hpp"

#include "../../Exception/RenderException.hpp"

#include "../../Debug/DebugAllocation.hpp"

#include "../../Utils/Logger/ILogger.hpp"

namespace OMGL3D
{
    namespace OGL3
    {

        const static unsigned int OMGL_MAX_TEXTURE = 8;

        GLenum TexCoordGenType[] = {
            GL_OBJECT_LINEAR,
            GL_EYE_LINEAR,
            GL_SPHERE_MAP
        };

        OGL3Texture::OGL3Texture(const std::string &name, unsigned int bpp, unsigned int width, unsigned int height) : CORE::CTexture(name, bpp, width, height), _id_name(0), _type(CORE::OMGL_COLOR_BUFFER_RGB)
        {
            glEnable(GL_TEXTURE_2D);
            glGenTextures (1, &_id_name);
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Texture] created | id =" << _id_name << UTILS::OMGL_LOGGER_FLUSH;
        }

        OGL3Texture::~OGL3Texture()
        {
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Texture] deleted | id =" << _id_name << UTILS::OMGL_LOGGER_FLUSH;
            glDeleteTextures(1, &_id_name);
        }

        void OGL3Texture::Enable(unsigned int position, const CORE::TextureEnvironement &texEnv) const
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();

            if( position < OMGL_MAX_TEXTURE)
            {
                GLenum enum_texture = GL_TEXTURE0;
                enum_texture += position;
                ext.glActiveTexture(enum_texture);
                glEnable(GL_TEXTURE_2D);

                switch(texEnv)
                {
                    case CORE::OMGL_TEXENV_STANDART:
                    {
                        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                        break;
                    }

                    case CORE::OMGL_TEXENV_SPLATTING:
                    {
                        //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
                        break;
                    }
                }
            }

            glBindTexture(GL_TEXTURE_2D, _id_name);

            TexGenMap::const_iterator it;
            it = _texgenmap.find(position);
            if( it != _texgenmap.end() )
            {
                switch(it->second)
                {
                    case 4:
                        glEnable(GL_TEXTURE_GEN_Q);
                    case 3:
                        glEnable(GL_TEXTURE_GEN_R);
                    case 2:
                        glEnable(GL_TEXTURE_GEN_T);
                    case 1:
                        glEnable(GL_TEXTURE_GEN_S);
                    default:
                        break;
                }
            }

        }

        void OGL3Texture::Disable(unsigned int position) const
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();

            if( position < OMGL_MAX_TEXTURE)
            {
                GLenum enum_texture = GL_TEXTURE0;
                enum_texture += position;
                ext.glActiveTexture(enum_texture);
            }

            glDisable(GL_TEXTURE_GEN_S);
            glDisable(GL_TEXTURE_GEN_T);
            glDisable(GL_TEXTURE_GEN_R);
            glDisable(GL_TEXTURE_GEN_Q);

            glDisable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void OGL3Texture::SetEmptyImage(const CORE::ColorBufferType & type, bool mipmap)
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();

            static const GLuint glColorSize[] = { GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT24 };
            static const GLuint glColorType[] = { GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT };
            static const GLuint glType[] = { GL_UNSIGNED_BYTE, GL_UNSIGNED_BYTE, GL_FLOAT };

            _type = type;

            glBindTexture(GL_TEXTURE_2D, _id_name);
            glTexImage2D(GL_TEXTURE_2D, 0, glColorSize[type], _width, _height, 0, glColorType[type], glType[type], NULL);
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            switch(type)
            {
                case CORE::OMGL_COLOR_BUFFER_DEPTH:
                    //glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);
                    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB );
                    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL );
                    break;

                default:
                    break;
            }

            if( mipmap == true)
            {
                //OGLExtention::GetInstance().glGenerateMipmap(GL_TEXTURE_2D);
                ext.glGenerateMipmap(GL_TEXTURE_2D);
            }
        }

        void OGL3Texture::SetImage(const CORE::CPicture & image, bool mipmap)
        {
            glBindTexture(GL_TEXTURE_2D, _id_name);
            //glEnable(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

            if( mipmap == true)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

                switch(image.GetBpp())
                {
                    case 24:
                        _type = CORE::OMGL_COLOR_BUFFER_RGB;
                        //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(),GL_RGB, GL_UNSIGNED_BYTE, image.GetDatas());
                        break;

                    case 32:
                        _type = CORE::OMGL_COLOR_BUFFER_RGBA;
                        //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.GetWidth(), image.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, image.GetDatas());
                        break;
                }
            }
            else
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

                switch(image.GetBpp())
                {
                    case 24:
                        _type = CORE::OMGL_COLOR_BUFFER_RGB;
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.GetWidth(), image.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.GetDatas());
                        break;

                    case 32:
                        _type = CORE::OMGL_COLOR_BUFFER_RGBA;
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetDatas());
                        break;
                }
            }

            glBindTexture(GL_TEXTURE_2D, 0);

            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Texture] id =" << _id_name << " | image set " << image.GetName() << UTILS::OMGL_LOGGER_FLUSH;;
        }

        void OGL3Texture::SetImage(const CORE::CPicture * images, std::size_t size)
        {
            if( size == 0 ) {
                throw EXCP::RenderException("No mipmap");
            }

            glBindTexture(GL_TEXTURE_2D, _id_name);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


            for(unsigned int index=0; index<size; ++index)
            {
                switch(images[index].GetBpp())
                {
                    case 24:
                        _type = CORE::OMGL_COLOR_BUFFER_RGB;
                        glTexImage2D(GL_TEXTURE_2D, index, GL_RGB, images[index].GetWidth(), images[index].GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, images[index].GetDatas());
                        break;

                    case 32:
                        _type = CORE::OMGL_COLOR_BUFFER_RGBA;
                        glTexImage2D(GL_TEXTURE_2D, index, GL_RGBA, images[index].GetWidth(), images[index].GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, images[index].GetDatas());
                        break;
                }

                UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Texture] id =" << _id_name << " | images set " << images[index].GetName() << UTILS::OMGL_LOGGER_FLUSH;;
            }

            glBindTexture(GL_TEXTURE_2D, 0);


        }

        void OGL3Texture::GenerateTexCoord(unsigned int position, const CORE::TexCoordPlane *planes, std::size_t size)
        {
            static const GLenum TexGen[] = {GL_TEXTURE_GEN_S, GL_TEXTURE_GEN_T, GL_TEXTURE_GEN_R, GL_TEXTURE_GEN_Q};
            static const GLenum Canal[] = {GL_S, GL_T, GL_R, GL_Q};

            _texgenmap[position] = size;

            Enable(position);
            for(unsigned int index=0; index<size; ++index)
            {
                glEnable(TexGen[index]);
                glTexGeni(Canal[index], GL_TEXTURE_GEN_MODE, TexCoordGenType[planes[index].type]);
                glTexGenfv(Canal[index], GL_OBJECT_PLANE, &planes[index].x);
                glDisable(TexGen[index]);
            }

            Disable(position);

        }

        GLuint OGL3Texture::GetId() const
        {
            return _id_name;
        }

        CORE::ColorBufferType OGL3Texture::GetType() const
        {
            return _type;
        }
    }
}

