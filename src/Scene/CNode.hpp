#ifndef _DEF_OMEGLOND3D_CNODE_HPP
#define _DEF_OMEGLOND3D_CNODE_HPP

#include "../Math/Matrix4.hpp"
#include "../Math/Vector3.hpp"
#include "../Math/Quaternion.hpp"
#include "../Utils/Ptr/SmartPtr.hpp"

#include <string>
#include <vector>

namespace OMGL3D
{
    namespace SCENE
    {
        class CScene;

        class CCameraNode;
        class CStaticModelNode;

        class CNode
        {

        public:

            CNode(const std::string & name);

            // ---------------------------------------------------------------
            // détruit les noeud fils, et demande au père de le supprimer
            // ---------------------------------------------------------------
            virtual ~CNode();

            // ---------------------------------------------------------------
            // retourne le nom du node
            // ---------------------------------------------------------------
            std::string GetName() const;

            // ---------------------------------------------------------------
            // Ajoute un noeud fils
            // ---------------------------------------------------------------
            //void AddNode(UTILS::ptr<CNode>::SharedPtr & node);
            void AddNode(CNode * node);

            // ---------------------------------------------------------------
            // Ajoute un noeud fils de type Caméra
            // ---------------------------------------------------------------
            //void AddNode(UTILS::ptr<CCameraNode>::SharedPtr & node);

            // ---------------------------------------------------------------
            // Ajoute un noeud fils de type StaticModelNode
            // ---------------------------------------------------------------
            //void AddNode(UTILS::ptr<CStaticModelNode>::SharedPtr & node);


            // ---------------------------------------------------------------
            // Retourne le node dont le nom est passé en paramètre
            // ---------------------------------------------------------------
            //UTILS::ptr<CNode>::SharedPtr GetNode(const std::string & name);
            CNode * GetNode(const std::string & name);

            // ---------------------------------------------------------------
            // Retourne la liste des node
            // ---------------------------------------------------------------
            //std::vector<UTILS::ptr<CNode>::SharedPtr> & GetListNodes();
            std::vector<CNode*> & GetListNodes();

            // ---------------------------------------------------------------
            // Supprime des fils le nom dont le nom est passé en paramètre
            // ---------------------------------------------------------------
            void RemoveNode(const std::string & name);

            // ---------------------------------------------------------------
            // Supprime tous les noeud fils
            // ---------------------------------------------------------------
            void ClearNodes();

            // ---------------------------------------------------------------
            // Retourne le noeud du père
            // ---------------------------------------------------------------
            CNode * GetFather();

            // ---------------------------------------------------------------
            // Demande au père de le tuer
            // ---------------------------------------------------------------
            void Detach();

            // ---------------------------------------------------------------
            // Définit la position du noeud
            // ---------------------------------------------------------------
            void SetPosition(const MATH::Vector3f & vector);

            // ---------------------------------------------------------------
            // Retourne la position du noeud
            // ---------------------------------------------------------------
            const MATH::Vector3f & GetPosition() const;

            // ---------------------------------------------------------------
            // Définit la rotation du noeud
            // ---------------------------------------------------------------
            void SetRotation(const MATH::Quaternionf & quaternion);

            // ---------------------------------------------------------------
            // Retourne la rotation du noeud
            // ---------------------------------------------------------------
            const MATH::Quaternionf & GetRotation() const;

            // ---------------------------------------------------------------
            // Définit la mise à l'échelle du noeud
            // ---------------------------------------------------------------
            void SetScale(const MATH::Vector3f & vector);

            // ---------------------------------------------------------------
            // Retourne la mise à l'échelle du noeud
            // ---------------------------------------------------------------
            const MATH::Vector3f & GetScale() const;

            // ---------------------------------------------------------------
            // Crée une matrice globale de l'objet
            // ---------------------------------------------------------------
            MATH::Matrix4f CreateGlobalMatrix() const;

            // ---------------------------------------------------------------
            // Retourne la matrice locale
            // ---------------------------------------------------------------
            MATH::Matrix4f GetMatrix() const;

            // ---------------------------------------------------------------
            // Multiplie la matrice locale par la matrice passée en paramètre
            // ---------------------------------------------------------------
            void MultMatrix(const MATH::Matrix4f & matrix);

            // ---------------------------------------------------------------
            // Remplace la matrice locale par la matrice passée en paramètre
            // ---------------------------------------------------------------
            void SetMatrix(const MATH::Matrix4f & matrix);

            // ---------------------------------------------------------------
            // Met à jour ce node
            // ---------------------------------------------------------------
            virtual void Update() { }



        protected:

            friend class CScene;

            std::string _name;

            CNode * _father;

            CScene * _scene;

            MATH::Vector3f _position, _scale;
            MATH::Quaternionf _rotation;

            MATH::Matrix4f _local_matrix, _global_matrix;

            typedef std::vector<CNode*> ListNode;
            //typedef std::vector<UTILS::ptr<CNode>::SharedPtr> ListNode;

            ListNode _list_nodes;

        };

        typedef UTILS::ptr<CNode>::SharedPtr NodePtr;

    }
}

#endif
