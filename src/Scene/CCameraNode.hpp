#ifndef _DEF_OMEGLOND3D_CCAMERANODE_HPP
#define _DEF_OMEGLOND3D_CCAMERANODE_HPP

#include "CNode.hpp"

namespace OMGL3D
{
    namespace SCENE
    {
        class CCameraNode : public CNode
        {

        public:

            CCameraNode(const std::string & name);

            ~CCameraNode();

            void SetProjectionMatrix(const MATH::Matrix4f & matrix);

            const MATH::Matrix4f & GetProjectionMatrix() const;


        private:

            MATH::Matrix4f _proj_matrix;
        };

        typedef UTILS::ptr<CCameraNode>::SharedPtr CameraNodePtr;
    }
}

#endif
