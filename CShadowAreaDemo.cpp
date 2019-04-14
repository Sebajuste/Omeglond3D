#include "CShadowAreaDemo.hpp"

#include <sstream>
#include <iostream>

CShadowAreaDemo::CShadowAreaDemo()
{
    width_screen = 800;
    height_screen = 600;

    tree_position.push_back(Vector3f(122, 75, 95));
    tree_position.push_back(Vector3f(140, 50, 140));

    tree_position.push_back(Vector3f(23, 9, 60));
    tree_position.push_back(Vector3f(35, 9, 59));
    tree_position.push_back(Vector3f(27, 7, 64));
    tree_position.push_back(Vector3f(15, 8, 79));
    tree_position.push_back(Vector3f(13, 10, 73));
    tree_position.push_back(Vector3f(4, 12, 57));
    tree_position.push_back(Vector3f(8, 15, 49));

    tree_position.push_back(Vector3f(-38, 58, -83));
    tree_position.push_back(Vector3f(-37, 54, -91));
    tree_position.push_back(Vector3f(-27, 56, -83));
    tree_position.push_back(Vector3f(-30, 60, -69));
    tree_position.push_back(Vector3f(-26, 46, -92));
    tree_position.push_back(Vector3f(-12, 53, -63));
}

void CShadowAreaDemo::init()
{
    window.Create(sf::VideoMode(width_screen, height_screen, 32), "Omeglond3D v2");

    #ifdef WIN32
        OMGL3D::CDevice * device = OMGL3D::CDevice::CreateDevice(width_screen, height_screen, OMGL3D::OMGL_OPENGL2);
    #else
        OMGL3D::CDevice * device = OMGL3D::CDevice::CreateDevice(width_screen, height_screen, "./bin/Release/linux/libOGLRender.so");
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

    scene_model = driver->GetStaticModel("scene.obj");
    projecteur = driver->GetStaticModel("projecteur.obj");
    tronc = driver->GetStaticModel("tree_tronc.obj");
    feuilles = driver->GetStaticModel("tree_leaf.obj");
    terrain = driver->GetStaticModel("terrain.obj");

    textureRock = driver->GetTexture("rock_color.tga");
    textureTronc = driver->GetTexture("tronc_color_map.tga");
    textureFeuille = driver->GetTexture("tree_alpha_leaf.tga");
    textureGrass = driver->GetTexture("grass.tga");

    frame_buffer = driver->GetFrameBufferRender("FBO_light_depthmap", 512, 512);
    frame_buffer2 = driver->GetFrameBufferRender("FBO_light_depthmap2", 512, 512);
    frame_buffer3 = driver->GetFrameBufferRender("FBO_light_depthmap3", 512, 512);

    ITexture * depth_texture = frame_buffer->GetDepthTexture();
    ITexture * depth_texture2 = frame_buffer2->GetDepthTexture();
    ITexture * depth_texture3 = frame_buffer3->GetDepthTexture();

    OMGL3D::CORE::TexCoordPlane texcoord[] = {
        {1.0, 0.0, 0.0, 0.0, OMGL3D::CORE::OMGL_TEXCOORD_LINEAR},
        {0.0, 1.0, 0.0, 0.0, OMGL3D::CORE::OMGL_TEXCOORD_LINEAR},
        {0.0, 0.0, 1.0, 0.0, OMGL3D::CORE::OMGL_TEXCOORD_LINEAR},
        {0.0, 0.0, 0.0, 1.0, OMGL3D::CORE::OMGL_TEXCOORD_LINEAR}
    };

    depth_texture->GenerateTexCoord(0, texcoord);
    depth_texture2->GenerateTexCoord(0, texcoord);
    depth_texture3->GenerateTexCoord(0, texcoord);


    shader_shadow = driver->GetShader("split-shadow-mapping", "shadow_split.vert", "shadow_split.frag");
    shader_shadow->SetParameter("shadowMap0", 0);
    shader_shadow->SetParameter("shadowMap1", 1);
    shader_shadow->SetParameter("shadowMap2", 2);
    //shader_shadow = driver->getShader("shadow-mapping", "shadow.vert", "shadow.frag");
    //shader_shadow->setParameter("shadowMap", 0);

}

void CShadowAreaDemo::yourEvent(float elapsedtime, const sf::Event & event)
{

            if( event.Type == sf::Event::KeyPressed )
            {
                if( event.Key.Code == sf::Key::F2 )
                {
                    proj_sun = OMGL3D::MATH::Matrix4f::CreatePerspectiveMatrix(130.0f, 1, 200.0f, max_proj++);
                }
                if( event.Key.Code == sf::Key::F1 )
                {
                    proj_sun = OMGL3D::MATH::Matrix4f::CreatePerspectiveMatrix(130.0f, 1, 200.0f, max_proj--);
                }
            }

}

void CShadowAreaDemo::run()
{
    OMGL3D::MATH::Matrix4f identity;

    Matrix4f proj_2d = OMGL3D::MATH::Matrix4f::CreateOrthoMatrix(0, width_screen, 0, height_screen, -1, 1);

    //Matrix4f pos_sun = OMGL3D::MATH::Matrix4f::createLookAtMatrix(5,10,5,  0,0,0,  0,1,0).inverse();
    //Matrix4f pos_sun = OMGL3D::MATH::Matrix4f::createLookAtMatrix(45,90,45,  0,0,0,  0,1,0).inverse();
    Matrix4f pos_sun = OMGL3D::MATH::Matrix4f::CreateLookAtMatrix(140,200,150,  0,0,0,  0,1,0).GetInverse();
    //Matrix4f pos_sun = OMGL3D::MATH::Matrix4f::createLookAtMatrix(103,93,123,  0,0,0,  0,1,0).inverse();
    //Matrix4f pos_sun = OMGL3D::MATH::Matrix4f::createLookAtMatrix(10,20,10,  0,0,0,  0,1,0).inverse();
    //Matrix4f pos_sun = OMGL3D::MATH::Matrix4f::createLookAtMatrix(12,19,73,  23,9,60,  0,1,0).inverse();
    Matrix4f proj_sun = OMGL3D::MATH::Matrix4f::CreatePerspectiveMatrix(130.0f, 1, 100.0f, 200.0f);
    Matrix4f proj_sun2 = OMGL3D::MATH::Matrix4f::CreatePerspectiveMatrix(130.0f, 1, 200.0f, 300.0f);
    Matrix4f proj_sun3 = OMGL3D::MATH::Matrix4f::CreatePerspectiveMatrix(130.0f, 1, 300.0f, 400.0f);

    position = Matrix4f::CreateTranslation(10, 20, 80);

    Matrix4f proj_view = OMGL3D::MATH::Matrix4f::CreatePerspectiveMatrix(70.0f, (double)width_screen/height_screen, 0.1f, 1000.0f);

    Matrix4f pos_model = Matrix4f::CreateTranslation(23, 9, 60);

    IDepthBuffer * depthBuffer = driver->GetDepthBuffer();

    sf::Clock clock;

    float move = 0.0;

    float max_proj=220;

    while ( running )
    {
        float elapsedtime = clock.GetElapsedTime();
        float framerate = 1.0f / elapsedtime;
        clock.Reset();

        events(elapsedtime);



        move += elapsedtime;

        driver->Begin();

        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_PROJECTION);
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_MODEL);
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_VIEW);
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_TEXTURE);

std::vector<Vector3f>::iterator it;


        //pos_sun *= Matrix4f::createTranslation(0, 0, elapsedtime);

        /// Dessin de l'ombre dans le buffer

        driver->PushMatrix(OMGL_MATRIX_VIEW);
        driver->MultMatrix(pos_sun, OMGL_MATRIX_VIEW);

        driver->PushMatrix(OMGL_MATRIX_PROJECTION);
        driver->MultMatrix(proj_sun, OMGL_MATRIX_PROJECTION);
        depthBuffer->Clear();
        frame_buffer->Clear();
        frame_buffer->Enable();
        drawShadow();
        frame_buffer->Disable();
        driver->PopMatrix(OMGL_MATRIX_PROJECTION);

        driver->PushMatrix(OMGL_MATRIX_PROJECTION);
        driver->MultMatrix(proj_sun2, OMGL_MATRIX_PROJECTION);
        depthBuffer->Clear();
        frame_buffer2->Clear();
        frame_buffer2->Enable();
        drawShadow();
        frame_buffer2->Disable();
        driver->PopMatrix(OMGL_MATRIX_PROJECTION);

        driver->PushMatrix(OMGL_MATRIX_PROJECTION);
        driver->MultMatrix(proj_sun3, OMGL_MATRIX_PROJECTION);
        depthBuffer->Clear();
        frame_buffer3->Clear();
        frame_buffer3->Enable();
        drawShadow();
        frame_buffer3->Disable();
        driver->PopMatrix(OMGL_MATRIX_PROJECTION);





        driver->PopMatrix(OMGL_MATRIX_PROJECTION);

        driver->PopMatrix(OMGL_MATRIX_VIEW);





        /// Dessin de la scène
        ITexture * depth_texture = frame_buffer->GetDepthTexture();
        ITexture * depth_texture2 = frame_buffer2->GetDepthTexture();
        ITexture * depth_texture3 = frame_buffer3->GetDepthTexture();

        driver->PushMatrix(OMGL_MATRIX_PROJECTION);
        driver->MultMatrix(proj_view, OMGL_MATRIX_PROJECTION);

        driver->PushMatrix(OMGL_MATRIX_VIEW);
        driver->MultMatrix(position, OMGL_MATRIX_VIEW);


        driver->PushMatrix(OMGL_MATRIX_MODEL);
        driver->MultMatrix(pos_model, OMGL_MATRIX_MODEL);
        textureRock->Enable(0);
        scene_model->Draw();
        textureRock->Disable(0);

        // Dessin de l'ombre
        depthBuffer->SetDepth(OMGL3D::CORE::OMGL_DEPTH_EQUAL);
        shader_shadow->Enable();
        depth_texture->Enable(0);
        driver->PushMatrix(OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(Matrix4f::CreateBias(), OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(proj_sun, OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(pos_model*pos_sun.GetInverse(), OMGL_MATRIX_TEXTURE);

        depth_texture2->Enable(1);
        driver->PushMatrix(OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(Matrix4f::CreateBias(), OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(proj_sun, OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(pos_model*pos_sun.GetInverse(), OMGL_MATRIX_TEXTURE);

        depth_texture3->Enable(2);
        driver->PushMatrix(OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(Matrix4f::CreateBias(), OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(proj_sun, OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(pos_model*pos_sun.GetInverse(), OMGL_MATRIX_TEXTURE);


        scene_model->Draw(AlphaTest(OMGL3D::CORE::OMGL_ALPHATEST_GREATER, 0.0f),
            BlendingMode(OMGL3D::CORE::OMGL_BLENDING_ZERO, OMGL3D::CORE::OMGL_BLENDING_SOURCE_ALPHA));

        depth_texture3->Disable(2);
        driver->PopMatrix(OMGL_MATRIX_TEXTURE);
        depth_texture2->Disable(1);
        driver->PopMatrix(OMGL_MATRIX_TEXTURE);
        depth_texture->Disable(0);
        driver->PopMatrix(OMGL_MATRIX_TEXTURE);

        shader_shadow->Disable();
        depthBuffer->SetDepth(OMGL3D::CORE::OMGL_DEPTH_LESS);

        driver->PopMatrix(OMGL_MATRIX_MODEL);



        driver->PushMatrix(OMGL_MATRIX_MODEL);
        driver->MultMatrix(Matrix4f::CreateScale(0.2f, 0.1f, 0.2f), OMGL_MATRIX_MODEL);
        driver->MultMatrix(Matrix4f::CreateRotationX(90), OMGL_MATRIX_MODEL);

        textureGrass->Enable(0);
        driver->PushMatrix(OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(Matrix4f::CreateScale(20, 20, 20), OMGL_MATRIX_TEXTURE);
        terrain->Draw();
        textureGrass->Disable(0);
        driver->PopMatrix(OMGL_MATRIX_TEXTURE);






        depthBuffer->SetDepth(OMGL3D::CORE::OMGL_DEPTH_EQUAL);
        //shader_shadow->enable();

        depth_texture->Enable(0);
        driver->PushMatrix(OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(Matrix4f::CreateBias(), OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(proj_sun, OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(Matrix4f::CreateRotationX(90)*Matrix4f::CreateScale(0.2f, 0.1f, 0.2f)*pos_sun.GetInverse(), OMGL_MATRIX_TEXTURE);

        depth_texture2->Enable(1);
        driver->PushMatrix(OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(Matrix4f::CreateBias(), OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(proj_sun2, OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(Matrix4f::CreateRotationX(90)*Matrix4f::CreateScale(0.2f, 0.1f, 0.2f)*pos_sun.GetInverse(), OMGL_MATRIX_TEXTURE);

        depth_texture3->Enable(2);
        driver->PushMatrix(OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(Matrix4f::CreateBias(), OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(proj_sun3, OMGL_MATRIX_TEXTURE);
        driver->MultMatrix(Matrix4f::CreateRotationX(90)*Matrix4f::CreateScale(0.2f, 0.1f, 0.2f)*pos_sun.GetInverse(), OMGL_MATRIX_TEXTURE);

        terrain->Draw(AlphaTest(OMGL3D::CORE::OMGL_ALPHATEST_GREATER, 0.0f),
            BlendingMode(OMGL3D::CORE::OMGL_BLENDING_ZERO, OMGL3D::CORE::OMGL_BLENDING_SOURCE_ALPHA));

        depth_texture3->Disable(2);
        driver->PopMatrix(OMGL_MATRIX_TEXTURE);
        depth_texture2->Disable(1);
        driver->PopMatrix(OMGL_MATRIX_TEXTURE);
        depth_texture->Disable(0);
        driver->PopMatrix(OMGL_MATRIX_TEXTURE);

        //shader_shadow->disable();
        depthBuffer->SetDepth(OMGL3D::CORE::OMGL_DEPTH_LESS);


        driver->PopMatrix(OMGL_MATRIX_MODEL);




        for(it=tree_position.begin(); it!=tree_position.end(); ++it)
        {
            drawTree(*it);

            depthBuffer->SetDepth(OMGL3D::CORE::OMGL_DEPTH_EQUAL);
            shader_shadow->Enable();

            depth_texture->Enable(0);
            driver->PushMatrix(OMGL_MATRIX_TEXTURE);
            driver->MultMatrix(Matrix4f::CreateBias(), OMGL_MATRIX_TEXTURE);
            driver->MultMatrix(proj_sun, OMGL_MATRIX_TEXTURE);
            driver->MultMatrix(Matrix4f::CreateTranslation(*it)*pos_sun.GetInverse(), OMGL_MATRIX_TEXTURE);

            drawTreeWithShadow(*it);

            depth_texture->Disable(0);
            driver->PopMatrix(OMGL_MATRIX_TEXTURE);

            shader_shadow->Disable();
            depthBuffer->SetDepth(OMGL3D::CORE::OMGL_DEPTH_LESS);

        }
        //drawTree(Vector3f(2, 0, 2));


        driver->PushMatrix(OMGL_MATRIX_MODEL);
        driver->MultMatrix(pos_sun, OMGL_MATRIX_MODEL);

        driver->MultMatrix(Matrix4f::CreateScale(0.01f, 0.01f, 0.01f), OMGL_MATRIX_MODEL);
        projecteur->Draw();

        driver->PopMatrix(OMGL_MATRIX_MODEL);



        driver->PopMatrix(OMGL_MATRIX_VIEW);
        driver->PopMatrix(OMGL_MATRIX_PROJECTION);











        driver->PushMatrix(OMGL_MATRIX_PROJECTION);
        driver->MultMatrix(proj_2d, OMGL_MATRIX_PROJECTION);

        driver->PushMatrix(OMGL_MATRIX_MODEL);

        driver->MultMatrix(Matrix4f::CreateTranslation(0, height_screen-12, 0), OMGL_MATRIX_MODEL);
        font->Draw("Omeglond3D", CColor::Green);

        std::ostringstream oss;
        oss << framerate;
        driver->MultMatrix(Matrix4f::CreateTranslation(0, -12, 0), OMGL_MATRIX_MODEL);
        font->Draw("FPS : "+oss.str(), CColor::Green);

        Vector3f pos = position.GetVector3();

        std::ostringstream ossx, ossy, ossz, ossmax;
        ossx << pos.x;
        ossy << pos.y;
        ossz << pos.z;
        driver->MultMatrix(Matrix4f::CreateTranslation(0, -12, 0), OMGL_MATRIX_MODEL);
        font->Draw("x : "+ossx.str(), CColor::Green);
        driver->MultMatrix(Matrix4f::CreateTranslation(0, -12, 0), OMGL_MATRIX_MODEL);
        font->Draw("y : "+ossy.str(), CColor::Green);
        driver->MultMatrix(Matrix4f::CreateTranslation(0, -12, 0), OMGL_MATRIX_MODEL);
        font->Draw("z : "+ossz.str(), CColor::Green);

        driver->MultMatrix(Matrix4f::CreateTranslation(0, -24, 0), OMGL_MATRIX_MODEL);
        ossmax << max_proj;
        font->Draw("max : "+ossmax.str(), CColor::Green);


        driver->PopMatrix(OMGL_MATRIX_MODEL);

        driver->PopMatrix(OMGL_MATRIX_PROJECTION);


        driver->End();

        window.Display();
    }
}

void CShadowAreaDemo::drawShadow()
{
    driver->PushMatrix(OMGL_MATRIX_MODEL);
    driver->MultMatrix(Matrix4f::CreateTranslation(23, 9, 60), OMGL_MATRIX_MODEL);
    scene_model->Draw();
    driver->PopMatrix(OMGL_MATRIX_MODEL);

    driver->PushMatrix(OMGL_MATRIX_MODEL);
    driver->MultMatrix(Matrix4f::CreateRotationX(90)*Matrix4f::CreateScale(0.2f, 0.1f, 0.2f), OMGL_MATRIX_MODEL);
    terrain->Draw();
    driver->PopMatrix(OMGL_MATRIX_MODEL);

    std::vector<Vector3f>::iterator it;
    for(it=tree_position.begin(); it!=tree_position.end(); ++it)
    {
        drawTree(*it);
    }
}

void CShadowAreaDemo::drawTree(const Vector3f & pos)
{
    driver->PushMatrix(OMGL_MATRIX_MODEL);
    driver->MultMatrix(Matrix4f::CreateTranslation(pos), OMGL_MATRIX_MODEL);
    //driver->multMatrix(Matrix4f::createScale(10, 10, 10), OMGL_MATRIX_MODEL);

    textureTronc->Enable(0);
    tronc->Draw();
    textureTronc->Disable(0);

    textureFeuille->Enable(0);
    driver->PushMatrix(OMGL_MATRIX_TEXTURE);
    driver->MultMatrix(Matrix4f::CreateScale(0.5f, 0.5f, 0.5f), OMGL_MATRIX_TEXTURE);
    feuilles->Draw(AlphaTest(OMGL_ALPHATEST_GREATER, 0.5f));
    textureFeuille->Disable(0);
    driver->PopMatrix(OMGL_MATRIX_TEXTURE);

    driver->PopMatrix(OMGL_MATRIX_MODEL);
}

void CShadowAreaDemo::drawTreeWithShadow(const Vector3f & pos)
{
    driver->PushMatrix(OMGL_MATRIX_MODEL);
    driver->MultMatrix(Matrix4f::CreateTranslation(pos), OMGL_MATRIX_MODEL);

    tronc->Draw(AlphaTest(OMGL_ALPHATEST_GREATER, 0.0f),
        BlendingMode(OMGL3D::CORE::OMGL_BLENDING_ZERO, OMGL3D::CORE::OMGL_BLENDING_SOURCE_ALPHA));

    //driver->pushMatrix(OMGL_MATRIX_TEXTURE);
    //driver->multMatrix(Matrix4f::createScale(0.5f, 0.5f, 0.5f), OMGL_MATRIX_TEXTURE);
    feuilles->Draw(AlphaTest(OMGL_ALPHATEST_GREATER, 0.0f),
        BlendingMode(OMGL3D::CORE::OMGL_BLENDING_ZERO, OMGL3D::CORE::OMGL_BLENDING_SOURCE_ALPHA));
    //driver->popMatrix(OMGL_MATRIX_TEXTURE);

    driver->PopMatrix(OMGL_MATRIX_MODEL);
}
