#include "CNode.hpp"

#include "CCameraNode.hpp"
#include "CStaticModelNode.hpp"

#include "../Utils/Logger/ILogger.hpp"

namespace OMGL3D
{
    namespace SCENE
    {
        CNode::CNode(const std::string & name) : _name(name), _father(0), _scene(0), _scale(1, 1, 1)
        {
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_DEBUG) << "[" << UTILS::ILogger::GetCurrentDate() << " " << UTILS::ILogger::GetCurrentTime() << "] Scene : node created " << _name << UTILS::OMGL_LOGGER_FLUSH;
        }

        CNode::~CNode()
        {
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_DEBUG) << "[" << UTILS::ILogger::GetCurrentDate() << " " << UTILS::ILogger::GetCurrentTime() << "] Scene : node deleted " << _name << UTILS::OMGL_LOGGER_FLUSH;

            ClearNodes();
            Detach();
        }

        std::string CNode::GetName() const
        {
            return _name;
        }


        //void CNode::AddNode(UTILS::ptr<CNode>::SharedPtr & node)
        void CNode::AddNode(CNode * node)
        {
            if( node == 0 ) return;
            if( node->_father != 0 )
            {
                node->Detach();
            }

            _list_nodes.push_back(node);
            node->_father = this;
        }

        /*
        void CNode::AddNode(UTILS::ptr<CCameraNode>::SharedPtr & node)
        {
            if( node->_father != 0 )
            {
                node->Detach();
            }

            _list_nodes.push_back(static_cast<UTILS::ptr<CNode>::SharedPtr>(node));
            node->_father = this;
        }

        // ---------------------------------------------------------------
        // Ajoute un noeud fils de type StaticModelNode
        // ---------------------------------------------------------------
        void CNode::AddNode(UTILS::ptr<CStaticModelNode>::SharedPtr & node)
        {
            if( node->_father != 0 )
            {
                node->Detach();
            }

            _list_nodes.push_back(static_cast<UTILS::ptr<CNode>::SharedPtr>(node));
            node->_father = this;
        }
        */


        //UTILS::ptr<CNode>::SharedPtr CNode::GetNode(const std::string & name)
        CNode * CNode::GetNode(const std::string & name)
        {
            //std::vector<UTILS::ptr<CNode>::SharedPtr>::iterator it;
            ListNode::iterator it;
            for(it=_list_nodes.begin(); it!=_list_nodes.end(); ++it)
            {
                if( (*it)->GetName() == name )
                {
                    return *it;
                }
            }
            //return UTILS::ptr<CNode>::SharedPtr(0);
            return 0;
        }

        //std::vector<UTILS::ptr<CNode>::SharedPtr> & CNode::GetListNodes()
        std::vector<CNode*> & CNode::GetListNodes()
        {
            return _list_nodes;
        }

        void CNode::RemoveNode(const std::string & name)
        {
            ListNode::iterator it;
            for(it=_list_nodes.begin(); it!=_list_nodes.end(); ++it)
            {
                if( (*it)->GetName() == name )
                {
                    (*it)->_father = 0;
                    _list_nodes.erase(it);
                    return;
                }
            }
        }

        void CNode::ClearNodes()
        {
            ListNode::iterator it;
            for(it=_list_nodes.begin(); it!=_list_nodes.end(); ++it)
            {
                (*it)->_father = 0;
            }
            _list_nodes.clear();
        }

        CNode * CNode::GetFather()
        {
            return _father;
        }

        void CNode::Detach()
        {
            if( _father != 0)
            {
                _father->RemoveNode(_name);
            }
        }

        // ---------------------------------------------------------------
        // Définit la position du noeud
        // ---------------------------------------------------------------
        void CNode::SetPosition(const MATH::Vector3f & vector)
        {
            _position = vector;
        }

        // ---------------------------------------------------------------
        // Retourne la position du noeud
        // ---------------------------------------------------------------
        const MATH::Vector3f & CNode::GetPosition() const
        {
            return _position;
        }

        // ---------------------------------------------------------------
        // Définit la rotation du noeud
        // ---------------------------------------------------------------
        void CNode::SetRotation(const MATH::Quaternionf & quaternion)
        {
            _rotation = quaternion;
        }

        // ---------------------------------------------------------------
        // Retourne la rotation du noeud
        // ---------------------------------------------------------------
        const MATH::Quaternionf & CNode::GetRotation() const
        {
            return _rotation;
        }

        // ---------------------------------------------------------------
        // Définit la mise à l'échelle du noeud
        // ---------------------------------------------------------------
        void CNode::SetScale(const MATH::Vector3f & vector)
        {
            _scale = vector;
        }

        // ---------------------------------------------------------------
        // Retourne la mise à l'échelle du noeud
        // ---------------------------------------------------------------
        const MATH::Vector3f & CNode::GetScale() const
        {
            return _scale;
        }

        // ---------------------------------------------------------------
        // Crée une matrice globale de l'objet
        // ---------------------------------------------------------------
        MATH::Matrix4f CNode::CreateGlobalMatrix() const
        {
            if( _father ) {
                return _local_matrix * _father->CreateGlobalMatrix();
            }
            return _local_matrix;
        }

        MATH::Matrix4f CNode::GetMatrix() const
        {
            return _local_matrix;
        }

        void CNode::MultMatrix(const MATH::Matrix4f & matrix)
        {
            _local_matrix *= matrix;
        }

        void CNode::SetMatrix(const MATH::Matrix4f & matrix)
        {
            _local_matrix = matrix;
        }
    }
}
