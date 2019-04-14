#include "CTowerDemo.hpp"

using namespace OMGL3D;
using namespace CORE;
using namespace MATH;

CTowerDemo::CTowerDemo()
{
}

void CTowerDemo::init()
{
    window.Create(sf::VideoMode(800, 600, 32), "Omeglond3D v2");

    #ifdef WIN32
        OMGL3D::CDevice * device = OMGL3D::CDevice::CreateDevice(800, 600, OMGL3D::OMGL_OPENGL2);
    #else
        OMGL3D::CDevice * device = OMGL3D::CDevice::CreateDevice(800, 600, "./bin/Release/linux/libOGLRender.so");
    #endif

    driver = device->GetVideoDriver();

    #ifdef WIN32
        font = driver->GetFont("Verdana");
    #else
        font = driver->GetFont("-adobe-helvetica-medium-r-*-*-12-*-*-*-*-*-*-*");
    #endif


    // Paramétrage des acces aux ressources
    driver->AddFilePath("./files/textures/");
    driver->AddFilePath("./files/models/");
    driver->AddFilePath("./files/shaders/");

    light = driver->GetLight("sun");

    light->SetType(OMGL_LIGHT_INFINITE);


    tower = driver->GetStaticModel("gard_tower.obj");

    textureTower = driver->GetTexture("tower_diffuse_map.tga");
    textureTowerNormal = driver->GetTexture("tower_normal_map.tga");

    shader = driver->GetShader("bump_mapping", "bump.vert", "bump.frag");
    shader->SetParameter("colorMap", 0);
    shader->SetParameter("normalMap", 1);
}

void CTowerDemo::run()
{

    sf::Clock clock;

    float angle = 0;

    bool run = true;
    while( run )
    {
        float elapsedtime = clock.GetElapsedTime();
        clock.Reset();

        angle += 10 * elapsedtime;

        // Gestion des évènement pour fermer l'applicaton
        sf::Event event;

        while(window.GetEvent(event))
        {
            switch(event.Type)
            {
                case sf::Event::Closed:
                    run = false;
                    break;

                case sf::Event::KeyPressed:
                {
                    if( event.Key.Code == sf::Key::Escape )
                {
                    run = false;
                }
                    break;
                }

                default:
                    break;
            }
        }

        driver->Begin();

        driver->PushMatrix(OMGL_MATRIX_PROJECTION);
        driver->MultMatrix(Matrix4f::CreatePerspectiveMatrix(90, 800/600, 0.1, 100), OMGL_MATRIX_PROJECTION);

        driver->PushMatrix(OMGL_MATRIX_VIEW);
        driver->MultMatrix(Matrix4f::CreateLookAtMatrix(10,5,0, 0,0,0, 0,1,0), OMGL_MATRIX_VIEW);
        driver->MultMatrix(Matrix4f::CreateRotationY(angle), OMGL_MATRIX_VIEW);


        shader->Enable();
        textureTower->Enable(0);
        textureTowerNormal->Enable(1);
        tower->Draw();
        textureTower->Disable(0);
        textureTowerNormal->Disable(1);
        shader->Disable();


        driver->PopMatrix(OMGL_MATRIX_VIEW);



        driver->PopMatrix(OMGL_MATRIX_PROJECTION);


        driver->End();

        window.Display();
    }

}
