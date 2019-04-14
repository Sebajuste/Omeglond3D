#include "CSquare.hpp"

#include "../../Core/IVideoDriver.hpp"
#include "../../Core/CDevice.hpp"
#include "../../Core/CMesh.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        CSquare::CSquare() : MODEL::CStaticModel("omgl_prefab_square")
        {
            CORE::IVideoDriver * driver = CDevice::GetDevice()->GetVideoDriver();


            OMGL3D::CORE::vertex_texcoord2 square_vertex[] = {
                {0, 0, 0, 0, 0},
                {0, 1, 0, 0, 1},
                {1, 1, 0, 1, 1},
                {1, 0, 0, 1, 0}
            };

            OMGL3D::CORE::indices3 square_index[] = {
                {0, 1, 2},
                {2, 3, 0}
            };

            OMGL3D::CORE::IBufferBase * square_vertex_buffer = driver->CreateBuffer(square_vertex, OMGL3D::CORE::OMGL_BUFFER_VERTEX);
            OMGL3D::CORE::IBufferBase * square_index_buffer = driver->CreateBuffer(square_index, OMGL3D::CORE::OMGL_BUFFER_INDEX);

            OMGL3D::CORE::IMesh * square_mesh = driver->CreateEmptyMesh("omgl_prefab_square_mesh");
            square_mesh->SetType(OMGL3D::CORE::OMGL_MESH_TRIANGLE);

            OMGL3D::CORE::Element square_elements[] = {
                {0, OMGL3D::CORE::OMGL_ELEMENT_TARGET_POSITIONAL, OMGL3D::CORE::OMGL_ELEMENT_TYPE_FLOAT3},
                {0, OMGL3D::CORE::OMGL_ELEMENT_TARGET_TEXCOORD0, OMGL3D::CORE::OMGL_ELEMENT_TYPE_FLOAT2}
            };

            OMGL3D::CORE::IDeclaration * square_declaration = driver->CreateDeclaration(square_elements);
            square_mesh->SetDeclaration(square_declaration);

            square_mesh->AddVertexBuffer(square_vertex_buffer);
            square_mesh->SetIndexBuffer(square_index_buffer);

            this->AddMesh(square_mesh);
        }
    }
}
