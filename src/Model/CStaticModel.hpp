#ifndef _DEF_OMEGLOND3D_STATICMODEL_HPP
#define _DEF_OMEGLOND3D_STATICMODEL_HPP

#include "IStaticModel.hpp"

#include <vector>

#include "../Core/IMesh.hpp"

namespace OMGL3D
{
    namespace MODEL
    {
        class CStaticModel : public IStaticModel
        {

        public:

            CStaticModel(const std::string &name);

            CStaticModel(const CStaticModel &model);

            ~CStaticModel();

            void Draw(const CORE::AlphaTest & alpha) const;

            void Draw(const CORE::BlendingMode & blending) const;

            void Draw(const CORE::AlphaTest & alpha, const CORE::BlendingMode & blending) const;

            void Draw() const;

            std::vector<UTILS::ptr<CORE::IMesh>::SharedPtr> GetAllMeshes();

            void AddMesh(const UTILS::ptr<CORE::IMesh>::SharedPtr & mesh);



        private:

            typedef std::vector<UTILS::ptr<CORE::IMesh>::SharedPtr> MeshList;
            MeshList _meshes;
        };
    }
}

#endif
