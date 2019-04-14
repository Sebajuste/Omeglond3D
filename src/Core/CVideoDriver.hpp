#ifndef _DEF_OMEGLOND3D_CVIDEODRIVER_HPP
#define _DEF_OMEGLOND3D_CVIDEODRIVER_HPP

#include "IVideoDriver.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class CVideoDriver : public IVideoDriver
        {

        public:

            CVideoDriver();

            virtual ~CVideoDriver();

            /// Media

            void AddFilePath(const std::string & path);

            ITexture * GetTexture(const std::string &name, bool mipmap=true) throw(EXCP::OMGLException);

            ITexture * GetTexture(const std::string &name, const std::string * images, std::size_t size) throw(EXCP::OMGLException);

            ICubeMap * GetCubeMap(const std::string &name);

            FONT::IFont * GetFont(const std::string & font_name, int size=12, bool bold=false, bool italic=false);

            MODEL::IStaticModel * GetStaticModel(const std::string & name);

            MODEL::IStaticModel * GetPrefabSquare();

            MODEL::IStaticModel * GetPrefabCube();

            IFrameBufferRender * GetFrameBufferRender(const std::string & name);

            IFrameBufferRender * GetFrameBufferRender(const std::string & name, int width, int height);

            IShader * GetShader(const std::string & name, const std::string & vertex_file, const std::string & pixel_file);

            ILight * GetLight(const std::string & name);


            /// Render

            virtual IColorBuffer * GetColorBuffer()=0;

            virtual IDepthBuffer * GetDepthBuffer()=0;

            virtual void Begin()=0;

            virtual void End()=0;

            virtual void SwapBuffer()=0;

            virtual void SetViewPort(int x, int y, int width, int height)=0;


            /// Matrix

            virtual void PushMatrix(const MatrixType &type)=0;

            virtual void PopMatrix(const MatrixType &type)=0;

            virtual void MultMatrix(const MATH::Matrix4f &matrix, const MatrixType &type)=0;

            virtual void LoadMatrix(const MATH::Matrix4f &matrix, const MatrixType &type)=0;


            /// Texture

            virtual ITexture * CreateEmptyTexture(const std::string & name, int width, int height, const ColorBufferType & type, bool mipmap=true)=0;

            virtual ITexture * CreateTexture(const CORE::CPicture &picture, bool mipmap=true)=0;

            virtual ITexture * CreateTexture(const std::string & name, const CPicture * images, std::size_t size)=0;

            virtual ICubeMap * CreateCubeMap(const std::string &name)=0;


            ///  Font

            virtual FONT::IFont * CreateSystemFont(const std::string & font_name, int size=12, bool bold=false, bool italic=false)=0;


            ///  Mesh

            virtual CORE::IDeclaration * CreateDeclaration(const CORE::Element *elements, std::size_t size)const=0;

            virtual CORE::IMesh * CreateEmptyMesh(const std::string &name)=0;


            /// Les lumières

            virtual ILight * CreateLight(const std::string & name)=0;


            /// Frame Buffer render

            virtual IFrameBufferRender * CreateFrameBufferRender(const std::string & name, int width, int height)=0;


            /// Shader

            // GLSL
            virtual CORE::IShaderBase * CreateShaderProgramGLSL(const std::string & name, const CORE::ShaderType & type)=0;

            virtual CORE::IShader * CreateShaderGLSL(const std::string & name, CORE::IShaderBase * vertex_shader, CORE::IShaderBase * pixel_shader)=0;



        private:

            virtual CORE::IBufferBase * CreateBuffer(unsigned int size, unsigned int stride, const CORE::BufferType &type)const=0;

            virtual CORE::IMesh * CreateMesh(CORE::IBufferBase * vertex_buffer, CORE::IBufferBase * index_buffer, const std::string &name)=0;

        };
    }
}

#endif
