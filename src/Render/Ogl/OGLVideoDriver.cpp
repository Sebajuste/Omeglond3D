#include "OGLVideoDriver.hpp"

#include <GL/gl.h>

#include "../../Core/ITexture.hpp"
#include "../../Core/IFrameBuffer.hpp"
#include "../../Core/IBufferBase.hpp"
#include "../../Core/CPicture.hpp"
#include "../../Core/CMesh.hpp"

#include "../../Exception/RenderException.hpp"

#include "OGLBufferVertex.hpp"
#include "OGLBufferVertexObject.hpp"
#include "OGLCubeMap.hpp"
#include "OGLDeclaration.hpp"
#include "OGLExtention.hpp"
#include "OGLFontSystem.hpp"
#include "OGLFrameBufferObject.hpp"
#include "OGLLight.hpp"
#include "OGLTexture.hpp"
#include "OGLMeshDirectMode.hpp"
#include "OGLMeshVertexArray.hpp"
#include "OGLMeshVertexBufferObject.hpp"
#include "OGLShaderBaseGLSL.hpp"
#include "OGLShaderGLSL.hpp"



#include "../../Utils/Logger/ILogger.hpp"

#include "../../Debug/DebugAllocation.hpp"

#include <iostream>

namespace OMGL3D
{
    namespace OGL
    {
        OGLVideoDriver::OGLVideoDriver()
        {
            UTILS::ILogger::GetLogger( UTILS::OMGL_LOGGER_RENDERER ) << (unsigned char*)glGetString(GL_RENDERER) << UTILS::OMGL_LOGGER_ENDL;
            UTILS::ILogger::GetLogger( UTILS::OMGL_LOGGER_RENDERER ) << (unsigned char*)glGetString(GL_VENDOR) << UTILS::OMGL_LOGGER_ENDL;
            UTILS::ILogger::GetLogger( UTILS::OMGL_LOGGER_RENDERER ) << (unsigned char*)glGetString(GL_VERSION) << UTILS::OMGL_LOGGER_FLUSH;
        }

        CORE::IColorBuffer * OGLVideoDriver::GetColorBuffer()
        {
            return &_colorBuffer;
        }

        CORE::IDepthBuffer * OGLVideoDriver::GetDepthBuffer()
        {
            return &_depthBuffer;
        }

        void OGLVideoDriver::Begin()
        {
            _colorBuffer.Clear();
            _depthBuffer.Clear();

            OMGL3D::MATH::Matrix4f identity;
            LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_PROJECTION);
            LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_MODEL);
            LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_VIEW);
            LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_TEXTURE);
        }

        void OGLVideoDriver::End()
        {
            glFlush();
        }

        void OGLVideoDriver::SwapBuffer()
        {
        }

        void OGLVideoDriver::SetViewPort(GLint x, GLint y, GLsizei width, GLsizei height)
        {
            glViewport(x, y, width, height);
        }

        void OGLVideoDriver::PushMatrix(const CORE::MatrixType &type)
        {
            switch(type)
            {
                case CORE::OMGL_MATRIX_PROJECTION:
                    glMatrixMode(GL_PROJECTION);
                    break;

                case CORE::OMGL_MATRIX_VIEW:
                case CORE::OMGL_MATRIX_MODEL:
                    glMatrixMode(GL_MODELVIEW);
                    break;

                case CORE::OMGL_MATRIX_TEXTURE:
                    glMatrixMode(GL_TEXTURE);
                    break;
            }
            glPushMatrix();
        }

        void OGLVideoDriver::PopMatrix(const CORE::MatrixType &type)
        {
            switch(type)
            {
                case CORE::OMGL_MATRIX_PROJECTION:
                    glMatrixMode(GL_PROJECTION);
                    break;

                case CORE::OMGL_MATRIX_VIEW:
                case CORE::OMGL_MATRIX_MODEL:
                    glMatrixMode(GL_MODELVIEW);
                    break;

                case CORE::OMGL_MATRIX_TEXTURE:
                    glMatrixMode(GL_TEXTURE);
                    break;
            }
            glPopMatrix();
        }

        void OGLVideoDriver::MultMatrix(const MATH::Matrix4f &matrix, const CORE::MatrixType &type)
        {
            switch(type)
            {
                case CORE::OMGL_MATRIX_PROJECTION:
                    glMatrixMode(GL_PROJECTION);
                    break;

                case CORE::OMGL_MATRIX_VIEW:
                {
                    glMatrixMode(GL_MODELVIEW);
                    glMultMatrixf(matrix.GetInverse()());
                    return;
                }
                case CORE::OMGL_MATRIX_MODEL:
                    glMatrixMode(GL_MODELVIEW);
                    break;

                case CORE::OMGL_MATRIX_TEXTURE:
                    glMatrixMode(GL_TEXTURE);
                    break;
            }
            glMultMatrixf(matrix());
        }

        void OGLVideoDriver::LoadMatrix(const MATH::Matrix4f &matrix, const CORE::MatrixType &type)
        {
            switch(type)
            {
                case CORE::OMGL_MATRIX_PROJECTION:
                    glMatrixMode(GL_PROJECTION);
                    break;

                case CORE::OMGL_MATRIX_VIEW:
                case CORE::OMGL_MATRIX_MODEL:
                    glMatrixMode(GL_MODELVIEW);
                    break;

                case CORE::OMGL_MATRIX_TEXTURE:
                    glMatrixMode(GL_TEXTURE);
                    break;
            }
            glLoadMatrixf(matrix());
        }

        CORE::ITexture * OGLVideoDriver::CreateEmptyTexture(const std::string & name, int width, int height, const CORE::ColorBufferType & type, bool mipmap)
        {
            OGLTexture * texture = new OGLTexture(name, 24, width, height);
            texture->SetEmptyImage(type);
            return texture;
        }

        CORE::ITexture * OGLVideoDriver::CreateTexture(const CORE::CPicture & picture, bool mipmap)
        {
            CORE::ITexture * texture = new OGLTexture(picture.GetName(), picture.GetBpp(), picture.GetWidth(), picture.GetHeight());
            texture->SetImage(picture, mipmap);

            return texture;
        }

        CORE::ITexture * OGLVideoDriver::CreateTexture(const std::string & name, const CORE::CPicture * images, std::size_t size)
        {
            if( size == 0 ) {
                throw EXCP::RenderException("no mipmap for "+name);
            }

            CORE::ITexture * texture = new OGLTexture(name, images[0].GetBpp(), images[0].GetWidth(), images[0].GetHeight());
            texture->SetImage(images, size);
            return texture;
        }

        CORE::ICubeMap * OGLVideoDriver::CreateCubeMap(const std::string &name)
        {
            CORE::ICubeMap * cubeMap = new OGLCubeMap(name);
            return cubeMap;
        }

        FONT::IFont * OGLVideoDriver::CreateSystemFont(const std::string & font_name, int size, bool bold, bool italic)
        {
            OGLFontSystem * font = new OGLFontSystem(font_name);
            font->LoadFont(font_name, size, bold, italic);
            return font;
        }

        CORE::IMesh * OGLVideoDriver::CreateEmptyMesh(const std::string &name)
        {
            CORE::IMesh * mesh = 0;
            OGLExtention & ext = OGLExtention::GetInstance();

            if( ext.VertexBufferObject )
            {
                mesh = new OGLMeshVertexBufferObject(name);
            }
            else if( ext.VertexArray )
            {
                mesh = new OGLMeshVertexArray(name);
            }
            else
            {
                mesh = new OGLMeshDirectMode(name);
            }


            return mesh;
        }

        CORE::IBufferBase * OGLVideoDriver::CreateBuffer(unsigned int size, unsigned int stride, const CORE::BufferType &type) const
        {
            OGLExtention & ext = OGLExtention::GetInstance();
            CORE::IBufferBase * buffer = 0;

            if( ext.VertexBufferObject )
            {
                switch(type)
                {
                    case CORE::OMGL_BUFFER_VERTEX:
                        buffer = new OGLBufferVertexObject<GL_ARRAY_BUFFER_ARB>(size, stride);
                        break;

                    case CORE::OMGL_BUFFER_INDEX:
                        buffer = new OGLIndexBufferObject(size, stride);
                        break;
                }
            }
            else
            {
                buffer = new OGLBufferVertex(size, stride);
            }

            return buffer;
        }

        CORE::IDeclaration * OGLVideoDriver::CreateDeclaration(const CORE::Element *elements, std::size_t size)const
        {
            OGLDeclaration * declaration = new OGLDeclaration();

            static const unsigned int Size[] = {4, 4, 3, 2, 1};

            std::vector<unsigned int> Offsets(size, 0);
            for(unsigned int i=0; i<size; ++i)
            {
                OGLElement el;

                el.channel = elements[i].stream;
                el.target = elements[i].target;
                el.type = elements[i].type;
                el.offset = Offsets[elements[i].stream];

                Offsets[elements[i].stream] += Size[el.type]*SizeOf[el.type];

                declaration->AddElement(el);
            }

            return declaration;
        }

        CORE::IMesh * OGLVideoDriver::CreateMesh(CORE::IBufferBase * vertex_buffer, CORE::IBufferBase * index_buffer, const std::string &name)
        {
            CORE::CMesh * mesh = 0;
            OGLExtention & ext = OGLExtention::GetInstance();

            if( ext.VertexBufferObject)
            {
                mesh = new OGLMeshVertexBufferObject(name);
            } else if( ext.VertexArray )
            {
                mesh = new OGLMeshVertexArray(name);
            }
            else
            {
                mesh = new OGLMeshDirectMode(name);
            }

            mesh->AddVertexBuffer(vertex_buffer);
            mesh->SetIndexBuffer(index_buffer);

            return mesh;
        }

        CORE::ILight * OGLVideoDriver::CreateLight(const std::string & name)
        {
            return new OGLLight(name);
        }

        CORE::IFrameBufferRender * OGLVideoDriver::CreateFrameBufferRender(const std::string & name, int width, int height)
        {
            if( OGLExtention::GetInstance().FrameBufferObject == true)
            {
                return new OGLFrameBufferObject(name, width, height);
            }
            throw EXCP::RenderException("Frame Buffer Object not supported");
        }

        CORE::IShaderBase * OGLVideoDriver::CreateShaderProgramGLSL(const std::string & name, const CORE::ShaderType & type)
        {
            if( OGLExtention::GetInstance().ShaderGLSL == true)
            {
                return new OGLShaderBaseGLSL(name, type);
            }
            throw EXCP::RenderException("Shader GLSL not supported");
        }

        CORE::IShader * OGLVideoDriver::CreateShaderGLSL(const std::string & name, CORE::IShaderBase * vertex_shader, CORE::IShaderBase * pixel_shader)
        {
            OGLShaderBaseGLSL * glsl_vertex_shader = dynamic_cast<OGLShaderBaseGLSL*>(vertex_shader);
            OGLShaderBaseGLSL * glsl_pixel_shader  = dynamic_cast<OGLShaderBaseGLSL*>(pixel_shader);
            return new OGLShaderGLSL(name, glsl_vertex_shader, glsl_pixel_shader);
        }
    }
}
