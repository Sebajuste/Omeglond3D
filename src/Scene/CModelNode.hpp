#ifndef _DEF_OMEGLOND3D_CMODELNODE_HPP
#define _DEF_OMEGLOND3D_CMODELNODE_HPP

#include "CNode.hpp"

#include "../Utils/Ptr/SmartPtr.hpp"

namespace OMGL3D
{
    namespace CORE {
        class ICubeMap;
        class ITexture;
        class IShader;
    }

    namespace SCENE
    {
        struct TextureStatement
        {
            UTILS::ptr<CORE::ITexture>::ResourcePtr texture;
            UTILS::ptr<CORE::ICubeMap>::ResourcePtr cubeMap;
            MATH::Matrix4f matrix;
            unsigned int index_mesh;
        };

        class CModelNode : public CNode
        {

        public:

            CModelNode(const std::string & name);

            virtual ~CModelNode();

            void SetProjectShadow(bool project_shadow);

            bool IsProjectShadow() const;

            void SetReceiveShadow(bool receive_shadow);

            bool IsReceiveShadow() const;

            void AddTextureStatement(const TextureStatement & texture_statement);

            std::vector<TextureStatement> & GetListTextureStatement();

            void SetShader(CORE::IShader * shader);

            CORE::IShader * GetShader();

            virtual void Draw() { }


        protected:

            bool _project_shadow, _receive_shadow;

            std::vector<TextureStatement> _list_texture_statement;

            UTILS::ptr<CORE::IShader>::ResourcePtr _shader;
        };

        typedef UTILS::ptr<CModelNode>::SharedPtr ModelNodePtr;
    }
}

#endif
