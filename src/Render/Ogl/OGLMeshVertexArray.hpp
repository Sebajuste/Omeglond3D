#ifndef _DEF_OMEGLOND3D_OGLMESHVERTEXARRAY_HPP
#define _DEF_OMEGLOND3D_OGLMESHVERTEXARRAY_HPP

#include "../../Core/CMesh.hpp"

namespace OMGL3D
{
    namespace OGL
    {
        class OGLMeshVertexArray : public CORE::CMesh
        {

        public:

            OGLMeshVertexArray(const std::string &name);

            void Draw(const CORE::AlphaTest &alpha) const;

            void Draw(const CORE::BlendingMode &blending) const;

            void Draw(const CORE::AlphaTest &alpha, const CORE::BlendingMode &blending) const;

            void Draw() const;

            void Update() const;
        };
    }
}

#endif
