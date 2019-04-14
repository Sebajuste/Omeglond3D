#ifndef _DEF_OMEGLOND3D_IMODEL_HPP
#define _DEF_OMEGLOND3D_IMODEL_HPP

#include "../Core/CResource.hpp"
#include "../Core/ECoreEnum.hpp"
#include "../Core/IMesh.hpp"

namespace OMGL3D
{
    namespace MODEL
    {
        class IModel : public CORE::CResource
        {

        public:

            IModel(const std::string &name) : CORE::CResource(name) { }

            virtual ~IModel() { }

            virtual void Draw(const CORE::AlphaTest & alpha) const=0;

            virtual void Draw(const CORE::BlendingMode & blending) const=0;

            virtual void Draw(const CORE::AlphaTest & alpha, const CORE::BlendingMode & blending) const=0;

            virtual void Draw()const=0;

            //virtual std::vector<UTILS::ptr<CORE::IMesh>::ResourcePtr> getAllMeshes()=0;

            // Annimation par KeyFrames
            //virtual int getMaxFrame()=0;

            //virtual const Mesh * getAnimatedMesh(const std::string &anim, unsigned int current_frame, unsigned int next_frame, float fPercent)=0;

            // TODO : Annimation par squelette
;
        };
    }
}

#endif
