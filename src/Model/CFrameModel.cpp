#include "CFrameModel.hpp"

namespace OMGL3D
{
    namespace MODEL
    {
        CFrameModel::CFrameModel(const std::string & name) : IFrameModel(name)
        {
        }

        CFrameModel::~CFrameModel()
        {
        }

        void CFrameModel::SetRootMesh(CORE::IMesh * mesh)
        {
        }

        void CFrameModel::AddFrameInfo(const FrameInfo & frame)
        {
            _frames.push_back(frame);
        }

        unsigned int CFrameModel::GetMaxFrames() const
        {
            return _frames.size();
        }

        void CFrameModel::Animate(unsigned int frame, unsigned int next_frame, float fPercent)
        {
        }

        void CFrameModel::Draw(const CORE::AlphaTest & alpha) const
        {
            _rootMesh.GetPtr()->Draw(alpha);
        }

        void CFrameModel::Draw(const CORE::BlendingMode & blending) const
        {
            _rootMesh.GetPtr()->Draw(blending);
        }

        void CFrameModel::Draw(const CORE::AlphaTest & alpha, const CORE::BlendingMode & blending) const
        {
            _rootMesh.GetPtr()->Draw(alpha, blending);
        }

        void CFrameModel::Draw()const
        {
            _rootMesh.GetPtr()->Draw();
        }
    }
}
