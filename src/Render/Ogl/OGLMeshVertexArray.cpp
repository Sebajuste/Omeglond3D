#include "OGLMeshVertexArray.hpp"

#include <GL/gl.h>

#include "OGLExtention.hpp"
#include "OGLDeclaration.hpp"
#include "OGLBufferVertex.hpp"
#include "OGLBlendingParameter.hpp"

#include "../../Utils/Logger/ILogger.hpp"

#include "../../Debug/DebugAllocation.hpp"

//#include <iostream>

namespace OMGL3D
{
    namespace OGL
    {

        OGLMeshVertexArray::OGLMeshVertexArray(const std::string &name) : CMesh(name)
        {
        }

        void OGLMeshVertexArray::Draw(const CORE::AlphaTest &alpha) const
        {
            glEnable(GL_ALPHA_TEST);
            glAlphaFunc(BlendingFunc::OGLAlphaMode[alpha.mode], alpha.value);
            Draw();
            glDisable(GL_ALPHA_TEST);
        }

        void OGLMeshVertexArray::Draw(const CORE::BlendingMode &blending) const
        {
            glEnable(GL_BLEND);
            glBlendFunc(BlendingFunc::OGLBlendingMode[blending.mode_source], BlendingFunc::OGLBlendingMode[blending.mode_target]);
            Draw();
            glDisable(GL_BLEND);
        }

        void OGLMeshVertexArray::Draw(const CORE::AlphaTest &alpha, const CORE::BlendingMode &blending) const
        {
            glEnable(GL_ALPHA_TEST);
            glEnable(GL_BLEND);
            glAlphaFunc(BlendingFunc::OGLAlphaMode[alpha.mode], alpha.value);
            glBlendFunc(BlendingFunc::OGLBlendingMode[blending.mode_source], BlendingFunc::OGLBlendingMode[blending.mode_target]);
            Draw();
            glDisable(GL_BLEND);
            glDisable(GL_ALPHA_TEST);
        }

        void OGLMeshVertexArray::Draw() const
        {
            OGLExtention & ext = OGLExtention::GetInstance();


            OGLBufferVertex * index_buffer = dynamic_cast<OGLBufferVertex*>((CORE::IBufferBase*)_index_buffer);

            OGLDeclaration * ogl_dec = static_cast<OGLDeclaration*>( (CORE::IDeclaration *)_declaration);



            std::vector<OGLElement>::iterator it;
            for(it=ogl_dec->_elements.begin(); it!=ogl_dec->_elements.end(); ++it)
            {
                OGLBufferVertex * vertex_buffer = dynamic_cast<OGLBufferVertex*>((CORE::IBufferBase*)_vertex_buffers[(*it).channel]);
                //

                const unsigned char * buffer = vertex_buffer->GetBuffer();

                unsigned int offset = (*it).offset;
                unsigned int stride = vertex_buffer->GetStride();

                switch((*it).target)
                {
                    case CORE::OMGL_ELEMENT_TARGET_POSITIONAL:
                    {
                        glEnableClientState(GL_VERTEX_ARRAY);
                        glVertexPointer(Size[(*it).type], Type[(*it).type], stride, &buffer[offset]);
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_COLOR:
                    {
                        glEnableClientState(GL_COLOR_ARRAY);
                        glColorPointer(Size[(*it).type], Type[(*it).type], stride, &buffer[offset]);
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_NORMAL:
                    {
                        glEnableClientState(GL_NORMAL_ARRAY);
                        glNormalPointer(Type[(*it).type], stride, &buffer[offset]);
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD0:
                    {
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        if( ext.MultiTexturing )
                        {
                            ext.glClientActiveTextureARB(GL_TEXTURE0_ARB);
                        }
                        glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, &buffer[offset]);
                        break;
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD1:
                    {
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        if( ext.MultiTexturing )
                        {
                            ext.glClientActiveTextureARB(GL_TEXTURE1_ARB);
                            glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, &buffer[offset]);
                        }
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD2:
                    {
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        if( ext.MultiTexturing )
                        {
                            ext.glClientActiveTextureARB(GL_TEXTURE2_ARB);
                            glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, &buffer[offset]);
                        }
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD3:
                    {
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        if( ext.MultiTexturing )
                        {
                            ext.glClientActiveTextureARB(GL_TEXTURE3_ARB);
                            glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, &buffer[offset]);
                        }
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD4:
                    {
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        if( ext.MultiTexturing )
                        {
                            ext.glClientActiveTextureARB(GL_TEXTURE4_ARB);
                            glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, &buffer[offset]);
                        }
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD5:
                    {
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        if( ext.MultiTexturing )
                        {
                            ext.glClientActiveTextureARB(GL_TEXTURE5_ARB);
                            glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, &buffer[offset]);
                        }
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD6:
                    {
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        if( ext.MultiTexturing )
                        {
                            ext.glClientActiveTextureARB(GL_TEXTURE6_ARB);
                            glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, &buffer[offset]);
                        }
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD7:
                    {
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        if( ext.MultiTexturing )
                        {
                            ext.glClientActiveTextureARB(GL_TEXTURE7_ARB);
                            glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, &buffer[offset]);
                        }
                    }

                    case CORE::OMGL_ELEMENT_TARGET_TEXCOORD8:
                    {
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        if( ext.MultiTexturing )
                        {
                            ext.glClientActiveTextureARB(GL_TEXTURE8_ARB);
                            glTexCoordPointer(Size[(*it).type], Type[(*it).type], stride, &buffer[offset]);
                        }
                    }

                    default:
                        break;
                }
            }



            const GLushort * indices = (GLushort*)index_buffer->GetBuffer();
            unsigned int count = (index_buffer->GetSize()*index_buffer->GetStride()/2);

            glEnableClientState(GL_INDEX_ARRAY);

            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, indices);

            glDisableClientState(GL_INDEX_ARRAY);

            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);

        }

        void OGLMeshVertexArray::Update() const
        {
        }
    }
}
