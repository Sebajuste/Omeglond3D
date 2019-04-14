#ifndef _DEF_OMEGLOND3D_CSCENENODEMANAGER_HPP
#define _DEF_OMEGLOND3D_CSCENENODEMANAGER_HPP

namespace OMGL3D
{
    namespace SCENE
    {

        template<class C> class CSceneNodeManager
        {

        public:

            CSceneNodeManager();

            ~CSceneNodeManager();


        private:

            typedef std::vector<C*> NodeList;

            NodeList _node_list;

        }
    }
}

#endif
