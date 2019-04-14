#ifndef _DEF_OMEGLOND3D_OGL3VIDEODRIVER_HPP
#define _DEF_OMEGLOND3D_OGL3VIDEODRIVER_HPP

#include "../../Core/CVideoDriver.hpp"


#include "OGL3ColorBuffer.hpp"
#include "OGL3DepthBuffer.hpp"

namespace OMGL3D
{
    namespace CORE {
        class IMesh;
        class IDeclaration;

        class IBuffer;
        class ITexture;
        class ICubeMap;
        class ILight;

        class IShaderBase;
        class IShader;
    }

    namespace OGL3
    {
        class OGL3VideoDriver : public CORE::CVideoDriver
        {

        public:

            OGL3VideoDriver();

            /// Buffers

            CORE::IColorBuffer * GetColorBuffer();

            CORE::IDepthBuffer * GetDepthBuffer();


            void Begin();

            void End();

            void SwapBuffer();

            void SetViewPort(int x, int y, int width, int height);


            /// Matrix

            void PushMatrix(const CORE::MatrixType &type);

            void PopMatrix(const CORE::MatrixType &type);

            void MultMatrix(const MATH::Matrix4f &matrix, const CORE::MatrixType &type);

            void LoadMatrix(const MATH::Matrix4f &matrix, const CORE::MatrixType &type);


            /// Texture

            CORE::ITexture * CreateEmptyTexture(const std::string & name, int width, int height, const CORE::ColorBufferType & type, bool mipmap=true);

            CORE::ITexture * CreateTexture(const CORE::CPicture &picture, bool mipmap=true);

            CORE::ITexture * CreateTexture(const std::string & name, const CORE::CPicture * images, std::size_t size);

            CORE::ICubeMap * CreateCubeMap(const std::string &name);


            ///  Font

            FONT::IFont * CreateSystemFont(const std::string & font_name, int size=12, bool bold=false, bool italic=false);


            /// Mesh

            CORE::IDeclaration * CreateDeclaration(const CORE::Element *elements, std::size_t size) const;

            CORE::IMesh * CreateEmptyMesh(const std::string & name);


            /// Les lumières

            CORE::ILight * CreateLight(const std::string & name);


            /// Frame Buffer render

            CORE::IFrameBufferRender * CreateFrameBufferRender(const std::string & name, int width, int height);


            /// Shaders

            // GLSL

            CORE::IShaderBase * CreateShaderProgramGLSL(const std::string & name, const CORE::ShaderType & type);

            CORE::IShader * CreateShaderGLSL(const std::string & name, CORE::IShaderBase * vertex_shader, CORE::IShaderBase * pixel_shader);



        private:

            CORE::IBufferBase * CreateBuffer(unsigned int size, unsigned int stride, const CORE::BufferType &type)const;

            CORE::IMesh * CreateMesh(CORE::IBufferBase * vertex_buffer, CORE::IBufferBase * index_buffer, const std::string &name);


            OGL3ColorBuffer _colorBuffer;
            OGL3DepthBuffer _depthBuffer;



        };
    }

}

#endif

