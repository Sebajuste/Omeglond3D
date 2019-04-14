#ifndef _DEF_OMEGLOND3D_IMESH_HPP
#define _DEF_OMEGLOND3D_IMESH_HPP

#include "CResource.hpp"

#include "IDeclaration.hpp"

#include "ECoreEnum.hpp"

#include <iostream>

namespace OMGL3D
{
    namespace CORE
    {
        struct indices;
        struct vertex;

        class IDeclaration;
        class IBufferBase;

        enum MeshType {
            OMGL_MESH_POINTS,
            OMGL_MESH_LINES,
            OMGL_MESH_TRIANGLE,
            OMGL_MESH_QUAD
        };

        class IMesh //: public CResource
        {

        public:

            IMesh(const std::string & name) {}//: CResource(name) {}

            virtual ~IMesh() {}

            virtual IMesh * Copy(const std::string & name) const=0;

            virtual void SetType(const MeshType & type)=0;

            virtual const MeshType & GetType() const=0;

            virtual void Draw(const AlphaTest & alpha) const=0;

            virtual void Draw(const BlendingMode & blending) const=0;

            virtual void Draw(const AlphaTest & alpha, const BlendingMode & blending) const=0;

            virtual void Draw() const=0;

            virtual void Update() const=0;

            //virtual void setDeclaration(IDeclaration * declaration)=0;

            virtual void SetDeclaration(DeclarationPtr declaration)=0;

            virtual const IDeclaration * GetDeclaration() const=0;


            virtual void AddVertexBuffer(IBufferBase *buffer)=0;

            virtual void SetIndexBuffer(IBufferBase * buffer)=0;


            template <class C> void FillVertexBuffer(unsigned int size, C * datas, unsigned int canal=0);

            template <class C> void FillIndexBuffer(unsigned int size, C * datas);



        private:

            virtual void * LockVertexBuffer(unsigned int offset, unsigned int size, unsigned int canal=0)=0;

            virtual void UnlockVertexBuffer(unsigned int canal=0) const=0;

            virtual void * LockIndexBuffer(unsigned int offset, unsigned int size)=0;

            virtual void UnlockIndexBuffer() const=0;

        };


        template <class C> void IMesh::FillVertexBuffer(unsigned int size, C * datas, unsigned int canal)
        {
            C * buffer = reinterpret_cast<C*>(LockVertexBuffer(0, size, canal));
            std::copy(datas, datas + size, buffer);
            UnlockVertexBuffer(canal);
        }

        template <class C> void IMesh::FillIndexBuffer(unsigned int size, C * datas)
        {
            C * buffer = reinterpret_cast<C*>(LockIndexBuffer(0, size));
            std::copy(datas, datas + size, buffer);
            UnlockIndexBuffer();
        }
    }
}

#endif
