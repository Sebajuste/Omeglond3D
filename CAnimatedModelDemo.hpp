#ifndef _DEF_CANIMATEDMODELDEMO_HPP
#define _DEF_CANIMATEDMODELDEMO_HPP

#include "IDemo.hpp"

using namespace OMGL3D;
using namespace CORE;
using namespace FONT;
using namespace MATH;
using namespace MODEL;
using namespace UI;
using namespace UTILS;

class CAnimatedModelDemo : public IDemo
{
    public:

    CAnimatedModelDemo();

    ~CAnimatedModelDemo() {}

    void init();

    void yourEvent(float elapsedtime, const sf::Event & event);

    void run();

    private:

    OMGL3D::CORE::IVideoDriver * driver;

    OMGL3D::UI::MouseEvent omgl_event;

    OMGL3D::SCENE::CScene _scene;
    OMGL3D::UTILS::ptr<OMGL3D::SCENE::CStaticModelNode>::SharedPtr model_node;
    OMGL3D::UTILS::ptr<OMGL3D::SCENE::CCameraNode>::SharedPtr camera;

    ptr<IStaticModel>::ResourcePtr scene_model;
    ptr<ITexture>::ResourcePtr textureRock;

};

#endif
