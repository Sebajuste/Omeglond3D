#include "CModelNode.hpp"

#include "../Core/IShader.hpp"
#include "../Core/ITexture.hpp"
#include "../Core/ICubeMap.hpp"

namespace OMGL3D
{
    namespace SCENE
    {
        CModelNode::CModelNode(const std::string & name) : CNode(name), _project_shadow(false), _receive_shadow(false)
        {
        }

        CModelNode::~CModelNode()
        {
        }

        void CModelNode::SetProjectShadow(bool project_shadow)
        {
            _project_shadow = project_shadow;
        }

        bool CModelNode::IsProjectShadow() const
        {
            return _project_shadow;
        }

        void CModelNode::SetReceiveShadow(bool receive_shadow)
        {
            _receive_shadow = receive_shadow;
        }

        bool CModelNode::IsReceiveShadow() const
        {
            return _receive_shadow;
        }

        void CModelNode::AddTextureStatement(const TextureStatement & texture_statement)
        {
            _list_texture_statement.push_back(texture_statement);
        }

        std::vector<TextureStatement> & CModelNode::GetListTextureStatement()
        {
            return _list_texture_statement;
        }

        void CModelNode::SetShader(CORE::IShader * shader)
        {
            _shader = shader;
        }

        CORE::IShader * CModelNode::GetShader()
        {
            return _shader;
        }
    }
}
