#include "CScene.hpp"

#include "CStaticModelNode.hpp"
#include "CCameraNode.hpp"

#include "../Core/CDevice.hpp"
#include "../Core/ITexture.hpp"
#include "../Core/IVideoDriver.hpp"

#include "../Debug/DebugAllocation.hpp"

#include "../Model/IStaticModel.hpp"

#include <iostream>

namespace OMGL3D
{
    namespace SCENE
    {
        CScene::CScene(const std::string & name) : _name(name), _active_camera(0), _rootNode(new CNode("root"))
        {
        }

        CScene::~CScene()
        {
        }

        CNode * CScene::CreateNode(const std::string & name)
        {
            CNode * node = new CNode(name);
            node->_scene = this;
            return node;
        }

        CStaticModelNode * CScene::CreateStaticModelNode(const std::string & name)
        {
            CStaticModelNode * node = new CStaticModelNode(name);
            node->_scene = this;
            _list_model.push_back(node);
            return node;
        }

        CCameraNode * CScene::CreateCameraNode(const std::string & name)
        {
            CCameraNode * node = new CCameraNode(name);
            node->_scene = this;
            return node;
        }

        //void CScene::SetActiveCamera(OMGL3D::UTILS::ptr<CCameraNode>::SharedPtr camera_node)
        void CScene::SetActiveCamera(CCameraNode * camera_node)
        {
            if( camera_node == 0) return;
            if( camera_node->_father != 0 )
            {
                _active_camera = camera_node;
            }
        }

        void CScene::ResetActiveCamera()
        {
            _active_camera = 0;
        }

        //OMGL3D::UTILS::ptr<CCameraNode>::SharedPtr CScene::GetActiveCamera()
        CCameraNode * CScene::GetActiveCamera() const
        {
            return _active_camera;
        }

        NodePtr CScene::GetRootNode()
        {
            return _rootNode;
        }

        void CScene::Draw()
        {
            UpdateNodes(_rootNode);

            CORE::IVideoDriver * driver = CDevice::GetDevice()->GetVideoDriver();


            MATH::Matrix4f proj_matrix;
            MATH::Matrix4f pos_matrix;

            if( isNodeValid(_active_camera) )
            {
                proj_matrix = _active_camera->GetProjectionMatrix();
                pos_matrix = _active_camera->_global_matrix;
            }


            driver->PushMatrix(CORE::OMGL_MATRIX_PROJECTION);
            driver->MultMatrix(proj_matrix, CORE::OMGL_MATRIX_PROJECTION);

            driver->PushMatrix(CORE::OMGL_MATRIX_VIEW);
            driver->MultMatrix(pos_matrix, CORE::OMGL_MATRIX_VIEW);


            std::vector<CModelNode*>::iterator it;
            for(it=_list_model.begin(); it!=_list_model.end(); ++it)
            {
                if( !isNodeValid(*it) ) continue;

                driver->PushMatrix(CORE::OMGL_MATRIX_MODEL);
                driver->MultMatrix((*it)->_global_matrix, CORE::OMGL_MATRIX_MODEL);

                (*it)->Draw();

                driver->PopMatrix(CORE::OMGL_MATRIX_MODEL);
            }

            driver->PopMatrix(CORE::OMGL_MATRIX_VIEW);

            driver->PopMatrix(CORE::OMGL_MATRIX_PROJECTION);

        }

        //void CScene::UpdateNodes(NodePtr & node)
        void CScene::UpdateNodes(CNode * node)
        {
            if( node == 0 ) return;
            node->Update();

            if( node->_father != 0 )
            {
                MATH::Matrix4f matrix_parameter = node->GetRotation().GetMatrix4() * MATH::Matrix4f::CreateTranslation(node->GetPosition()) * MATH::Matrix4f::CreateScale(node->GetScale());
                //node->_global_matrix = node->_father->_global_matrix * node->_local_matrix;
                node->_global_matrix = matrix_parameter * node->_local_matrix * node->_father->_global_matrix;
            }
            else
            {
                node->_global_matrix = node->_local_matrix;
            }

            //std::vector<NodePtr> & list = node->GetListNodes();
            //std::vector<NodePtr>::iterator it;
            std::vector<CNode*> & list = node->GetListNodes();
            std::vector<CNode*>::iterator it;

            for(it=list.begin(); it!=list.end(); ++it)
            {
                UpdateNodes(*it);
            }
        }

        void CScene::RemoveStaticModelNode(CStaticModelNode * node)
        {
            std::vector<CModelNode*>::iterator it;
            for(it=_list_model.begin(); it!=_list_model.end(); ++it)
            {
                if( *it == node )
                {
                    _list_model.erase(it);
                    return;
                }
            }
        }

        // ---------------------------------------------------------------
        // Fonction récursive qui retourne vrai si le noeud passé en paramètre est correctement paramétré dans le graph
        // ---------------------------------------------------------------
        bool CScene::isNodeValid(CNode * node)
        {
            if( node == 0 ) return false;
            if( node == _rootNode ) return true;
            if( node->_father == 0) return false;
            return this->isNodeValid(node->_father);
        }
    }
}
