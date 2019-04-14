#ifndef _DEF_OMEGLOND3D_OGL3MESHVBO_HPP
#define _DEF_OMEGLOND3D_OGL3MESHVBO_HPP

#include "../../Core/CMesh.hpp"

namespace OMGL3D
{
    namespace OGL3
    {
        class OGL3MeshVBO : public CORE::CMesh
        {

        public:

            OGL3MeshVBO(const std::string &name);

            ~OGL3MeshVBO();

            void Draw(const CORE::AlphaTest &alpha) const;

            void Draw(const CORE::BlendingMode &blending) const;

            void Draw(const CORE::AlphaTest &alpha, const CORE::BlendingMode &blending) const;

            void Draw() const;

            void Update() const;

        };
    }
}

#endif
