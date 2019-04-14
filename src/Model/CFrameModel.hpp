#ifndef _DEF_OMEGLOND3D_CFRAMEMODEL_HPP
#define _DEF_OMEGLOND3D_CFRAMEMODEL_HPP

#include "IFrameModel.hpp"

#include "../Utils/Ptr/SmartPtr.hpp"

#include <vector>

namespace OMGL3D
{
    namespace MODEL
    {
        struct FrameVertex {
            float x, y, z;
        };

        struct FrameInfo {
            std::vector<FrameVertex> vertex;
            std::vector<FrameVertex> normal;
        };

        class CFrameModel : public IFrameModel
        {

        public:

            CFrameModel(const std::string & name);

            ~CFrameModel();

            void SetRootMesh(CORE::IMesh * mesh);

            void AddFrameInfo(const FrameInfo & frame);

            unsigned int GetMaxFrames() const;

            void Animate(unsigned int frame, unsigned int next_frame, float fPercent);

            void Draw(const CORE::AlphaTest & alpha) const;

            void Draw(const CORE::BlendingMode & blending) const;

            void Draw(const CORE::AlphaTest & alpha, const CORE::BlendingMode & blending) const;

            void Draw()const;



        private:

            typedef std::vector<FrameInfo> Frames;
            Frames _frames;

            UTILS::ptr<CORE::IMesh>::SharedPtr _rootMesh;
        };
    }
}

#endif
