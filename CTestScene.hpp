#ifndef _DEF_CTESTSCENE_HPP
#define _DEF_CTESTSCENE_HPP

#include "IDemo.hpp"

#include "src/Omgl3D.hpp"
#include <SFML/Window.hpp>

class CTestScene : public IDemo
{

public:

	CTestScene();

	void init();

	void run();


private:

    int width_screen;
	int height_screen;


	OMGL3D::CDevice * device;
	OMGL3D::CORE::IVideoDriver * driver;



    /*
	OMGL3D::UTILS::ptr<OMGL3D::SCENE::CStaticModelNode>::SharedPtr node;
	OMGL3D::UTILS::ptr<OMGL3D::SCENE::CNode>::SharedPtr nodeCameraPivot;
	OMGL3D::UTILS::ptr<OMGL3D::SCENE::CCameraNode>::SharedPtr nodeCamera;
	OMGL3D::UTILS::ptr<OMGL3D::SCENE::CCameraNode>::SharedPtr nodeCameraSkybox;

    OMGL3D::UTILS::ptr<OMGL3D::SCENE::CStaticModelNode>::SharedPtr skybox;
	OMGL3D::UTILS::ptr<OMGL3D::CORE::ICubeMap>::ResourcePtr skybox_cube_map;
	*/
	OMGL3D::SCENE::CStaticModelNode * node;
	OMGL3D::SCENE::CNode * nodeCameraPivot;
	OMGL3D::SCENE::CCameraNode * nodeCamera;
	OMGL3D::SCENE::CCameraNode * nodeCameraSkybox;

    OMGL3D::SCENE::CStaticModelNode * skybox;
	OMGL3D::CORE::ICubeMap * skybox_cube_map;

	/*
	OMGL3D::SCENE::CStaticModelNode * node;
	OMGL3D::SCENE::CCameraNode * nodeCamera;

	OMGL3D::MODEL::IStaticModel * skybox;
	OMGL3D::CORE::ICubeMap * skybox_cube_map;
	*/


    OMGL3D::SCENE::CScene sceneSkyBox;
    OMGL3D::SCENE::CScene scene;

};

#endif
