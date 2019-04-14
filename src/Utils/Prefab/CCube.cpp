#include "CCube.hpp"

#include "../../Core/CDevice.hpp"
#include "../../Core/CMesh.hpp"
#include "../../Core/IVideoDriver.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        CCube::CCube() : MODEL::CStaticModel("omgl_prefab_cube")
        {
            CORE::IVideoDriver * driver = CDevice::GetDevice()->GetVideoDriver();

            OMGL3D::CORE::vertex_texcoord3 vertex[] = {
                {-1,-1,-1,  -1,-1,-1},
                {-1, 1,-1,  -1, 1,-1},
                {-1,-1, 1,  -1,-1, 1},
                {-1, 1, 1,  -1, 1, 1},

                { 1,-1,-1,  1,-1,-1},
                { 1,-1, 1,  1,-1, 1},
                { 1, 1,-1,  1, 1,-1},
                { 1, 1, 1,  1, 1, 1},
            };

            OMGL3D::CORE::indices3 index[] = {
                {0, 1, 2},
                {1, 2, 3},
                {4, 5, 6},
                {5, 6, 7},
                {0, 2, 4},
                {2, 4, 5},
                {1, 6, 3},
                {6, 3, 7},
                {0, 4, 1},
                {4, 1, 6},
                {2, 3, 5},
                {3, 5, 7}
            };

            CORE::Element elements[] = {
                {0, CORE::OMGL_ELEMENT_TARGET_POSITIONAL, CORE::OMGL_ELEMENT_TYPE_FLOAT3},
                {0, CORE::OMGL_ELEMENT_TARGET_TEXCOORD0, CORE::OMGL_ELEMENT_TYPE_FLOAT3}
            };

            CORE::IBufferBase * vertex_buffer = driver->CreateBuffer(vertex, CORE::OMGL_BUFFER_VERTEX);
            CORE::IBufferBase * index_buffer = driver->CreateBuffer(index, CORE::OMGL_BUFFER_INDEX);



            CORE::IDeclaration * declaration = driver->CreateDeclaration(elements);

            CORE::IMesh * mesh = driver->CreateEmptyMesh("omgl_prefab_cube_mesh");
            mesh->SetDeclaration(declaration);
            mesh->AddVertexBuffer(vertex_buffer);
            mesh->SetIndexBuffer(index_buffer);
            mesh->SetType(CORE::OMGL_MESH_TRIANGLE);

            this->AddMesh(mesh);
        }
    }
}
