#include "CStaticModelNode.hpp"

#include "../Core/ICubeMap.hpp"
#include "../Core/ITexture.hpp"
#include "../Model/IStaticModel.hpp"

#include "CScene.hpp"

namespace OMGL3D
{
    namespace SCENE
    {
        CStaticModelNode::CStaticModelNode(const std::string & name) : CModelNode(name)
        {
        }

        CStaticModelNode::~CStaticModelNode()
        {
            _scene->RemoveStaticModelNode(this);
        }

        void CStaticModelNode::SetStaticModel(MODEL::IStaticModel * model)
        {
            _model = model;
        }

        MODEL::IStaticModel * CStaticModelNode::GetStaticModel()
        {
            return _model;
        }

        void CStaticModelNode::Draw()
        {
            std::vector<TextureStatement>::iterator it_texstate;

            unsigned int index_tex = 0;
            for(it_texstate=_list_texture_statement.begin(); it_texstate!=_list_texture_statement.end(); ++it_texstate)
            {
                if( (*it_texstate).texture ) {
                    (*it_texstate).texture->Enable(index_tex);
                }
                if( (*it_texstate).cubeMap ) {
                    (*it_texstate).cubeMap->Enable(index_tex);
                }
                index_tex++;
            }

            _model->Draw();

            index_tex = 0;
            for(it_texstate=_list_texture_statement.begin(); it_texstate!=_list_texture_statement.end(); ++it_texstate)
            {
                if( (*it_texstate).texture ) {
                    (*it_texstate).texture->Disable(index_tex);
                }
                if( (*it_texstate).cubeMap ) {
                    (*it_texstate).cubeMap->Disable(index_tex);
                }
                index_tex++;
            }
        }
    }
}
