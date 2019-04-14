#include "OGL3CubeMap.hpp"

//#define GL3_PROTOTYPES 1

//#include <GL3/gl3.h>
//#include <GL/glu.h>

#include "../../Core/CPicture.hpp"

#include "../../Utils/Logger/ILogger.hpp"

#include "OGL3Extention.hpp"

namespace OMGL3D
{
    namespace OGL3
    {
        /*
        GLenum TexcoordGenType[] = {
            GL_OBJECT_LINEAR,
            GL_EYE_LINEAR,
            GL_SPHERE_MAP
        };
        */

        GLenum OGLCubeMapOrientation[] = {
            GL_TEXTURE_CUBE_MAP_POSITIVE_X,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
        };

        OGL3CubeMap::OGL3CubeMap(const std::string & name) : CORE::CCubeMap(name)
        {
            glGenTextures(1, &_id_name);
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "CubeMap create | id =" << _id_name << UTILS::OMGL_LOGGER_FLUSH;;
        }

        OGL3CubeMap::~OGL3CubeMap()
        {
            glDeleteTextures(1, &_id_name);
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "CubeMap delete | id =" << _id_name << UTILS::OMGL_LOGGER_FLUSH;;
        }

        void OGL3CubeMap::SetTexture(const CORE::CubeMapOrientation & orient, const CORE::CPicture & picture) const
        {
            //glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, _id_name);
            glBindTexture(GL_TEXTURE_CUBE_MAP, _id_name);

            switch(picture.GetBpp())
            {
                case 24:
                    glTexImage2D(OGLCubeMapOrientation[orient], 0, 3, picture.GetWidth(), picture.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, picture.GetDatas());
                    //gluBuild2DMipmaps(OGLCubeMapOrientation[orient], GL_RGB, picture.GetWidth(), picture.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, picture.GetDatas());
                    break;

                case 32:
                    glTexImage2D(OGLCubeMapOrientation[orient], 0, 4, picture.GetWidth(), picture.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, picture.GetDatas());
                    //gluBuild2DMipmaps(OGLCubeMapOrientation[orient], GL_RGBA, picture.GetWidth(), picture.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, picture.GetDatas());
                    break;
            }

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
            //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);

            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Texture] id =" << _id_name << " | image set " << picture.GetName() << UTILS::OMGL_LOGGER_FLUSH;;


            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }

        void OGL3CubeMap::Enable(unsigned int position, const CORE::TextureEnvironement &texEnv) const
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();

            if( position < 8)
            {
                GLenum enum_texture = GL_TEXTURE0;
                enum_texture += position;
                ext.glActiveTexture(enum_texture);
                glEnable(GL_TEXTURE_CUBE_MAP);

                switch(texEnv)
                {
                    case CORE::OMGL_TEXENV_STANDART:
                    {
                        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                        break;
                    }

                    case CORE::OMGL_TEXENV_SPLATTING:
                    {
                        //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
                        break;
                    }
                }
            }

            glBindTexture(GL_TEXTURE_CUBE_MAP, _id_name);

            /*
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
                }
            }
            */
        }

        void OGL3CubeMap::Disable(unsigned int position) const
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();

            if( position < 8)
            {
                GLenum enum_texture = GL_TEXTURE0;
                enum_texture += position;
                ext.glActiveTexture(enum_texture);
            }

            /*
            glDisable(GL_TEXTURE_GEN_S);
            glDisable(GL_TEXTURE_GEN_T);
            glDisable(GL_TEXTURE_GEN_R);
            glDisable(GL_TEXTURE_GEN_Q);
            */

            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
            glDisable(GL_TEXTURE_CUBE_MAP);
        }

        void OGL3CubeMap::GenerateTexCoord(unsigned int position, const CORE::TexCoordPlane *planes, std::size_t size)
        {
            _texgenmap[position] = size;

            Enable(position);
            /*
            for(unsigned int index=0; index<size; ++index)
            {
                GLenum texGen = 0;
                GLenum canal = 0;

                switch(index)
                {
                    case 0:
                        texGen = GL_TEXTURE_GEN_S;
                        canal = GL_S;
                        break;

                    case 1:
                        texGen = GL_TEXTURE_GEN_T;
                        canal = GL_T;
                        break;

                    case 2:
                        texGen = GL_TEXTURE_GEN_R;
                        canal = GL_R;
                        break;

                    case 3:
                        texGen = GL_TEXTURE_GEN_Q;
                        canal = GL_Q;
                        break;

                    default:
                        break;
                }

                glEnable(texGen);
                glTexGeni(canal, GL_TEXTURE_GEN_MODE, TexcoordGenType[planes[index].type]);
                glTexGenfv(canal, GL_OBJECT_PLANE, &planes[index].x);
                glDisable(texGen);
            }
            */

            Disable(position);
        }
    }
}
