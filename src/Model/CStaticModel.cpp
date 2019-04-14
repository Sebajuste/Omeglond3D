#include "CStaticModel.hpp"

#include "../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace MODEL
    {
        CStaticModel::CStaticModel(const std::string & name) : IStaticModel(name)
        {
        }

        CStaticModel::CStaticModel(const CStaticModel & model) : IStaticModel(model.GetName())
        {
        }

        CStaticModel::~CStaticModel()
        {
        }

        void CStaticModel::Draw(const CORE::AlphaTest & alpha) const
        {
            MeshList::const_iterator it;
            for(it=_meshes.begin(); it!=_meshes.end(); ++it)
            {
                UTILS::ptr<CORE::IMesh>::SharedPtr mesh = *it;
                mesh->Draw(alpha);
            }
        }

        void CStaticModel::Draw(const CORE::BlendingMode & blending) const
        {
            MeshList::const_iterator it;
            for(it=_meshes.begin(); it!=_meshes.end(); ++it)
            {
                UTILS::ptr<CORE::IMesh>::SharedPtr mesh = *it;
                mesh->Draw(blending);
            }
        }

        void CStaticModel::Draw(const CORE::AlphaTest & alpha, const CORE::BlendingMode & blending) const
        {
            MeshList::const_iterator it;
            for(it=_meshes.begin(); it!=_meshes.end(); ++it)
            {
                UTILS::ptr<CORE::IMesh>::SharedPtr mesh = *it;
                mesh->Draw(alpha, blending);
            }
        }

        void CStaticModel::Draw() const
        {
            MeshList::const_iterator it;
            for(it=_meshes.begin(); it!=_meshes.end(); ++it)
            {
                UTILS::ptr<CORE::IMesh>::SharedPtr mesh = *it;
                mesh->Draw();
            }
        }

        std::vector<UTILS::ptr<CORE::IMesh>::SharedPtr> CStaticModel::GetAllMeshes()
        {
            return _meshes;
        }

        void CStaticModel::AddMesh(const UTILS::ptr<CORE::IMesh>::SharedPtr &mesh)
        {
            _meshes.push_back(mesh);
        }
    }
}
