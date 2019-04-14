#include "CVideoDriver.hpp"


#include "CMediaManager.hpp"
#include "CPicture.hpp"
#include "CResourceManager.hpp"
#include "ICubeMap.hpp"
#include "ILight.hpp"
#include "IShader.hpp"
#include "IShaderBase.hpp"
#include "ITexture.hpp"

#include "../Debug/DebugAllocation.hpp"

#include "../Exception/PointerNullException.hpp"
#include "../Exception/ReadException.hpp"
#include "../Exception/LoadException.hpp"

#include "../Font/IFont.hpp"

#include "../Model/CStaticModel.hpp"

#include "../Utils/Prefab/CCube.hpp"
#include "../Utils/Prefab/CSquare.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        CVideoDriver::CVideoDriver()
        {
        }

        CVideoDriver::~CVideoDriver()
        {
        }

        void CVideoDriver::AddFilePath(const std::string & path)
        {
            CMediaManager::GetInstance().AddFilePath(path);
        }

        ITexture * CVideoDriver::GetTexture(const std::string &name, bool mipmap) throw(EXCP::OMGLException)
        {
            ITexture * texture = 0;
            try {
                texture = CResourceManager::GetInstance().GetResource<ITexture>(name);

            } catch( EXCP::PointerNullException &e ) {
                UTILS::ptr<CPicture>::SharedPtr picture = CMediaManager::GetInstance().LoadFromFile<CPicture>(name);
                texture = this->CreateTexture(*picture, mipmap);
                CResourceManager::GetInstance().AddResource(name, texture);
            }
            return texture;
        }

        ITexture * CVideoDriver::GetTexture(const std::string &name, const std::string * images, std::size_t size) throw(EXCP::OMGLException)
        {
            ITexture * texture = 0;
            try {
                texture = CResourceManager::GetInstance().GetResource<ITexture>(name);
            } catch(EXCP::PointerNullException &e) {


                std::vector<CPicture> pictures;

                for(unsigned int index=0; index<size; ++index)
                {
                    CPicture * p = CMediaManager::GetInstance().LoadFromFile<CPicture>(images[index]);
                    pictures.push_back(*p);
                    delete p;
                }

                texture = this->CreateTexture(name, &pictures[0], size);


            }
            return texture;
        }

        ICubeMap * CVideoDriver::GetCubeMap(const std::string & name)
        {
            ICubeMap * cubeMap = 0;

            try {
                cubeMap = CResourceManager::GetInstance().GetResource<ICubeMap>(name);
            } catch(EXCP::PointerNullException & e)  {
                cubeMap = this->CreateCubeMap(name);
                CResourceManager::GetInstance().AddResource(name, cubeMap);
            }

            return cubeMap;
        }

        FONT::IFont * CVideoDriver::GetFont(const std::string & font_name, int size, bool bold, bool italic)
        {
            FONT::IFont * font = 0;
            try {
                font = CResourceManager::GetInstance().GetResource<FONT::IFont>(font_name);
            } catch(EXCP::PointerNullException & e) {
                font = this->CreateSystemFont(font_name, size, bold, italic);
                CResourceManager::GetInstance().AddResource(font_name, font);
            }
            return font;
        }

        MODEL::IStaticModel * CVideoDriver::GetStaticModel(const std::string & name)
        {
            MODEL::IStaticModel * model = 0;
            try {
                model = CResourceManager::GetInstance().GetResource<MODEL::IStaticModel>(name);
            } catch(EXCP::PointerNullException & e) {
                model = new MODEL::CStaticModel(name);

                {
                    OMGL3D::UTILS::ptr<OMGL3D::MODEL::IStaticModel>::ResourcePtr model_temp = OMGL3D::CORE::CMediaManager::GetInstance().LoadFromFile<MODEL::IStaticModel>(name);
                    OMGL3D::CORE::CResourceManager::GetInstance().AddResource("omgl_StaticModelLoading", model_temp);

                    std::vector<UTILS::ptr<CORE::IMesh>::SharedPtr> all_meshes = model_temp->GetAllMeshes();

                    std::vector<UTILS::ptr<CORE::IMesh>::SharedPtr>::const_iterator it;
                    for(it=all_meshes.begin(); it!=all_meshes.end(); ++it)
                    {
                        OMGL3D::UTILS::ptr<OMGL3D::CORE::IMesh>::SharedPtr mesh = (*it).GetPtr()->Copy("omgl_mesh_copy_loading");
                        model->AddMesh(mesh);
                    }
                }

                CResourceManager::GetInstance().AddResource(name, model);
            }
            return model;
        }

        MODEL::IStaticModel * CVideoDriver::GetPrefabSquare()
        {
            MODEL::IStaticModel * model = 0;
            try {
                model = CResourceManager::GetInstance().GetResource<MODEL::IStaticModel>("omgl_prefab_square");
            } catch(EXCP::PointerNullException & e) {
                model = new UTILS::CSquare();
                CResourceManager::GetInstance().AddResource("omgl_prefab_square", model);
            }
            return model;
        }

        MODEL::IStaticModel * CVideoDriver::GetPrefabCube()
        {
            MODEL::IStaticModel * model = 0;
            try {
                model = CResourceManager::GetInstance().GetResource<MODEL::IStaticModel>("omgl_prefab_cube");
            } catch(EXCP::PointerNullException & e) {
                model = new UTILS::CCube();
                CResourceManager::GetInstance().AddResource("omgl_prefab_cube", model);
            }
            return model;
        }

        IFrameBufferRender * CVideoDriver::GetFrameBufferRender(const std::string & name)
        {
            IFrameBufferRender * frame_buffer = 0;
            frame_buffer = CResourceManager::GetInstance().GetResource<IFrameBufferRender>(name);
            return frame_buffer;
        }

        IFrameBufferRender * CVideoDriver::GetFrameBufferRender(const std::string & name, int width, int height)
        {
            IFrameBufferRender * frame_buffer = 0;
            try {
                frame_buffer = CResourceManager::GetInstance().GetResource<IFrameBufferRender>(name);
            } catch(EXCP::PointerNullException & e) {
                frame_buffer = this->CreateFrameBufferRender(name, width, height);
                CResourceManager::GetInstance().AddResource(name, frame_buffer);

                ITexture * color_texture = this->CreateEmptyTexture("colortexture_"+name, width, height, OMGL_COLOR_BUFFER_RGB);
                ITexture * depth_texture = this->CreateEmptyTexture("depthtexture_"+name, width, height, OMGL_COLOR_BUFFER_DEPTH);
                frame_buffer->SetTexture(color_texture, depth_texture);
                CResourceManager::GetInstance().AddResource("colortexture_"+name, color_texture);
                CResourceManager::GetInstance().AddResource("depthtexture_"+name, depth_texture);
            }
            return frame_buffer;
        }

        IShader * CVideoDriver::GetShader(const std::string & name, const std::string & vertex_file, const std::string & pixel_file)
        {
            IShader * shader = 0;

            try {
                shader = CResourceManager::GetInstance().GetResource<IShader>(name);
            } catch(EXCP::PointerNullException & e) {
                UTILS::CFileReader fileReader;
                IShaderBase * vertexshader = 0;
                IShaderBase * pixelshader = 0;

                try {
                    vertexshader = CResourceManager::GetInstance().GetResource<IShaderBase>(vertex_file);
                } catch(EXCP::PointerNullException & e_shader) {
                    vertexshader = this->CreateShaderProgramGLSL(vertex_file, OMGL_SHADERTYPE_VERTEX);
                    char * src = OMGL3D::CORE::CMediaManager::GetInstance().LoadFromFile<char>(vertex_file);
                    vertexshader->SetSource(src);
                    delete[] src;
                    vertexshader->Compile();

                    CResourceManager::GetInstance().AddResource(vertex_file, vertexshader);
                }

                try {
                    pixelshader = CResourceManager::GetInstance().GetResource<IShaderBase>(pixel_file);
                } catch(EXCP::PointerNullException & e_shader) {
                    pixelshader = this->CreateShaderProgramGLSL(pixel_file, OMGL_SHADERTYPE_PIXEL);
                    char * src = OMGL3D::CORE::CMediaManager::GetInstance().LoadFromFile<char>(pixel_file);
                    pixelshader->SetSource(src);
                    delete[] src;
                    pixelshader->Compile();

                    CResourceManager::GetInstance().AddResource(pixel_file, pixelshader);
                }

                shader = this->CreateShaderGLSL(name, vertexshader, pixelshader);
                CResourceManager::GetInstance().AddResource(name, shader);
            }

            return shader;
        }

        ILight * CVideoDriver::GetLight(const std::string & name)
        {
            ILight * light = 0;
            try {
                light = CResourceManager::GetInstance().GetResource<ILight>(name);
            } catch(EXCP::PointerNullException & e) {
                light = CreateLight(name);
                CResourceManager::GetInstance().AddResource(name, light);
            }
            return light;
        }

    }
}
