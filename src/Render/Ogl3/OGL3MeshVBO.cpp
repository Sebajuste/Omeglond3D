#include "OGL3MeshVBO.hpp"

#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#include "OGL3BlendingParameter.hpp"
#include "OGL3BufferVertexObject.hpp"
#include "OGL3Declaration.hpp"
#include "OGL3Extention.hpp"
#include "OGL3MatrixManager.hpp"
#include "OGL3ShaderManager.hpp"

#include "../../Math/Matrix4.hpp"

#include "../../Debug/DebugAllocation.hpp"

#include "../../Utils/Logger/ILogger.hpp"

#include <iostream>

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

namespace OMGL3D
{
    namespace OGL3
    {
        GLenum OGLMeshType[] = {
            GL_POINTS,
            GL_LINES,
            GL_TRIANGLES
        };


        OGL3MeshVBO::OGL3MeshVBO(const std::string &name) : CORE::CMesh(name)
        {
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "Create Mesh VBO " << name << UTILS::OMGL_LOGGER_FLUSH;
        }

        OGL3MeshVBO::~OGL3MeshVBO()
        {
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "Delete Mesh VBO " << UTILS::OMGL_LOGGER_FLUSH;
        }

        void OGL3MeshVBO::Draw(const CORE::AlphaTest &alpha) const
        {
            //glEnable(GL_ALPHA_TEST);
            //glAlphaFunc(BlendingFunc::OGLAlphaMode[alpha.mode], alpha.value);
            Draw();
            //glDisable(GL_ALPHA_TEST);
        }

        void OGL3MeshVBO::Draw(const CORE::BlendingMode &blending) const
        {
            glEnable(GL_BLEND);
            glBlendFunc(BlendingFunc::OGLBlendingMode[blending.mode_source], BlendingFunc::OGLBlendingMode[blending.mode_target]);
            Draw();
            glDisable(GL_BLEND);
        }

        void OGL3MeshVBO::Draw(const CORE::AlphaTest &alpha, const CORE::BlendingMode &blending) const
        {
            //glEnable(GL_ALPHA_TEST);
            glEnable(GL_BLEND);
            //glAlphaFunc(BlendingFunc::OGLAlphaMode[alpha.mode], alpha.value);
            glBlendFunc(BlendingFunc::OGLBlendingMode[blending.mode_source], BlendingFunc::OGLBlendingMode[blending.mode_target]);
            Draw();
            glDisable(GL_BLEND);
            //glDisable(GL_ALPHA_TEST);
        }

        void OGL3MeshVBO::Draw() const
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();

            OGL3ShaderManager & shader_manager = OGL3ShaderManager::GetInstance();


            OGL3IndexBufferObject * index_buffer = dynamic_cast<OGL3IndexBufferObject*>((CORE::IBufferBase*)_index_buffer);
            //OGLBufferVertexObject<GL_ELEMENT_ARRAY_BUFFER_ARB> * index_buffer = dynamic_cast<OGLBufferVertexObject<GL_ELEMENT_ARRAY_BUFFER_ARB> *>((CORE::IBufferBase*)_index_buffer);

            OGL3Declaration * ogl_dec = dynamic_cast<OGL3Declaration*>( (CORE::IDeclaration *)_declaration);

//std::cout << "debug OGLMeshVertexBufferObject::draw() " << ogl_dec->_elements.size() << std::endl;

            //int id_shader = 0;

            MATH::Matrix4f worldViewProjectionMatrix = OGL3MatrixManager::GetInstance().GetMatrix(OMGL3D::CORE::OMGL_MATRIX_PROJECTION)
                                                       * OGL3MatrixManager::GetInstance().GetMatrix(OMGL3D::CORE::OMGL_MATRIX_VIEW).GetInverse()
                                                       * OGL3MatrixManager::GetInstance().GetMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);
            GLuint matrixID = shader_manager.GetUniform(OMGL_OGL3_UNIFORM_MODELVIEWPROJECTION_MATRIX);

            ext.glUniformMatrix4fv(matrixID, 1, GL_FALSE, worldViewProjectionMatrix());



            std::vector<OGL3Element>::iterator it;
            for(it=ogl_dec->_elements.begin(); it!=ogl_dec->_elements.end(); ++it)
            {
                OGL3VertexBufferObject * vertex_buffer = dynamic_cast<OGL3VertexBufferObject*>((CORE::IBufferBase*)_vertex_buffers[(*it).channel]);

                //const unsigned char * buffer = vertex_buffer->getBuffer();
                ext.glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->GetId());

                unsigned int offset = (*it).offset;
                unsigned int stride = vertex_buffer->GetStride();


                switch((*it).target)
                {
                    case CORE::OMGL_ELEMENT_TARGET_POSITIONAL:
                    {
                        GLuint id_shader = shader_manager.GetAttrib(OMGL_OGL3_ATTRIB_VERTEX_POSITION);

                        ext.glEnableVertexAttribArray(id_shader);
                        ext.glVertexAttribPointer(id_shader, Size[(*it).type], Type[(*it).type], GL_FALSE, stride, BUFFER_OFFSET(offset)) ;

                        //glEnableClientState(GL_VERTEX_ARRAY);
                        //glVertexPointer(Size[(*it).type], Type[(*it).type], stride, BUFFER_OFFSET(offset));
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_COLOR:
                    {
                        GLuint id_shader = shader_manager.GetAttrib(OMGL_OGL3_ATTRIB_VERTEX_COLOR);

                        ext.glEnableVertexAttribArray(id_shader);
                        ext.glVertexAttribPointer(id_shader, Size[(*it).type], Type[(*it).type], GL_FALSE, stride, BUFFER_OFFSET(offset)) ;

                        //glEnableClientState(GL_COLOR_ARRAY);
                        //glColorPointer(Size[(*it).type], Type[(*it).type], stride, BUFFER_OFFSET(offset));
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_NORMAL:
                    {
                        GLuint id_shader = shader_manager.GetAttrib(OMGL_OGL3_ATTRIB_VERTEX_NORMAL);

                        ext.glEnableVertexAttribArray(id_shader);
                        ext.glVertexAttribPointer(id_shader, Size[(*it).type], Type[(*it).type], GL_FALSE, stride, BUFFER_OFFSET(offset)) ;
                        //glEnableClientState(GL_NORMAL_ARRAY);
                        //glNormalPointer(Type[(*it).type], stride, BUFFER_OFFSET(offset));
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD0:
                    {
                        GLuint id_shader = shader_manager.GetAttrib(OMGL_OGL3_ATTRIB_VERTEX_TEX_COORD);

                        ext.glEnableVertexAttribArray(id_shader);
                        ext.glVertexAttribPointer(id_shader, Size[(*it).type], Type[(*it).type], GL_FALSE, stride, BUFFER_OFFSET(offset)) ;

                        //if( ext.MultiTexturing )
                        {
                            //ext.glActiveTextureARB(GL_TEXTURE0_ARB);
                            //ext.glClientActiveTextureARB(GL_TEXTURE0_ARB);
                        }
                        //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        //glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, BUFFER_OFFSET(offset));
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD1:
                    {
                        //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        //if( ext.MultiTexturing )
                        {
                            //ext.glActiveTextureARB(GL_TEXTURE1_ARB);
                            //ext.glClientActiveTextureARB(GL_TEXTURE1_ARB);
                            //glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, BUFFER_OFFSET(offset));
                        }
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD2:
                    {
                        //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        //if( ext.MultiTexturing )
                        {
                            //ext.glActiveTextureARB(GL_TEXTURE2_ARB);
                            //ext.glClientActiveTextureARB(GL_TEXTURE2_ARB);
                            //glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, BUFFER_OFFSET(offset));
                        }
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD3:
                    {
                        //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        //if( ext.MultiTexturing )
                        {
                            //ext.glActiveTextureARB(GL_TEXTURE3_ARB);
                            //ext.glClientActiveTextureARB(GL_TEXTURE3_ARB);
                            //glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, BUFFER_OFFSET(offset));
                        }
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD4:
                    {
                        //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        //if( ext.MultiTexturing )
                        {
                            //ext.glActiveTextureARB(GL_TEXTURE4_ARB);
                            //ext.glClientActiveTextureARB(GL_TEXTURE4_ARB);
                            //glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, BUFFER_OFFSET(offset));
                        }
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD5:
                    {
                        //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        //if( ext.MultiTexturing )
                        {
                            //ext.glActiveTextureARB(GL_TEXTURE5_ARB);
                            //ext.glClientActiveTextureARB(GL_TEXTURE5_ARB);
                            //glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, BUFFER_OFFSET(offset));
                        }
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD6:
                    {
                        //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        //if( ext.MultiTexturing )
                        {
                            //ext.glActiveTextureARB(GL_TEXTURE6_ARB);
                            //ext.glClientActiveTextureARB(GL_TEXTURE6_ARB);
                            //glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, BUFFER_OFFSET(offset));
                        }
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD7:
                    {
                        //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        //if( ext.MultiTexturing )
                        {
                            //ext.glActiveTextureARB(GL_TEXTURE7_ARB);
                            //ext.glClientActiveTextureARB(GL_TEXTURE7_ARB);
                            //glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, BUFFER_OFFSET(offset));
                        }
                        break;
                    }

                    default:
                        break;
                }
            }


            //const GLuint * indices = (GLuint*)index_buffer->getBuffer();
            //const GLushort * indices = (GLushort*)index_buffer->getBuffer();
            unsigned int count = (index_buffer->GetSize()*index_buffer->GetStride()/sizeof(GLushort));

            //glEnableClientState(GL_INDEX_ARRAY);

            ext.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->GetId());



            glDrawElements(OGLMeshType[_type], count, GL_UNSIGNED_SHORT, 0);


            // Désactivation de tous les shaders

            //std::vector<OGL3Element>::iterator it;
            for(it=ogl_dec->_elements.begin(); it!=ogl_dec->_elements.end(); ++it)
            {
                switch((*it).target)
                {
                    case CORE::OMGL_ELEMENT_TARGET_POSITIONAL:
                    {
                        GLuint id_shader = shader_manager.GetAttrib(OMGL_OGL3_ATTRIB_VERTEX_POSITION);
                        ext.glDisableVertexAttribArray(id_shader);
                    }
                    break;

                    case CORE::OMGL_ELEMENT_TARGET_COLOR:
                    {
                        GLuint id_shader = shader_manager.GetAttrib(OMGL_OGL3_ATTRIB_VERTEX_COLOR);
                        ext.glDisableVertexAttribArray(id_shader);
                    }
                    break;

                    case CORE::OMGL_ELEMENT_TARGET_NORMAL:
                    {
                        GLuint id_shader = shader_manager.GetAttrib(OMGL_OGL3_ATTRIB_VERTEX_NORMAL);
                        ext.glDisableVertexAttribArray(id_shader);
                    }
                    break;

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD0:
                    {
                        GLuint id_shader = shader_manager.GetAttrib(OMGL_OGL3_ATTRIB_VERTEX_TEX_COORD);
                        ext.glDisableVertexAttribArray(id_shader);
                    }
                    break;

                    default: break;
                }
            }




            ext.glBindBuffer(GL_ARRAY_BUFFER, 0);
            ext.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

/*
            glDisableClientState(GL_INDEX_ARRAY);

            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);

            ext.glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
            ext.glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);

            //std::cout << "debug OGLMeshVertexBufferObject::draw()" << std::endl;

            for (int i = 0; i < 8; ++i)
            {
                ext.glActiveTextureARB(GL_TEXTURE0_ARB + i);
                glDisable(GL_TEXTURE_2D);
            }
            */
        }

        void OGL3MeshVBO::Update() const
        {
        }
    }
}
