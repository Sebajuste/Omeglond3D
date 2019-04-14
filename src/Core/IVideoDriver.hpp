#ifndef _DEF_OMEGLOND3D_IVIDEODRIVER_HPP
#define _DEF_OMEGLOND3D_IVIDEODRIVER_HPP

#include <string>

#include "ECoreEnum.hpp"
#include "IBufferBase.hpp"
#include "IColorBuffer.hpp"
#include "IDepthBuffer.hpp"
#include "IFrameBufferRender.hpp"
#include "IDeclaration.hpp"
#include "CResourceManager.hpp"

#include "../Exception/OmglException.hpp"

//#include "../Font/IFont.hpp"

#include "../Math/Matrix4.hpp"

//#include "../Model/IStaticModel.hpp"

//#include "../Utils/Logger/ILogger.hpp"

#include "../Utils/Ptr/SmartPtr.hpp"

namespace OMGL3D
{
    namespace FONT {
        class IFont;
    }

    namespace MODEL {
        class IStaticModel;
    }

    namespace CORE
    {
        //struct vertex;
        //struct indices;

        class IMesh;
        class CPicture;
        class ILight;

        class ITexture;
        class ICubeMap;
        class IBuffer;
        class IColorBuffer;
        class IDepthBuffer;

        class IFrameBufferRender;

        class IShaderBase;
        class IShader;

        class IVideoDriver
        {

        public:

            IVideoDriver() {}

            virtual ~IVideoDriver() {}

            /// Media

            virtual void AddFilePath(const std::string & path)=0;

            virtual ITexture * GetTexture(const std::string &name, bool mipmap=true) throw(EXCP::OMGLException)=0;

            virtual ITexture * GetTexture(const std::string &name, const std::string * images, std::size_t size) throw(EXCP::OMGLException)=0;

            template <std::size_t S> ITexture * GetTextureMipMap(const std::string & name, const std::string (&images)[S]) throw(EXCP::OMGLException);

            virtual ICubeMap * GetCubeMap(const std::string &name)=0;

            virtual FONT::IFont * GetFont(const std::string & font_name, int size=12, bool bold=false, bool italic=false)=0;

            virtual MODEL::IStaticModel * GetStaticModel(const std::string & name)=0;

            virtual MODEL::IStaticModel * GetPrefabSquare()=0;

            virtual MODEL::IStaticModel * GetPrefabCube()=0;

            virtual IFrameBufferRender * GetFrameBufferRender(const std::string & name)=0;

            virtual IFrameBufferRender * GetFrameBufferRender(const std::string & name, int width, int height)=0;

            virtual IShader * GetShader(const std::string & name, const std::string & vertex_file, const std::string & pixel_file)=0;

            virtual ILight * GetLight(const std::string & name)=0;


            /// Render

            virtual IColorBuffer * GetColorBuffer()=0;

            virtual IDepthBuffer * GetDepthBuffer()=0;

            virtual void Begin()=0;

            virtual void End()=0;

            virtual void SwapBuffer()=0;

            virtual void SetViewPort(int x, int y, int width, int height)=0;

            /// Matrix

            virtual void PushMatrix(const MatrixType & type)=0;

            virtual void PopMatrix(const MatrixType & type)=0;

            virtual void MultMatrix(const MATH::Matrix4f & matrix, const MatrixType & type)=0;

            virtual void LoadMatrix(const MATH::Matrix4f & matrix, const MatrixType & type)=0;


            /// Texture

            virtual ITexture * CreateEmptyTexture(const std::string & name, int width, int height, const ColorBufferType & type, bool mipmap=true)=0;

            virtual ITexture * CreateTexture(const CPicture & picture, bool mimap=true)=0;

            virtual ITexture * CreateTexture(const std::string & name, const CPicture * images, std::size_t size)=0;

            virtual ICubeMap * CreateCubeMap(const std::string & name)=0;


            ///  Font

            virtual FONT::IFont * CreateSystemFont(const std::string & font_name, int size=12, bool bold=false, bool italic=false)=0;


            ///  Mesh

            virtual CORE::IDeclaration * CreateDeclaration(const CORE::Element *elements, std::size_t size)const=0;

            template <std::size_t T> CORE::IDeclaration * CreateDeclaration(const CORE::Element (&e)[T])const;

            virtual CORE::IMesh * CreateEmptyMesh(const std::string &name)=0;

            template <class C1, class C2> CORE::IMesh * CreateMesh(unsigned int vertex_size, C1 * vertex, unsigned int index_size, C2 * index, const std::string &name);

            virtual CORE::IMesh * CreateMesh(CORE::IBufferBase * vertex_buffer, CORE::IBufferBase * index_buffer, const std::string &name)=0;

            template <class C, std::size_t S> CORE::IBufferBase * CreateBuffer( C (&c)[S], const CORE::BufferType &type) const;

            virtual CORE::IBufferBase * CreateBuffer(unsigned int size, unsigned int stride, const CORE::BufferType &type)const=0;


            /// Les lumières

            virtual ILight * CreateLight(const std::string & name)=0;


            /// Frame Buffer render

            virtual IFrameBufferRender * CreateFrameBufferRender(const std::string & name, int width, int height)=0;
        };

        template <std::size_t S> ITexture * IVideoDriver::GetTextureMipMap(const std::string & name, const std::string (&images)[S]) throw(EXCP::OMGLException)
        {
            return GetTexture(name, images, S);
        }

        template <std::size_t S> CORE::IDeclaration * IVideoDriver::CreateDeclaration(const CORE::Element (&e)[S]) const
        {
            return CreateDeclaration(e, S);
        }

        template <class C1, class C2> CORE::IMesh * IVideoDriver::CreateMesh(unsigned int vertex_size, C1 * vertex, unsigned int index_size, C2 * index, const std::string &name)
        {
            CORE::IBufferBase * vertex_buffer = CreateBuffer(vertex_size, sizeof(C1), CORE::OMGL_BUFFER_VERTEX);
            CORE::IBufferBase * index_buffer = CreateBuffer(index_size, sizeof(C2), CORE::OMGL_BUFFER_INDEX);

            C1 * vertex_buffer_datas = reinterpret_cast<C1*>(vertex_buffer->Lock(0, vertex_size));
            std::copy(vertex, vertex + vertex_size, vertex_buffer_datas);
            vertex_buffer->Unlock();

            C2 * index_buffer_datas = reinterpret_cast<C2*>(index_buffer->Lock(0, index_size));
            std::copy(index, index + index_size, index_buffer_datas);
            index_buffer->Unlock();

            CORE::IMesh * mesh = CreateMesh(vertex_buffer, index_buffer, name);

            return mesh;
        }

        template <class C, std::size_t S> CORE::IBufferBase * IVideoDriver::CreateBuffer( C (&c)[S], const CORE::BufferType &type)const
        {
            CORE::IBufferBase * buffer = CreateBuffer(S, sizeof(C), type);

            C * buffer_datas = reinterpret_cast<C*>(buffer->Lock(0, S));
            std::copy(c, c + S, buffer_datas);

            buffer->Unlock();

            return buffer;
        }
    }
}

#endif
