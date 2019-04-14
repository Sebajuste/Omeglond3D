#include "CMesh.hpp"

#include "CDevice.hpp"
#include "IVideoDriver.hpp"

#include "../Debug/DebugAllocation.hpp"

#include "../Utils/Logger/ILogger.hpp"

using namespace OMGL3D::MATH;

namespace OMGL3D
{
    namespace CORE
    {
        CMesh::CMesh() : IMesh(""),  _type(OMGL_MESH_TRIANGLE), _index_buffer(0) //, _vertex(0), _indices(0)
        {
        }

        CMesh::CMesh(const std::string &name) : IMesh(name), _type(OMGL_MESH_TRIANGLE), _index_buffer(0)//, _vertex(0), _indices(0)
        {
        }

        CMesh::CMesh(const CMesh &mesh) : IMesh(""), _type(OMGL_MESH_TRIANGLE), _index_buffer(0)
        {
        }

        CMesh::~CMesh()
        {
        }

        IMesh * CMesh::Copy(const std::string & name) const
        {
            if( _index_buffer.GetPtr() == 0 || _vertex_buffers.size() == 0)
            {
                UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_ERROR) << "Error copy Mesh " << "; index buffer or vertex buffer empty" << UTILS::OMGL_LOGGER_FLUSH;
                return 0;
            }
            IMesh * copy = CDevice::GetDevice()->GetVideoDriver()->CreateEmptyMesh(name);

            if( copy == 0 )
            {
                throw EXCP::OMGLException("CMesh::copy()   copy null");
            }

            copy->SetType( this->GetType() );

            DeclarationPtr copy_dec = GetDeclaration()->Copy();
            copy->SetDeclaration(copy_dec);

            // copie des indices
            {
                unsigned int size = _index_buffer.GetPtr()->GetSize();
                unsigned int stride = _index_buffer.GetPtr()->GetStride();

                IBufferBase * index = CDevice::GetDevice()->GetVideoDriver()->CreateBuffer(size, stride, OMGL_BUFFER_INDEX);

                const unsigned char * source = reinterpret_cast<const unsigned char*>(ConstLockIndexBuffer(0, size*stride));
                unsigned char* buffer = reinterpret_cast<unsigned char*>(index->Lock(0, size*stride));
                std::copy(source, source + size*stride, buffer);
                index->Unlock();
                UnlockIndexBuffer();
                copy->SetIndexBuffer(index);
            }

            // copie des vertex buffer

            BufferVector::const_iterator it;
            for(it=_vertex_buffers.begin(); it!=_vertex_buffers.end(); ++it)
            {
                unsigned int size = (*it).GetPtr()->GetSize();
                unsigned int stride = (*it).GetPtr()->GetStride();

                IBufferBase * buffer = CDevice::GetDevice()->GetVideoDriver()->CreateBuffer(size, stride, OMGL_BUFFER_VERTEX);

                const unsigned char * source = reinterpret_cast<const unsigned char*>( (*it).GetPtr()->ConstLock(0, size*stride));
                unsigned char * datas = reinterpret_cast<unsigned char*>(buffer->Lock(0, size*stride));
                std::copy(source, source + size*stride, datas);
                buffer->Unlock();
                (*it).GetPtr()->Unlock();

                copy->AddVertexBuffer(buffer);
            }

            return copy;
        }

        void CMesh::SetType(const MeshType & type)
        {
            _type = type;
        }

        const MeshType & CMesh::GetType() const
        {
            return _type;
        }

        void CMesh::AddVertexBuffer(IBufferBase * buffer)
        {
            _vertex_buffers.push_back(buffer);
        }


        void CMesh::SetIndexBuffer(IBufferBase * buffer)
        {
            _index_buffer = buffer;
        }
/*
        void CMesh::setDeclaration(IDeclaration * declaration)
        {
            _declaration = declaration;
        }
*/
        void CMesh::SetDeclaration(DeclarationPtr declaration)
        {
            _declaration = declaration;
        }

        const IDeclaration * CMesh::GetDeclaration() const
        {
            return _declaration.GetPtr();
        }

        unsigned int CMesh::GetVertexBufferSize() const
        {
            return _vertex_buffers.size();
        }

        void CMesh::NormalFace()
        {
            /*
            delete[] _normal;
            _normal = new mesh_normal[_count_vertex];

            for(int i=0; i<_count_indices; ++i)
            {
                MATH::Vector3f ve1a(_vertex[_indices[i].vert[0]].x, _vertex[_indices[i].vert[0]].y, _vertex[_indices[i].vert[0]].z);
                MATH::Vector3f ve1b(_vertex[_indices[i].vert[1]].x, _vertex[_indices[i].vert[1]].y, _vertex[_indices[i].vert[1]].z);

                MATH::Vector3f ve1 = ve1b - ve1a;

                MATH::Vector3f ve2a(_vertex[_indices[i].vert[2]].x, _vertex[_indices[i].vert[2]].y, _vertex[_indices[i].vert[2]].z);

                MATH::Vector3f ve2 = ve2a - ve1b;

                MATH::Vector3f ve = MATH::Vector3f::vectorCross(ve2, ve1);

                _normal[_indices[i].vert[0]].x=ve.x; _normal[_indices[i].vert[0]].y=ve.y; _normal[_indices[i].vert[0]].z=ve.z;
                _normal[_indices[i].vert[1]].x=ve.x; _normal[_indices[i].vert[1]].y=ve.y; _normal[_indices[i].vert[1]].z=ve.z;
                _normal[_indices[i].vert[2]].x=ve.x; _normal[_indices[i].vert[2]].y=ve.y; _normal[_indices[i].vert[2]].z=ve.z;
            }
            */
        }

        void CMesh::NormalVertex()
        {

            // on calcul les normales par faces
            this->NormalFace();
    /*
            mesh_vertex *v = &_vertex[0];
            mesh_normal *n = _normal;

            for(int i=0; i<_count_vertex/3; ++i)
            {
                mesh_normal max;
                int nb=1;
                max.x = n[i].x;
                max.y = n[i].y;
                max.z = n[i].z;

                for(int j=0; j<_count_vertex/3; ++j)
                {
                    if( j != i)
                    {
                        if( v[i].x == v[j].x && v[i].y == v[j].y && v[i].z == v[j].z )
                        {
                            nb++;
                            max.x += n[j].x;
                            max.y += n[j].y;
                            max.z += n[j].z;
                        }
                    }
                }

                for(int j=0; j<_count_vertex/3; ++j)
                {
                        if( v[i].x == v[j].x && v[i].y == v[j].y && v[i].z == v[j].z )
                        {
                            n[j].x = max.x / nb;
                            n[j].y = max.y / nb;
                            n[j].z = max.z / nb;

                        }
                }
            }
    */
        }

        Vector3f CMesh::GetCollide(const Vector3f & vPos, const Vector3f & vRayon) const
        {
            Vector3f vFinal;
            /*

            float min_distance = -1.0;

            for(unsigned int index_poly=0; index_poly < _count_indices; ++index_poly)
            {
                Vector3f p1(_vertex[_indices[index_poly].vert[0]].x, _vertex[_indices[index_poly].vert[0]].y, _vertex[_indices[index_poly].vert[0]].z);
                Vector3f p2(_vertex[_indices[index_poly].vert[1]].x, _vertex[_indices[index_poly].vert[1]].y, _vertex[_indices[index_poly].vert[1]].z);
                Vector3f p3(_vertex[_indices[index_poly].vert[2]].x, _vertex[_indices[index_poly].vert[2]].y, _vertex[_indices[index_poly].vert[2]].z);

                Vector3f v1 = p1 - p2;
                Vector3f v2 = p1 - p3;

                Vector3f normal = Vector3f::vectorCross(v1, v2).normalize();

                // Si le rayon et le polygone sont parrallèle
                float dot = Vector3f::vectorDot(normal, vRayon);
                if( dot >= 0 ) continue;

                // On calcul le point de collision du rayon avec le plan
                float t = Vector3f::vectorDot(normal, p1 - vPos) / dot;

                // On vérifie que le point est bien sur la demie droite dans le sens du rayon
                if( t < 0 ) continue;

                Vector3f vCollide = vPos + vRayon * t;

                // On vérifie que le point de collision est bien dans le triangle
                Vector3f a = p1 - vCollide;
                Vector3f b = p2 - vCollide;
                Vector3f c = p3 - vCollide;
                Vector3f vVerif = a.normalize() + b.normalize() + c.normalize();

                if( vVerif.length() > 1) continue;

                Vector3f vDist = vPos - vCollide;
                if( vDist.length() < min_distance || min_distance == -1)
                {
                    vFinal = vCollide;
                    min_distance = vDist.length();
                }
            }
            */

            return vFinal;
        }

        void * CMesh::LockVertexBuffer(unsigned int offset, unsigned int size, unsigned int canal)
        {
            if( canal < _vertex_buffers.size() )
            {
                return _vertex_buffers[canal]->Lock(offset, size);
            }
            /*
            if( _vertex_buffer != 0)
            {
                return _vertex_buffer->lock(offset, size);
            }
            */
            return 0;
        }

        void CMesh::UnlockVertexBuffer(unsigned int canal) const
        {
            if( canal < _vertex_buffers.size() )
            {
                _vertex_buffers[canal].GetPtr()->Unlock();
            }
            /*
            if( _vertex_buffer != 0)
            {
                _vertex_buffer->unlock();
            }
            */
        }

        void * CMesh::LockIndexBuffer(unsigned int offset, unsigned int size)
        {
            if( _index_buffer.GetPtr() != 0)
            {
                return _index_buffer->Lock(offset, size);
            }
            return 0;
        }

        const void * CMesh::ConstLockIndexBuffer(unsigned int offset, unsigned int size) const
        {
           if( _index_buffer.GetPtr() != 0)
            {
                return _index_buffer.GetPtr()->ConstLock(offset, size);
            }
            return 0;
        }

        void CMesh::UnlockIndexBuffer() const
        {
            if( _index_buffer.GetPtr() != 0)
            {
                _index_buffer.GetPtr()->Unlock();
            }
        }
    }
}
