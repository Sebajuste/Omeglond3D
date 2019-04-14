#ifndef _DEF_OMEGLOND3D_ISTATICMODEL_HPP
#define _DEF_OMEGLOND3D_ISTATICMODEL_HPP

#include <vector>

#include "IModel.hpp"

#include "../Utils/Ptr/SmartPtr.hpp"

namespace OMGL3D
{
    namespace MODEL
    {
        class IStaticModel : public IModel
        {

        public:

            IStaticModel(const std::string &name) : IModel(name) {}

            virtual ~IStaticModel() {}

            virtual void Draw(const CORE::AlphaTest & alpha) const=0;

            virtual void Draw(const CORE::BlendingMode & blending) const=0;

            virtual void Draw(const CORE::AlphaTest & alpha, const CORE::BlendingMode & blending) const=0;

            virtual void Draw() const=0;

            virtual std::vector<UTILS::ptr<CORE::IMesh>::SharedPtr> GetAllMeshes()=0;

            virtual void AddMesh(const UTILS::ptr<CORE::IMesh>::SharedPtr & mesh)=0;
        };
    }
}

#endif
