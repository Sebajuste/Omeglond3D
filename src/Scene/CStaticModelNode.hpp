#ifndef _DEF_OMEGLOND3D_CSTATICMODELNODE_HPP
#define _DEF_OMEGLOND3D_CSTATICMODELNODE_HPP

#include "CModelNode.hpp"

namespace OMGL3D
{
    namespace MODEL {
        class IStaticModel;
    }

    namespace SCENE
    {
        class CStaticModelNode : public CModelNode
        {

        public:

            CStaticModelNode(const std::string & name);

            ~CStaticModelNode();

            void SetStaticModel(MODEL::IStaticModel * model);

            MODEL::IStaticModel * GetStaticModel();

            void Draw();


        private:

            UTILS::ptr<MODEL::IStaticModel>::ResourcePtr _model;
        };

        //typedef UTILS::ptr<CStaticModelNode>::SharedPtr StaticModelNodePtr;
    }
}

#endif
