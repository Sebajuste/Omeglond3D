#ifndef _DEF_OMEGLOND3D_OGLMESHVERTEXBUFFEROBJECT_HPP
#define _DEF_OMEGLOND3D_OGLMESHVERTEXBUFFEROBJECT_HPP

#include "../../Core/CMesh.hpp"

namespace OMGL3D
{
    namespace OGL
    {
        class OGLMeshVertexBufferObject : public CORE::CMesh
        {

        public:

            OGLMeshVertexBufferObject(const std::string &name);

            ~OGLMeshVertexBufferObject();

            void Draw(const CORE::AlphaTest &alpha) const;

            void Draw(const CORE::BlendingMode &blending) const;

            void Draw(const CORE::AlphaTest &alpha, const CORE::BlendingMode &blending) const;

            void Draw() const;

            void Update() const;

        };
    }
}

#endif
