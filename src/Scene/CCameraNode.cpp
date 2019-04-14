#include "CCameraNode.hpp"

#include "CScene.hpp"

namespace OMGL3D
{
    namespace SCENE
    {
        CCameraNode::CCameraNode(const std::string & name) : CNode(name)
        {
        }

        CCameraNode::~CCameraNode()
        {
            if( _scene->GetActiveCamera() == this )
            {
                _scene->ResetActiveCamera();
            }
        }

        void CCameraNode::SetProjectionMatrix(const MATH::Matrix4f & matrix)
        {
            _proj_matrix = matrix;
        }

        const MATH::Matrix4f & CCameraNode::GetProjectionMatrix() const
        {
            return _proj_matrix;
        }
    }
}
