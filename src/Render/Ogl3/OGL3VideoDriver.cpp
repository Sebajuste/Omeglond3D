#include "OGL3VideoDriver.hpp"

#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#include "../../Core/ITexture.hpp"
#include "../../Core/IFrameBuffer.hpp"
#include "../../Core/IBufferBase.hpp"
#include "../../Core/CPicture.hpp"
#include "../../Core/CMesh.hpp"

#include "../../Exception/RenderException.hpp"


#include "OGL3BufferVertex.hpp"
#include "OGL3BufferVertexObject.hpp"
#include "OGL3CubeMap.hpp"
#include "OGL3Declaration.hpp"
//#include "OGL3Extention.hpp"
#include "OGL3FontSystem.hpp"
#include "OGL3MatrixManager.hpp"
//#include "OGL3FrameBufferObject.hpp"
//#include "OGL3Light.hpp"
#include "OGL3Texture.hpp"
#include "OGL3MeshVBO.hpp"
//#include "OGL3MeshVertexArray.hpp"
//#include "OGL3MeshVertexBufferObject.hpp"
#include "OGL3ShaderBaseGLSL.hpp"
#include "OGL3ShaderGLSL.hpp"



#include "../../Utils/Logger/ILogger.hpp"

#include "../../Debug/DebugAllocation.hpp"

#include <iostream>

namespace OMGL3D
{
    namespace OGL3
    {
        OGL3VideoDriver::OGL3VideoDriver()
        {
            UTILS::ILogger::GetLogger( UTILS::OMGL_LOGGER_RENDERER ) << "OMGL3D OpenGL3 Renderer" << UTILS::OMGL_LOGGER_ENDL;
            UTILS::ILogger::GetLogger( UTILS::OMGL_LOGGER_RENDERER ) << (unsigned char*)glGetString(GL_RENDERER) << UTILS::OMGL_LOGGER_ENDL;
            UTILS::ILogger::GetLogger( UTILS::OMGL_LOGGER_RENDERER ) << (unsigned char*)glGetString(GL_VENDOR) << UTILS::OMGL_LOGGER_ENDL;
            UTILS::ILogger::GetLogger( UTILS::OMGL_LOGGER_RENDERER ) << (unsigned char*)glGetString(GL_VERSION) << UTILS::OMGL_LOGGER_FLUSH;
        }

        CORE::IColorBuffer * OGL3VideoDriver::GetColorBuffer()
        {
            return &_colorBuffer;
        }

        CORE::IDepthBuffer * OGL3VideoDriver::GetDepthBuffer()
        {
            return &_depthBuffer;
        }

        void OGL3VideoDriver::Begin()
        {
            _colorBuffer.Clear();
            _depthBuffer.Clear();
        }

        void OGL3VideoDriver::End()
        {
            glFlush();
        }

        void OGL3VideoDriver::SwapBuffer()
        {
        }

        void OGL3VideoDriver::SetViewPort(int x, int y, int width, int height)
        {
            glViewport(x, y, width, height);
        }

        void OGL3VideoDriver::PushMatrix(const CORE::MatrixType & type)
        {
            OGL3MatrixManager::GetInstance().PushMatrix(type);
        }

        void OGL3VideoDriver::PopMatrix(const CORE::MatrixType & type)
        {
            OGL3MatrixManager::GetInstance().PopMatrix(type);
        }

        void OGL3VideoDriver::MultMatrix(const MATH::Matrix4f & matrix, const CORE::MatrixType & type)
        {
            OGL3MatrixManager::GetInstance().MultMatrix(matrix, type);
        }

        void OGL3VideoDriver::LoadMatrix(const MATH::Matrix4f & matrix, const CORE::MatrixType & type)
        {
            OGL3MatrixManager::GetInstance().LoadMatrix(matrix, type);
        }

        CORE::ITexture * OGL3VideoDriver::CreateEmptyTexture(const std::string & name, int width, int height, const CORE::ColorBufferType & type, bool mipmap)
        {
            OGL3Texture * texture = new OGL3Texture(name, 24, width, height);
            texture->SetEmptyImage(type);
            return texture;
        }

        CORE::ITexture * OGL3VideoDriver::CreateTexture(const CORE::CPicture & picture, bool mipmap)
        {
            CORE::ITexture * texture = new OGL3Texture(picture.GetName(), picture.GetBpp(), picture.GetWidth(), picture.GetHeight());
            texture->SetImage(picture, mipmap);

            return texture;
        }

        CORE::ITexture * OGL3VideoDriver::CreateTexture(const std::string & name, const CORE::CPicture * images, std::size_t size)
        {
            if( size == 0 ) {
                throw EXCP::RenderException("no mipmap for "+name);
            }

            CORE::ITexture * texture = new OGL3Texture(name, images[0].GetBpp(), images[0].GetWidth(), images[0].GetHeight());
            texture->SetImage(images, size);
            return texture;
        }

        CORE::ICubeMap * OGL3VideoDriver::CreateCubeMap(const std::string &name)
        {
            CORE::ICubeMap * cubeMap = new OGL3CubeMap(name);
            return cubeMap;
        }

        FONT::IFont * OGL3VideoDriver::CreateSystemFont(const std::string & font_name, int size, bool bold, bool italic)
        {
            OGL3FontSystem * font = new OGL3FontSystem(font_name);
            font->LoadFont(font_name);
            return font;
        }

        CORE::IMesh * OGL3VideoDriver::CreateEmptyMesh(const std::string &name)
        {
            return new OGL3MeshVBO(name);
        }

        CORE::IBufferBase * OGL3VideoDriver::CreateBuffer(unsigned int size, unsigned int stride, const CORE::BufferType &type) const
        {
            CORE::IBufferBase * buffer = 0;

            switch(type)
            {
                case CORE::OMGL_BUFFER_VERTEX:
                    buffer = new OGL3VertexBufferObject(size, stride);
                    break;

                case CORE::OMGL_BUFFER_INDEX:
                    buffer = new OGL3IndexBufferObject(size, stride);
                    break;
            }

            return buffer;
        }

        CORE::IDeclaration * OGL3VideoDriver::CreateDeclaration(const CORE::Element *elements, std::size_t size)const
        {
            OGL3Declaration * declaration = new OGL3Declaration();

            static const unsigned int Size[] = {4, 4, 3, 2, 1};

            std::vector<unsigned int> Offsets(size, 0);
            for(unsigned int i=0; i<size; ++i)
            {
                OGL3Element el;

                el.channel = elements[i].stream;
                el.target = elements[i].target;
                el.type = elements[i].type;
                el.offset = Offsets[elements[i].stream];

                Offsets[elements[i].stream] += Size[el.type]*SizeOf[el.type];

                declaration->AddElement(el);
            }

            return declaration;
        }

        CORE::IMesh * OGL3VideoDriver::CreateMesh(CORE::IBufferBase * vertex_buffer, CORE::IBufferBase * index_buffer, const std::string &name)
        {
            CORE::CMesh * mesh = new OGL3MeshVBO(name);

            mesh->AddVertexBuffer(vertex_buffer);
            mesh->SetIndexBuffer(index_buffer);

            return mesh;
        }

        CORE::ILight * OGL3VideoDriver::CreateLight(const std::string & name)
        {
            //return new OGLLight(name);
            return 0;
        }

        CORE::IFrameBufferRender * OGL3VideoDriver::CreateFrameBufferRender(const std::string & name, int width, int height)
        {
            /*
            if( OGLExtention::GetInstance().FrameBufferObject == true)
            {
                return new OGLFrameBufferObject(name, width, height);
            }
            */
            throw EXCP::RenderException("Frame Buffer Object not supported");
        }

        CORE::IShaderBase * OGL3VideoDriver::CreateShaderProgramGLSL(const std::string & name, const CORE::ShaderType & type)
        {
            return new OGL3ShaderBaseGLSL(name, type);
            /*
            if( OGLExtention::GetInstance().ShaderGLSL == true)
            {
                return new OGLShaderBaseGLSL(name, type);
            }
            */
            throw EXCP::RenderException("Shader GLSL not supported");
        }

        CORE::IShader * OGL3VideoDriver::CreateShaderGLSL(const std::string & name, CORE::IShaderBase * vertex_shader, CORE::IShaderBase * pixel_shader)
        {

            OGL3ShaderBaseGLSL * glsl_vertex_shader = dynamic_cast<OGL3ShaderBaseGLSL*>(vertex_shader);
            OGL3ShaderBaseGLSL * glsl_pixel_shader  = dynamic_cast<OGL3ShaderBaseGLSL*>(pixel_shader);
            return new OGL3ShaderGLSL(name, glsl_vertex_shader, glsl_pixel_shader);

            //return 0;
        }
    }
}

