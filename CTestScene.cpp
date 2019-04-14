#include "CTestScene.hpp"

CTestScene::CTestScene() : sceneSkyBox("scene_skybox"), scene("scene")
{
    width_screen = 800;
    height_screen = 600;
}

void CTestScene::init()
{
    window.Create(sf::VideoMode(width_screen, height_screen, 32), "Test Demo");

    OMGL3D::CDevice * device = OMGL3D::CDevice::CreateDevice(width_screen, height_screen, OMGL3D::OMGL_OPENGL2);

    driver = device->GetVideoDriver();

    // Paramétrage des acces aux ressources
    driver->AddFilePath("./files/textures/");
    driver->AddFilePath("./files/models/");
    driver->AddFilePath("./files/shaders/");


    skybox_cube_map = driver->GetCubeMap("skybox_cubemap");
    skybox_cube_map->SetTexture(OMGL3D::CORE::OMGL_CUBEMAP_FRONT, "skybox00/nightsky_north.tga");
    skybox_cube_map->SetTexture(OMGL3D::CORE::OMGL_CUBEMAP_RIGHT, "skybox00/nightsky_east.tga");
    skybox_cube_map->SetTexture(OMGL3D::CORE::OMGL_CUBEMAP_BEHIND, "skybox00/nightsky_south.tga");
    skybox_cube_map->SetTexture(OMGL3D::CORE::OMGL_CUBEMAP_LEFT, "skybox00/nightsky_west.tga");
    skybox_cube_map->SetTexture(OMGL3D::CORE::OMGL_CUBEMAP_UP, "skybox00/nightsky_up.tga");
    skybox_cube_map->SetTexture(OMGL3D::CORE::OMGL_CUBEMAP_DOWN, "skybox00/nightsky_down.tga");



    // Matrice de projection pour la vue
    OMGL3D::MATH::Matrix4f projection = OMGL3D::MATH::Matrix4f::CreatePerspectiveMatrix(90, 800/600, 0.1, 100);


    nodeCameraPivot = scene.CreateNode("camera_pivot");
    scene.GetRootNode()->AddNode(nodeCameraPivot);



    nodeCamera = scene.CreateCameraNode("camera");
    nodeCamera->SetProjectionMatrix(projection);
    nodeCamera->SetMatrix(OMGL3D::MATH::Matrix4f::CreateLookAtMatrix(5,5,5, 0,0,0, 0,1,0));
    //scene.GetRootNode()->AddNode(nodeCamera);
    nodeCameraPivot->AddNode(nodeCamera);
    scene.SetActiveCamera(nodeCamera);

    nodeCameraSkybox = sceneSkyBox.CreateCameraNode("camera_skybox");
    nodeCameraSkybox->SetProjectionMatrix(projection);
    //nodeCameraSkybox->SetMatrix(OMGL3D::MATH::Matrix4f::CreateLookAtMatrix(5,5,5, 0,0,0, 0,1,0));
    sceneSkyBox.GetRootNode()->AddNode(nodeCameraSkybox);
    sceneSkyBox.SetActiveCamera(nodeCameraSkybox);


    skybox = sceneSkyBox.CreateStaticModelNode("skybox");
    skybox->SetStaticModel( driver->GetPrefabCube() );
    //skybox->SetStaticModel( driver->GetStaticModel("scene.obj") );


    OMGL3D::SCENE::TextureStatement skyboxTexture;
    skyboxTexture.cubeMap = skybox_cube_map;
    //skyboxTexture.texture = driver->GetTexture("rock_color.tga", true);

    skybox->AddTextureStatement(skyboxTexture);

    sceneSkyBox.GetRootNode()->AddNode(skybox);





    node = scene.CreateStaticModelNode("scene");
    node->SetStaticModel(driver->GetStaticModel("scene.obj"));

    OMGL3D::SCENE::TextureStatement sceneTexture;
    sceneTexture.texture = driver->GetTexture("rock_color.tga", true);

    node->AddTextureStatement(sceneTexture);

    //node->SetScale(OMGL3D::MATH::Vector3f(0.1f, 0.1f, 0.1f));
    //node->SetMatrix(OMGL3D::MATH::Matrix4f::CreateScale(0.01f, 0.01f, 0.01f));
    scene.GetRootNode()->AddNode(node);
}

void CTestScene::run()
{
    // Matrice vide => à l'identité
    OMGL3D::MATH::Matrix4f identity;

    // Matrice de projection pour la vue
    OMGL3D::MATH::Matrix4f projection = OMGL3D::MATH::Matrix4f::CreatePerspectiveMatrix(100, (double)width_screen/height_screen, 0.1, 100);

    // Matrice de projection pour la lumière
    OMGL3D::MATH::Matrix4f projection_texture = OMGL3D::MATH::Matrix4f::CreatePerspectiveMatrix(130, 1, 0.1, 20);

    // Matrice de positionement de la camera
    OMGL3D::MATH::Matrix4f lookAt = OMGL3D::MATH::Matrix4f::CreateLookAtMatrix(5,5,5, 0,0,0, 0,1,0);


    // On récupère un pointeur vers le Z-Buffer
    OMGL3D::CORE::IDepthBuffer * depthBuffer = driver->GetDepthBuffer();


    sf::Clock clock;

    float angle = 0;

    bool run = true;
    while( run )
    {
        float elapsed_time = clock.GetElapsedTime();
        //float framerate = 1.f / elapsed_time;
        clock.Reset();

         sf::Event event;
        while(window.GetEvent(event))
        {
            switch(event.Type)
            {
                case sf::Event::Closed:
                    run = false; running = false;
                    break;

                case sf::Event::KeyPressed:
                {
                    if( event.Key.Code == sf::Key::Escape )
                    {
                        run = false;
                        running = false;
                    }
                    break;
                }

                default:
                    break;
            }
        }




         // Mise à jour de l'angle pour l'animation
        angle += 10 * elapsed_time;

        // on évite d'avoir une augmentation infinie.
        if( angle >= 360 ) {
            angle =- 360;
        }

        OMGL3D::MATH::Eulerf euler;
        euler.x = 0;
        OMGL3D::MATH::Quaternionf rotation = OMGL3D::MATH::Quaternionf::CreateQuaternion(euler);

        OMGL3D::MATH::Matrix4f matrix = OMGL3D::MATH::Matrix4f::CreateScale(0.01f, 0.01f, 0.01f) * rotation.GetMatrix4();

        //node->SetMatrix(matrix);
        //node->SetMatrix(OMGL3D::MATH::Matrix4f::CreateScale(0.01f, 0.01f, 0.01f));

        // Création de la matrice pivot
        OMGL3D::MATH::Matrix4f pivot = OMGL3D::MATH::Matrix4f::CreateRotationY(angle);
        //node->SetMatrix(pivot);
        nodeCameraPivot->SetMatrix(pivot);
        //skybox->SetMatrix(pivot);

        // matrice du positionnement de la caméra
        OMGL3D::MATH::Matrix4f matrix_view = lookAt * pivot.GetInverse();

        //nodeCamera->SetMatrix(matrix_view);

        OMGL3D::MATH::Matrix4f mat = nodeCamera->CreateGlobalMatrix();
        OMGL3D::MATH::Quaternionf q = OMGL3D::MATH::Quaternionf::CreateQuaternion(mat);
        mat = q.GetMatrix4();
        nodeCameraSkybox->SetMatrix(mat);

        // Vide les buffers
        driver->Begin();

        // Initialise les matrices
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_PROJECTION);
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_MODEL);
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_VIEW);
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_TEXTURE);



        // On paramètre les matrices pour l'image "normale"
        //driver->MultMatrix(projection, OMGL3D::CORE::OMGL_MATRIX_PROJECTION);

        // On place la caméra
        //driver->MultMatrix(matrix_view, OMGL3D::CORE::OMGL_MATRIX_VIEW);



        // On dessine la skybox
        {
            // On vérouille l'écriture dans le Z-buffer
            depthBuffer->Lock();

            OMGL3D::MATH::Matrix4f matrix_skybox = OMGL3D::MATH::Matrix4f::CreateTranslation(matrix_view.GetVector3());
            //skybox->SetMatrix(matrix_skybox);

            sceneSkyBox.Draw();

/*
            driver->PushMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);

            // On place la skybox à la position de la caméra
            OMGL3D::MATH::Matrix4f matrix_skybox = OMGL3D::MATH::Matrix4f::CreateTranslation(matrix_view.GetVector3());
            driver->MultMatrix(matrix_skybox, OMGL3D::CORE::OMGL_MATRIX_MODEL);

            skybox_cube_map->Enable();
            skybox->Draw();
            skybox_cube_map->Disable();

            driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);
*/
            depthBuffer->Unlock(); // On dévérouille le Z-buffer

            //driver->pushMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);
        }


        // Initialise les matrices
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_PROJECTION);
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_MODEL);
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_VIEW);
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_TEXTURE);

        /*
        driver->MultMatrix(OMGL3D::MATH::Matrix4f::CreatePerspectiveMatrix(90, 800/600, 0.1, 1000), OMGL3D::CORE::OMGL_MATRIX_PROJECTION);
        driver->MultMatrix(OMGL3D::MATH::Matrix4f::CreateLookAtMatrix(5,5,5, 0,0,0, 0,1,0), OMGL3D::CORE::OMGL_MATRIX_VIEW);
        driver->MultMatrix(OMGL3D::MATH::Matrix4f::CreateScale(0.01f, 0.01f, 0.01f), OMGL3D::CORE::OMGL_MATRIX_MODEL);
        driver->GetStaticModel("projecteur.obj")->Draw();
        */


        scene.Draw();




        driver->End();

        window.Display();

    }
}
