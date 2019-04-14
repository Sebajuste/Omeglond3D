#ifndef _DEF_OMEGLOND3D_IFRAMEMODEL_HPP
#define _DEF_OMEGLOND3D_IFRAMEMODEL_HPP

#include "IModel.hpp"

namespace OMGL3D
{
    namespace MODEL
    {
        class IFrameModel : public IModel
        {

        public:

            IFrameModel(const std::string & name) : IModel(name) {}

            virtual ~IFrameModel() {}

            virtual unsigned int GetMaxFrame() const=0;

            virtual void Animate(unsigned int frame, unsigned int next_frame, float fPercent)=0;

            virtual void Draw(const CORE::AlphaTest & alpha) const=0;

            virtual void Draw(const CORE::BlendingMode & blending) const=0;

            virtual void Draw(const CORE::AlphaTest & alpha, const CORE::BlendingMode & blending) const=0;

            virtual void Draw()const=0;
        };
    }
}

#endif
