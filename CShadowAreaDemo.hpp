#ifndef _DEF_CSHADOWAREADEMO_HPP
#define _DEF_CSHADOWAREADEMO_HPP

#include "IDemo.hpp"

#include <SFML/Window.hpp>
#include "src/Omgl3D.hpp"

#include <vector>

using namespace OMGL3D;
using namespace CORE;
using namespace UTILS;
using namespace MODEL;
using namespace MATH;

class CShadowAreaDemo : public IDemo
{
    public:

    CShadowAreaDemo();

    ~CShadowAreaDemo() {}

    void init();

    void yourEvent(float elapsedtime, const sf::Event & event);

    void run();


    void drawShadow();
    void drawTree(const Vector3f & pos);
    void drawTreeWithShadow(const Vector3f & pos);

    private:

    int width_screen, height_screen;

    OMGL3D::UTILS::ptr<OMGL3D::FONT::IFont>::ResourcePtr font;

	OMGL3D::UTILS::ptr<OMGL3D::CORE::ILight>::ResourcePtr light;

	OMGL3D::UTILS::ptr<OMGL3D::MODEL::IStaticModel>::ResourcePtr scene_model;
    OMGL3D::UTILS::ptr<OMGL3D::MODEL::IStaticModel>::ResourcePtr projecteur;
    OMGL3D::UTILS::ptr<OMGL3D::CORE::IMesh>::SharedPtr skybox;

    OMGL3D::UTILS::ptr<OMGL3D::CORE::IFrameBufferRender>::ResourcePtr frame_buffer;
    OMGL3D::UTILS::ptr<OMGL3D::CORE::IFrameBufferRender>::ResourcePtr frame_buffer2;
    OMGL3D::UTILS::ptr<OMGL3D::CORE::IFrameBufferRender>::ResourcePtr frame_buffer3;

    OMGL3D::UTILS::ptr<OMGL3D::CORE::IShader>::ResourcePtr shader;
    OMGL3D::UTILS::ptr<OMGL3D::CORE::IShader>::ResourcePtr shader_shadow;

    OMGL3D::UTILS::ptr<OMGL3D::CORE::ITexture>::ResourcePtr textureRock;
    OMGL3D::UTILS::ptr<OMGL3D::CORE::ITexture>::ResourcePtr textureRockNormal;
    OMGL3D::UTILS::ptr<OMGL3D::CORE::ITexture>::ResourcePtr textureRockHeight;

    OMGL3D::UTILS::ptr<OMGL3D::CORE::ICubeMap>::ResourcePtr skybox_cube_map;

    IVideoDriver * driver;

    ptr<IStaticModel>::ResourcePtr terrain;
    ptr<ITexture>::ResourcePtr textureGrass;


    ptr<IStaticModel>::ResourcePtr tronc;
    ptr<IStaticModel>::ResourcePtr feuilles;
    ptr<ITexture>::ResourcePtr textureTronc;
    ptr<ITexture>::ResourcePtr textureTroncNormale;
    ptr<ITexture>::ResourcePtr textureFeuille;

    std::vector<Vector3f> tree_position;


    Matrix4f proj_sun;
    float max_proj;
};

#endif
