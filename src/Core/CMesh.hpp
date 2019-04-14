#ifndef _DEF_OMEGLOND3D_CMESH_HPP
#define _DEF_OMEGLOND3D_CMESH_HPP

#include <string>
#include <vector>

#include "IMesh.hpp"
#include "IBufferBase.hpp"

#include "../Math/Vector3.hpp"

#include "../Utils/Ptr/SmartPtr.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        #pragma pack(push, 1)
        struct vertex
        {
            float x, y, z;
            float nx, ny, nz;
        };
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct vertex_normal
        {
            float x, y, z;
            float nx, ny, nz;
        };
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct vertex_texcoord2
        {
            float x, y, z;
            float s, t;
        };
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct vertex_texcoord3
        {
            float x, y, z;
            float s, t, q;
        };
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct vertex_normal_texcoord
        {
            float x, y, z;
            float nx, ny, nz;
            float s, t;
        };
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct vertex_normal_color
        {
            float x, y, z;
            float nx, ny, nz;
            unsigned char c1, c2, c3, c4;
        };
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct vertex_normal_texcoord_color
        {
            float x, y, z;
            float nx, ny, nz;
            float s, t;
            unsigned char c1, c2, c3, c4;
        };
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct texcoord2
        {
            float s, t;
        };
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct texcoord3
        {
            float s, t, q;
        };
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct color
        {
            unsigned char c1, c2, c3, c4;
        };
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct indices1
        {
            unsigned short v;
        };
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct indices2
        {
            unsigned short v1, v2;
        };
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct indices3
        {
            unsigned short v1, v2, v3;
        };
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct indices4
        {
            unsigned short v1, v2, v3, v4;
        };
        #pragma pack(pop)

        class CMesh : public IMesh
        {

        public:

            CMesh();

            CMesh(const std::string &name);

            CMesh(const CMesh &mesh);

            virtual ~CMesh();

            IMesh * Copy(const std::string & name) const;

            void SetType(const MeshType & type);

            const MeshType & GetType() const;

            virtual void Draw(const AlphaTest & alpha) const {}

            virtual void Draw(const BlendingMode & blending) const {}

            virtual void Draw(const AlphaTest & alpha, const BlendingMode & blending) const {}

            virtual void Draw() const {}

            virtual void Update() const {}

            void AddVertexBuffer(IBufferBase * buffer);

            void SetIndexBuffer(IBufferBase * buffer);

            //void setDeclaration(IDeclaration * declaration);

            void SetDeclaration(DeclarationPtr declaration);

            const IDeclaration * GetDeclaration() const;

            unsigned int GetVertexBufferSize() const;


            void NormalFace(); // calcul les normales par faces
            void NormalVertex(); // calcul les normales par vertex

            MATH::Vector3f GetCollide(const MATH::Vector3f & vPos, const MATH::Vector3f & vRayon) const;


        protected:

            MeshType _type;
            typedef std::vector<BufferBasePtr> BufferVector;
            BufferVector _vertex_buffers;
            BufferBasePtr _index_buffer;
            DeclarationPtr _declaration;


        private:

            void * LockVertexBuffer(unsigned int offset, unsigned int size, unsigned int canal=0);

            void UnlockVertexBuffer(unsigned int canal=0) const;

            void * LockIndexBuffer(unsigned int offset, unsigned int size);

            const void * ConstLockIndexBuffer(unsigned int offset, unsigned int size) const;

            void UnlockIndexBuffer() const;
        };
    }
}

#endif
