#ifndef _DEF_OMEGLOND3D_CSENE_HPP
#define _DEF_OMEGLOND3D_CSENE_HPP

#include <string>

#include "CNode.hpp"

namespace OMGL3D
{
    namespace SCENE
    {
        class CModelNode;
        class CStaticModelNode;
        class CCameraNode;

        class CScene
        {

        public:

            // ---------------------------------------------------------------
            // Constructeur
            // ---------------------------------------------------------------
            CScene(const std::string & name);

            // ---------------------------------------------------------------
            // Destructeur
            // ---------------------------------------------------------------
            ~CScene();

            // ---------------------------------------------------------------
            // Crée un node pour cette scène et retourne son ponteur
            // ---------------------------------------------------------------
            CNode * CreateNode(const std::string & name);

            // ---------------------------------------------------------------
            //  Crée un node de type StaticMode pour cette scène et retourne son ponteur
            // ---------------------------------------------------------------
            CStaticModelNode * CreateStaticModelNode(const std::string & name);

            // ---------------------------------------------------------------
            // Crée une caméra pour cette scène et retourne son pointeur
            // ---------------------------------------------------------------
            CCameraNode * CreateCameraNode(const std::string & name);

            // ---------------------------------------------------------------
            // Définit la caméra active
            // ---------------------------------------------------------------
            //void SetActiveCamera(OMGL3D::UTILS::ptr<CCameraNode>::SharedPtr camera_node);
            void SetActiveCamera(CCameraNode * camera_node);

            // ---------------------------------------------------------------
            // Réinitialise le point de vue par défaut
            // ---------------------------------------------------------------
            void ResetActiveCamera();

            // ---------------------------------------------------------------
            // Retourne la caméra active
            // ---------------------------------------------------------------
            //OMGL3D::UTILS::ptr<CCameraNode>::SharedPtr GetActiveCamera();
            CCameraNode * GetActiveCamera() const;

            // ---------------------------------------------------------------
            // Retourne le noeud principal de la scène
            // ---------------------------------------------------------------
            NodePtr GetRootNode();

            // ---------------------------------------------------------------
            // Dessine la scène
            // ---------------------------------------------------------------
            void Draw();



        private:

            friend class CStaticModelNode;

            // ---------------------------------------------------------------
            // Fonction récursive de mise à jour de la position des nodes
            // ---------------------------------------------------------------
            //void UpdateNodes(NodePtr & node);
            void UpdateNodes(CNode * node);

            // ---------------------------------------------------------------
            // Retire un StaticModelNode de la liste d'affichage
            // ---------------------------------------------------------------
            void RemoveStaticModelNode(CStaticModelNode * node);

            // ---------------------------------------------------------------
            // Fonction récursive qui retourne vrai si le noeud passé en paramètre est correctement paramétré dans le graph
            // ---------------------------------------------------------------
            bool isNodeValid(CNode * node);



            std::string _name;

            // OMGL3D::UTILS::ptr<CCameraNode>::SharedPtr _active_camera;
            CCameraNode * _active_camera;

            NodePtr _rootNode;

            std::vector<CModelNode*> _list_model;
        };
    }
}

#endif
