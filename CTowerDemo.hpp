#ifndef _DEF_CTOWERDEMO_HPP
#define _DEF_CTOWERDEMO_HPP

#include "IDemo.hpp"

#include "src/Omgl3D.hpp"
#include <SFML/Window.hpp>

class CTowerDemo : public IDemo
{
	public:

	CTowerDemo();

    ~CTowerDemo() { }

	void init();

	void run();



	private:

	int width_screen;
	int height_screen;

	sf::Window window;
	OMGL3D::CDevice * device;
	OMGL3D::CORE::IVideoDriver * driver;

	OMGL3D::UTILS::ptr<OMGL3D::FONT::IFont>::ResourcePtr font;

	OMGL3D::UTILS::ptr<OMGL3D::CORE::ILight>::ResourcePtr light;

	OMGL3D::UTILS::ptr<OMGL3D::MODEL::IStaticModel>::ResourcePtr tower;

    OMGL3D::UTILS::ptr<OMGL3D::CORE::IFrameBufferRender>::ResourcePtr frame_buffer;

    OMGL3D::UTILS::ptr<OMGL3D::CORE::IShader>::ResourcePtr shader;
    OMGL3D::UTILS::ptr<OMGL3D::CORE::IShader>::ResourcePtr shader_shadow;

    OMGL3D::UTILS::ptr<OMGL3D::CORE::ITexture>::ResourcePtr textureTower;
    OMGL3D::UTILS::ptr<OMGL3D::CORE::ITexture>::ResourcePtr textureTowerNormal;

};

#endif

