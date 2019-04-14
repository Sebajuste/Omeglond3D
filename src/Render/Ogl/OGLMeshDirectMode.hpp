#ifndef _DEF_OMEGLOND3D_OGLMESH_HPP
#define _DEF_OMEGLOND3D_OGLMESH_HPP

#include "../../Core/CMesh.hpp"

namespace OMGL3D
{
    namespace OGL
    {
        class OGLMeshDirectMode : public CORE::CMesh
        {

        public:

            OGLMeshDirectMode(const std::string &name);

            void Draw(const CORE::AlphaTest &alpha) const;

            void Draw(const CORE::BlendingMode &blending) const;

            void Draw(const CORE::AlphaTest &alpha, const CORE::BlendingMode &blending) const;

            void Draw() const;

            void Update() const;
        };
    }
}

#endif
