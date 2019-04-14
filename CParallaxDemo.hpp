#ifndef _DEF_CPARALLAXDEMO_HPP
#define _DEF_CPARALLAXDEMO_HPP

#include "IDemo.hpp"

#include "src/Omgl3D.hpp"
#include <SFML/Window.hpp>

class CParallaxDemo : public IDemo
{
	public:

	CParallaxDemo();

    ~CParallaxDemo() { }

	void init();

	void run();



	private:

	int width_screen;
	int height_screen;


	OMGL3D::CDevice * device;
	OMGL3D::CORE::IVideoDriver * driver;

	OMGL3D::UTILS::ptr<OMGL3D::FONT::IFont>::ResourcePtr font;

	OMGL3D::UTILS::ptr<OMGL3D::CORE::ILight>::ResourcePtr light;

	OMGL3D::UTILS::ptr<OMGL3D::MODEL::IStaticModel>::ResourcePtr scene_model;
    OMGL3D::UTILS::ptr<OMGL3D::MODEL::IStaticModel>::ResourcePtr projecteur;
    //OMGL3D::UTILS::ptr<OMGL3D::CORE::IMesh>::SharedPtr skybox;
    OMGL3D::UTILS::ptr<OMGL3D::MODEL::IStaticModel>::ResourcePtr skybox;

    OMGL3D::UTILS::ptr<OMGL3D::CORE::IFrameBufferRender>::ResourcePtr frame_buffer;

    OMGL3D::UTILS::ptr<OMGL3D::CORE::IShader>::ResourcePtr shader;
    OMGL3D::UTILS::ptr<OMGL3D::CORE::IShader>::ResourcePtr shader_shadow;

    OMGL3D::UTILS::ptr<OMGL3D::CORE::ITexture>::ResourcePtr textureRock;
    OMGL3D::UTILS::ptr<OMGL3D::CORE::ITexture>::ResourcePtr textureRockNormal;
    OMGL3D::UTILS::ptr<OMGL3D::CORE::ITexture>::ResourcePtr textureRockHeight;

    OMGL3D::UTILS::ptr<OMGL3D::MODEL::IStaticModel>::ResourcePtr tronc;
    OMGL3D::UTILS::ptr<OMGL3D::MODEL::IStaticModel>::ResourcePtr feuilles;
    OMGL3D::UTILS::ptr<OMGL3D::CORE::ITexture>::ResourcePtr textureTronc;
    OMGL3D::UTILS::ptr<OMGL3D::CORE::ITexture>::ResourcePtr textureFeuilles;

    OMGL3D::UTILS::ptr<OMGL3D::CORE::ICubeMap>::ResourcePtr skybox_cube_map;

    //OMGL3D::UTILS::ptr<OMGL3D::UI::CFrame>::SharedPtr frame;
};

#endif
