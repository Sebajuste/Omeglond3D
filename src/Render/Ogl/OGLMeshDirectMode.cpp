#include "OGLMeshDirectMode.hpp"

#include "OGLExtention.hpp"
#include "OGLBufferVertex.hpp"
#include "OGLDeclaration.hpp"

#include "../../Debug/DebugAllocation.hpp"

#include "OGLBlendingParameter.hpp"

#include <map>
#include <GL/gl.h>



namespace OMGL3D
{
    namespace OGL
    {
        struct BufferInfo
        {
            OGLBufferVertex * buffer;
            unsigned int offset;
            unsigned int stride;
            unsigned int size;
            unsigned int type;
        };


        OGLMeshDirectMode::OGLMeshDirectMode(const std::string &name) : CORE::CMesh(name)
        {
        }

        void OGLMeshDirectMode::Draw(const CORE::AlphaTest &alpha) const
        {
            glEnable(GL_ALPHA_TEST);
            glAlphaFunc(BlendingFunc::OGLAlphaMode[alpha.mode], alpha.value);
            Draw();
            glDisable(GL_ALPHA_TEST);
        }

        void OGLMeshDirectMode::Draw(const CORE::BlendingMode &blending) const
        {
            glEnable(GL_BLEND);
            glBlendFunc(BlendingFunc::OGLBlendingMode[blending.mode_source], BlendingFunc::OGLBlendingMode[blending.mode_target]);
            Draw();
            glDisable(GL_BLEND);
        }

        void OGLMeshDirectMode::Draw(const CORE::AlphaTest &alpha, const CORE::BlendingMode &blending) const
        {
            glEnable(GL_ALPHA_TEST);
            glEnable(GL_BLEND);
            glAlphaFunc(BlendingFunc::OGLAlphaMode[alpha.mode], alpha.value);
            glBlendFunc(BlendingFunc::OGLBlendingMode[blending.mode_source], BlendingFunc::OGLBlendingMode[blending.mode_target]);
            Draw();
            glDisable(GL_BLEND);
            glDisable(GL_ALPHA_TEST);
        }

        void OGLMeshDirectMode::Draw() const
        {
            OGLExtention & ext = OGLExtention::GetInstance();
            std::map<CORE::ElementTarget, BufferInfo> buffers_map;

            OGLDeclaration * ogl_dec = static_cast<OGLDeclaration*>( _declaration.GetPtr() );

            std::vector<OGLElement>::iterator it;
            for(it=ogl_dec->_elements.begin(); it!=ogl_dec->_elements.end(); ++it)
            {
                OGLBufferVertex * buffer = dynamic_cast<OGLBufferVertex*>((CORE::IBufferBase*)_vertex_buffers[(*it).channel].GetPtr());

                switch((*it).target)
                {
                    case CORE::OMGL_ELEMENT_TARGET_POSITIONAL:
                    {
                        BufferInfo info;
                        info.buffer = buffer;
                        info.stride = buffer->GetStride();
                        info.offset = (*it).offset;
                        info.size = Size[(*it).type];
                        info.type = Type[(*it).type];


                        buffers_map[CORE::OMGL_ELEMENT_TARGET_POSITIONAL] = info;
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_COLOR:
                    {
                        BufferInfo info;
                        info.buffer = buffer;
                        info.stride = buffer->GetStride();
                        info.offset = (*it).offset;
                        info.size = Size[(*it).type];
                        info.type = Type[(*it).type];


                        buffers_map[CORE::OMGL_ELEMENT_TARGET_COLOR] = info;
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_NORMAL:
                    {
                        BufferInfo info;
                        info.buffer = buffer;
                        info.stride = buffer->GetStride();
                        info.offset = (*it).offset;
                        info.size = Size[(*it).type];
                        info.type = Type[(*it).type];


                        buffers_map[CORE::OMGL_ELEMENT_TARGET_NORMAL] = info;
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD0:
                    {
                        BufferInfo info;
                        info.buffer = buffer;
                        info.stride = buffer->GetStride();
                        info.offset = (*it).offset;
                        info.size = Size[(*it).type];
                        info.type = Type[(*it).type];
                        buffers_map[CORE::OMGL_ELEMENT_TARGET_TEXCOORD0] = info;
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD1:
                    {
                        BufferInfo info;
                        info.buffer = buffer;
                        info.stride = buffer->GetStride();
                        info.offset = (*it).offset;
                        info.size = Size[(*it).type];
                        info.type = Type[(*it).type];
                        buffers_map[CORE::OMGL_ELEMENT_TARGET_TEXCOORD1] = info;
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD2:
                    {
                        BufferInfo info;
                        info.buffer = buffer;
                        info.stride = buffer->GetStride();
                        info.offset = (*it).offset;
                        info.size = Size[(*it).type];
                        info.type = Type[(*it).type];
                        buffers_map[CORE::OMGL_ELEMENT_TARGET_TEXCOORD2] = info;
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD3:
                    {
                        BufferInfo info;
                        info.buffer = buffer;
                        info.stride = buffer->GetStride();
                        info.offset = (*it).offset;
                        info.size = Size[(*it).type];
                        info.type = Type[(*it).type];
                        buffers_map[CORE::OMGL_ELEMENT_TARGET_TEXCOORD3] = info;
                        break;
                    }

                    default:
                        break;
                }
            }


            OGLBufferVertex * index_buffer = dynamic_cast<OGLBufferVertex*>((CORE::IBufferBase*)_index_buffer.GetPtr());

            //GLubyte * indices = (GLubyte*)index_buffer->getBuffer();
            //OGLBuffer * index_buffer = dynamic_cast<OGLBuffer*>((CORE::IBufferBase*)_index_buffer);

            //const GLuint * indices = reinterpret_cast<const GLuint*>(index_buffer->getBuffer());

            unsigned int count_indices = (index_buffer->GetSize()*index_buffer->GetStride()/4);

            glBegin(GL_TRIANGLES);

            for(unsigned int index_indice=0; index_indice<count_indices; ++index_indice)
            {

                unsigned int offset = 0;
                unsigned int stride = 0;

                BufferInfo info_texcoord0 = buffers_map[CORE::OMGL_ELEMENT_TARGET_TEXCOORD0];

                offset = info_texcoord0.offset;
                stride = info_texcoord0.stride;

                switch(info_texcoord0.type)
                {
                    case GL_FLOAT:
                    {
                        const GLfloat * buffer = reinterpret_cast<const GLfloat*>(info_texcoord0.buffer->GetBuffer());

                        if( buffer == 0) break;

                        stride = stride / sizeof(GLfloat);

                        if( ext.MultiTexturing )
                        {
                            switch(info_texcoord0.size)
                            {
                                //case 2: ext.glMultiTexCoord2fARB(0, buffer[indices[index_indice]*stride+offset], buffer[indices[index_indice]*stride+offset+1]); break;
                                //case 3: glTexCoord3f(buffer[indices[index_indice]*stride+offset], buffer[indices[index_indice]*stride+offset+1], buffer[indices[index_indice]*stride+offset+2]); break;
                                default: break;
                            }
                        }
                        else
                        {

                            switch(info_texcoord0.size)
                            {
                                //case 2: glTexCoord2f(buffer[indices[index_indice]*stride+offset], buffer[indices[index_indice]*stride+offset+1]); break;
                                //case 3: glTexCoord3f(buffer[indices[index_indice]*stride+offset], buffer[indices[index_indice]*stride+offset+1], buffer[indices[index_indice]*stride+offset+2]); break;
                                default: break;
                            }
                        }
                    }
                }



                if( ext.MultiTexturing )
                {
                    BufferInfo info_texcoord1 = buffers_map[CORE::OMGL_ELEMENT_TARGET_TEXCOORD1];

                    offset = info_texcoord1.offset;
                    stride = info_texcoord1.stride;

                    switch(info_texcoord1.type)
                    {


                        case GL_FLOAT:
                        {
                            const GLfloat * buffer = reinterpret_cast<const GLfloat*>(info_texcoord1.buffer->GetBuffer());

                            if( buffer == 0) break;

                            stride = stride/sizeof(GLfloat);

                            switch(info_texcoord1.size)
                            {
                                //case 2: ext.glMultiTexCoord2fARB(1, buffer[indices[index_indice]*stride+offset], buffer[indices[index_indice]*stride+offset+1]); break;
                                //case 3: glTexCoord3f(buffer[indices[index_indice]*stride+offset], buffer[indices[index_indice]*stride+offset+1], buffer[indices[index_indice]*stride+offset+2]); break;
                                default: break;
                            }
                        }
                    }
                }



                BufferInfo info_normal = buffers_map[CORE::OMGL_ELEMENT_TARGET_NORMAL];

                offset = info_normal.offset;
                stride = info_normal.stride;

                switch(info_normal.type)
                {
                    case GL_FLOAT:
                    {
                        const GLfloat * buffer = reinterpret_cast<const GLfloat*>(info_normal.buffer->GetBuffer());

                        if( buffer == 0) return;

                        stride = stride / sizeof(GLfloat);

                        switch(info_normal.size)
                        {
                            //case 3: glNormal3f(buffer[indices[index_indice]*stride+offset], buffer[indices[index_indice]*stride+offset+1], buffer[indices[index_indice]*stride+offset+2]); break;
                            default: break;
                        }
                        break;
                    }
                }


                BufferInfo info_positional = buffers_map[CORE::OMGL_ELEMENT_TARGET_POSITIONAL];

                offset = info_positional.offset;
                stride = info_positional.stride;

                switch(info_positional.type)
                {
                    case GL_FLOAT:
                    {
                        const GLfloat * buffer = reinterpret_cast<const GLfloat*>(info_positional.buffer->GetBuffer());

                        if( buffer == 0) return;

                        stride = stride / sizeof(GLfloat);

                        switch(info_positional.size)
                        {
                            //case 2: glVertex2f(buffer[indices[index_indice]*stride+offset], buffer[indices[index_indice]*stride+offset+1]); break;
                            //case 3: glVertex3f(buffer[indices[index_indice]*stride+offset], buffer[indices[index_indice]*stride+offset+1], buffer[indices[index_indice]*stride+offset+2]); break;
                            default: break;
                        }

                        break;
                    }
                }



            }

            glEnd();

        }

        void OGLMeshDirectMode::Update() const
        {
        }
    }
}
