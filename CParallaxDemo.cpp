#include "CParallaxDemo.hpp"

#include "src/Core/CMesh.hpp"
#include "src/Model/CStaticModel.hpp"
#include "src/Interface/CFrame.hpp"

#include <iostream>

using namespace OMGL3D;

CParallaxDemo::CParallaxDemo() : device(0), driver(0)
{
    width_screen = 800;
    height_screen = 600;
}

struct MyEvent : public OMGL3D::UI::IMouseAction
{
    void OnClick(const OMGL3D::UI::MouseEvent & event)
    {
        std::cout << "j'ai clique sur l'image de ma frame x: " << event.x << "   y: " << event.y << std::endl;
    }
};

void CParallaxDemo::init()
{
    window.Create(sf::VideoMode(width_screen, height_screen, 32), "Parallax & Shadow mapping Demo");

    #ifdef WIN32
        //OMGL3D::CDevice * device = OMGL3D::CDevice::createDevice(width_screen, height_screen, OMGL3D::OMGL_OPENGL);
    #else
        //OMGL3D::CDevice * device = OMGL3D::CDevice::createDevice(width_screen, height_screen, "./bin/Release/linux/libOGLRender.so");
    #endif

    OMGL3D::CDevice * device = OMGL3D::CDevice::CreateDevice(width_screen, height_screen, OMGL3D::OMGL_OPENGL2);

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

    // Création d'une lumière
    light = driver->CreateLight("lumière");
    light->SetType(CORE::OMGL_LIGHT_POSITIONAL);
    light->SetColor(CORE::OMGL_LIGHT_COLOR_AMBIENT, CORE::CColor(0.5f, 0.5f, 0.7f));
    light->SetColor(CORE::OMGL_LIGHT_COLOR_DIFUSE, CORE::CColor(0.9f, 0.8f, 0.5f));

    OMGL3D::CORE::CResourceManager::GetInstance().AddResource("lumière", light);



    // Chargement des modèles 3D
    scene_model = driver->GetStaticModel("scene.obj");
    projecteur = driver->GetStaticModel("projecteur.obj");



    // Création de notre FBO
    frame_buffer = driver->GetFrameBufferRender("FBO_light_depthmap", 512, 512);

    // On récupère la texture du Z-buffer depuis notre FBO
    OMGL3D::CORE::ITexture * depth_texture = frame_buffer->GetDepthTexture();

    // On définit nos propriétés pour la génération automatique de texture
    OMGL3D::CORE::TexCoordPlane planes_linear[] = {
        {1.0, 0.0, 0.0, 0.0, OMGL3D::CORE::OMGL_TEXCOORD_LINEAR},
        {0.0, 1.0, 0.0, 0.0, OMGL3D::CORE::OMGL_TEXCOORD_LINEAR},
        {0.0, 0.0, 1.0, 0.0, OMGL3D::CORE::OMGL_TEXCOORD_LINEAR},
        {0.0, 0.0, 0.0, 1.0, OMGL3D::CORE::OMGL_TEXCOORD_LINEAR}
    };

    // On génère les coordonnées pour notre texture, sur le canal 0
    depth_texture->GenerateTexCoord(0, planes_linear);



    // Chargement du shader de parallax mapping
    shader = driver->GetShader("parallax-mapping", "parallax.vert", "parallax.frag");
    shader->SetParameter("colorMap", 0);
    shader->SetParameter("normalMap", 1);
    shader->SetParameter("heightMap", 2);

    // Chargement du shader d'affichage des ombres
    shader_shadow = driver->GetShader("shadow_mapping", "shadow.vert", "shadow.frag");
    shader_shadow->SetParameter("shadowMap", 0);

    // chargement des textures
    textureRock = driver->GetTexture("rock_color.tga");
    textureRockNormal = driver->GetTexture("rock_normal.tga");
    textureRockHeight = driver->GetTexture("rock_height.tga");

    tronc = driver->GetStaticModel("tree_tronc.obj");
    feuilles = driver->GetStaticModel("tree_leaf.obj");
    textureTronc = driver->GetTexture("tronc_color_map.tga");
    textureFeuilles = driver->GetTexture("tree_alpha_leaf.tga");



    // Création de la skybox

    skybox = driver->GetPrefabCube();





    // Création d'une texture cube map pour la Sky Box
    skybox_cube_map = driver->GetCubeMap("skybox_cubemap");

    // Chargement des 6 textures pour la skybox
    //OMGL3D::UTILS::ptr<OMGL3D::CORE::CPicture>::SharedPtr img;
    //img = OMGL3D::CORE::CMediaManager::GetInstance().LoadFromFile<OMGL3D::CORE::CPicture>("skybox00/nightsky_north.tga");
    skybox_cube_map->SetTexture(OMGL3D::CORE::OMGL_CUBEMAP_FRONT, "skybox00/nightsky_north.tga");

    //img = OMGL3D::CORE::CMediaManager::GetInstance().LoadFromFile<OMGL3D::CORE::CPicture>("skybox00/nightsky_east.tga");
    skybox_cube_map->SetTexture(OMGL3D::CORE::OMGL_CUBEMAP_RIGHT, "skybox00/nightsky_east.tga");

    //img = OMGL3D::CORE::CMediaManager::GetInstance().LoadFromFile<OMGL3D::CORE::CPicture>("skybox00/nightsky_south.tga");
    skybox_cube_map->SetTexture(OMGL3D::CORE::OMGL_CUBEMAP_BEHIND, "skybox00/nightsky_south.tga");

    //img = OMGL3D::CORE::CMediaManager::GetInstance().LoadFromFile<OMGL3D::CORE::CPicture>("skybox00/nightsky_west.tga");
    skybox_cube_map->SetTexture(OMGL3D::CORE::OMGL_CUBEMAP_LEFT, "skybox00/nightsky_west.tga");

    //img = OMGL3D::CORE::CMediaManager::GetInstance().LoadFromFile<OMGL3D::CORE::CPicture>("skybox00/nightsky_up.tga");
    skybox_cube_map->SetTexture(OMGL3D::CORE::OMGL_CUBEMAP_UP, "skybox00/nightsky_up.tga");

    //img = OMGL3D::CORE::CMediaManager::GetInstance().LoadFromFile<OMGL3D::CORE::CPicture>("skybox00/nightsky_down.tga");
    skybox_cube_map->SetTexture(OMGL3D::CORE::OMGL_CUBEMAP_DOWN, "skybox00/nightsky_down.tga");




    /// Création de la frame

    OMGL3D::UI::CFrame * frame = OMGL3D::UI::CInterfaceManager::CreateFrame("main_frame");

    frame->SetSize(400, 300);
    frame->SetPosition(10, 10);
    frame->SetBackground("rock_color.tga");
    frame->SetTitle("Ma Frame", "verdana");



    UI::CLabel * label = new UI::CLabel("label1");
    label->SetFont("verdana");
    label->SetPosition(10, 10);
    label->SetText("Mon Label !");
    frame->AddComponent(label);

    UI::CImage * image = new UI::CImage("mon_image");
    image->SetTexture("caisse.tga");
    image->SetPosition(50, 60);
    image->SetSize(200, 100);

    MyEvent * event = new MyEvent();
    image->SetMouseAction(event);

    frame->AddComponent(image);

    OMGL3D::UI::CInterfaceManager * interface = OMGL3D::CDevice::GetDevice()->CreateInterfaceManager();
    interface->AddComponent(frame);



}

void CParallaxDemo::run()
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
    CORE::IDepthBuffer * depthBuffer = driver->GetDepthBuffer();


    sf::Clock clock;

    float angle = 0;

    bool run = true;
    while( run )
    {
        float elapsed_time = clock.GetElapsedTime();
        float framerate = 1.f / elapsed_time;
        clock.Reset();


        // Mise à jour de l'angle pour l'animation
        angle += 10 * elapsed_time;

        // on évite d'avoir une augmentation infinie.
        if( angle >= 360 )
            angle =- 360;

        // Création de la matrice pivot
        OMGL3D::MATH::Matrix4f pivot = OMGL3D::MATH::Matrix4f::CreateRotationY(angle);

        // Gestion des évènement pour fermer l'applicaton
        sf::Event event;

        OMGL3D::UI::MouseEvent e;

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

                case sf::Event::MouseMoved:
                {
                    e.x = event.MouseMove.X;
                    e.y = height_screen-event.MouseMove.Y;
                    break;
                }

                case sf::Event::MouseButtonPressed:
                {
                    //OMGL3D::UI::CInterfaceManager::getInstance().OnEvent(e);
                    //OMGL3D::UI::CInterfaceManager * interface = OMGL3D::CDevice::GetDevice()->GetUserInterfaceManager();
                    //interface->OnEvent(e);
                    break;
                }

                default:
                    break;
            }
        }




        // Vide les buffers
        driver->Begin();

        // Initialise les matrices

        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_PROJECTION);
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_MODEL);
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_VIEW);
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_TEXTURE);



        // matrice du positionnement de la caméra
        OMGL3D::MATH::Matrix4f matrix_view = lookAt * pivot.GetInverse() ;

        // Matrice de positionnement de la lumière
        OMGL3D::MATH::Matrix4f matrix_light = OMGL3D::MATH::Matrix4f::CreateRotationY(-90) * OMGL3D::MATH::Matrix4f::CreateTranslation(6, 3, 0) * pivot;
        //OMGL3D::MATH::Matrix4f matrix_light = OMGL3D::MATH::Matrix4f::createLookAtMatrix(5,10,5, 0,0,0, 0,1,0).inverse();


        // Pré rendu pour l'ombre
        driver->PushMatrix(OMGL3D::CORE::OMGL_MATRIX_PROJECTION);
        driver->MultMatrix(projection_texture, OMGL3D::CORE::OMGL_MATRIX_PROJECTION);

        // On positionne le point de vue de la lampe
        driver->PushMatrix(OMGL3D::CORE::OMGL_MATRIX_VIEW);
        driver->MultMatrix(matrix_light, OMGL3D::CORE::OMGL_MATRIX_VIEW);

        // On active le dessin dans le FBO
        frame_buffer->Clear();
        frame_buffer->Enable();

        scene_model->Draw(); // on dessine la scène

        driver->PushMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);
        driver->MultMatrix(OMGL3D::MATH::Matrix4f::CreateTranslation(2, 0, 2), OMGL3D::CORE::OMGL_MATRIX_MODEL);
        tronc->Draw();
        textureFeuilles->Enable(0);
        feuilles->Draw(OMGL3D::CORE::AlphaTest(OMGL3D::CORE::OMGL_ALPHATEST_GREATER, 0.5f));
        textureFeuilles->Disable(0);
        driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);

        frame_buffer->Disable(); // on désactive le FBO

        // On revient à l'état initiale des matrices
        driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_VIEW);
        driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_PROJECTION);


        // On paramètre les matrices pour l'image "normale"
        driver->PushMatrix(OMGL3D::CORE::OMGL_MATRIX_PROJECTION);
        driver->MultMatrix(projection, OMGL3D::CORE::OMGL_MATRIX_PROJECTION);

        // On place la caméra
        driver->PushMatrix(OMGL3D::CORE::OMGL_MATRIX_VIEW);
        driver->MultMatrix(matrix_view, OMGL3D::CORE::OMGL_MATRIX_VIEW);

        // On dessine la skybox
        {
            // On vérouille l'écriture dans le Z-buffer
            depthBuffer->Lock();

            driver->PushMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);

            // On place la skybox à la position de la caméra
            OMGL3D::MATH::Matrix4f matrix_skybox = OMGL3D::MATH::Matrix4f::CreateTranslation(matrix_view.GetVector3());
            driver->MultMatrix(matrix_skybox, OMGL3D::CORE::OMGL_MATRIX_MODEL);

            skybox_cube_map->Enable();
            skybox->Draw();
            skybox_cube_map->Disable();

            driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);

            depthBuffer->Unlock(); // On dévérouille le Z-buffer

            //driver->pushMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);
        }

        // On positionne la lumière
        {
            driver->PushMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);

            // On fixe la position de la lumière
            light->SetPosition(matrix_light.GetVector3());

            // On place la lumière
            driver->MultMatrix(matrix_light, OMGL3D::CORE::OMGL_MATRIX_MODEL);

            // On effectue quelques réglages pour placer le modèle 3D du projecteur
            driver->MultMatrix(OMGL3D::MATH::Matrix4f::CreateTranslation(0, -2, 0), OMGL3D::CORE::OMGL_MATRIX_MODEL); // On descend le modèle
            driver->MultMatrix(OMGL3D::MATH::Matrix4f::CreateScale(0.01, 0.01, 0.01), OMGL3D::CORE::OMGL_MATRIX_MODEL); // on le rend plus petit
            driver->MultMatrix(OMGL3D::MATH::Matrix4f::CreateRotationY(180.0f), OMGL3D::CORE::OMGL_MATRIX_MODEL); // on le retourne pour qu'il pointe dans la bonne direction
            projecteur->Draw(); // dessin du projecteur
            driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);

            // On active la lumière; elle restera activé tant qu'on a pas appelé la méthode disable()
            light->Enable();
        }

        // dessin de la scène
        {
            // On utilise le shader de parallax-mapping
            shader->Enable();

            // On active les 3 texture
            textureRock->Enable(0); // la couleur
            textureRockNormal->Enable(1); // la normal-map, pour le bump mapping
            textureRockHeight->Enable(2); // la hauteur, pour la déformation de la texture

            scene_model->Draw(); // on dessine la scène

            // On désactive les textures
            textureRockHeight->Disable(2);
            textureRockNormal->Disable(1);
            textureRock->Disable(0);

            // On désactive le shader puis la lumière
            shader->Disable();


            driver->PushMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);
            driver->MultMatrix(OMGL3D::MATH::Matrix4f::CreateTranslation(2, 0, 2), OMGL3D::CORE::OMGL_MATRIX_MODEL);
            textureTronc->Enable(0);
            tronc->Draw();
            textureTronc->Disable(0);
            textureFeuilles->Enable(0);
            feuilles->Draw(OMGL3D::CORE::AlphaTest(OMGL3D::CORE::OMGL_ALPHATEST_GREATER, 0.5f));
            textureFeuilles->Disable(0);
            driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);




            light->Disable();
        }

        // Dessin de l'ombre sur la scène
        {
            OMGL3D::CORE::ITexture * depth_texture = frame_buffer->GetDepthTexture();

            // On demande d'utiliser le Z-buffer en "inférieur ou égal" (par défaut "strictement inférieur")
            // Nécéssaire pour le blending (affichage d'un model sur un autre)
            depthBuffer->SetDepth(OMGL3D::CORE::OMGL_DEPTH_EQUAL);

            // On active le shader d'ombre
            shader_shadow->Enable();

            // On active la texture du Z-Buffer du FBO
            depth_texture->Enable(0);

            // On paramètre la matrice de texture
            driver->PushMatrix(OMGL3D::CORE::OMGL_MATRIX_TEXTURE);
            //driver->loadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_TEXTURE);

            driver->MultMatrix(MATH::Matrix4f::CreateBias(), OMGL3D::CORE::OMGL_MATRIX_TEXTURE); // on luis applique un bias
            driver->MultMatrix(projection_texture, OMGL3D::CORE::OMGL_MATRIX_TEXTURE); // puis la projection utilisée par le FBO
            driver->MultMatrix(matrix_light.GetInverse(), OMGL3D::CORE::OMGL_MATRIX_TEXTURE); // et on positionne le point de vue de la matrice sur le point de vue de la lumière

            // On dessine la scène
            // - le test alpha pour n'afficher que les pixel d'ombres
            // - avec un blending alpha, pour mélanger l'ombre à la couleur précédente. Le but étant d'assombrir la zone.
            scene_model->Draw(CORE::AlphaTest(CORE::OMGL_ALPHATEST_GREATER, 0.0f),
                OMGL3D::CORE::BlendingMode(OMGL3D::CORE::OMGL_BLENDING_ZERO, OMGL3D::CORE::OMGL_BLENDING_SOURCE_ALPHA));

            // On désactive la texture
            depth_texture->Disable(0);
            driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_TEXTURE); // on remet la matrice de texture à son état précédent


            driver->PushMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);
            driver->MultMatrix(OMGL3D::MATH::Matrix4f::CreateTranslation(2, 0, 2), OMGL3D::CORE::OMGL_MATRIX_MODEL);
            depth_texture->Enable(0);
            driver->PushMatrix(OMGL3D::CORE::OMGL_MATRIX_TEXTURE);
            driver->MultMatrix(MATH::Matrix4f::CreateBias(), OMGL3D::CORE::OMGL_MATRIX_TEXTURE); // on luis applique un bias
            driver->MultMatrix(projection_texture, OMGL3D::CORE::OMGL_MATRIX_TEXTURE); // puis la projection utilisée par le FBO
            driver->MultMatrix(matrix_light.GetInverse(), OMGL3D::CORE::OMGL_MATRIX_TEXTURE); // et on positionne le point de vue de la matrice sur le point de vue de la lumière
            tronc->Draw(CORE::AlphaTest(CORE::OMGL_ALPHATEST_GREATER, 0.0f),
                OMGL3D::CORE::BlendingMode(OMGL3D::CORE::OMGL_BLENDING_ZERO, OMGL3D::CORE::OMGL_BLENDING_SOURCE_ALPHA));
            depth_texture->Disable(0);
            driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_TEXTURE); // on remet la matrice de texture à son état précédent

            depth_texture->Enable(0);
            driver->PushMatrix(OMGL3D::CORE::OMGL_MATRIX_TEXTURE);
            driver->MultMatrix(MATH::Matrix4f::CreateBias(), OMGL3D::CORE::OMGL_MATRIX_TEXTURE); // on luis applique un bias
            driver->MultMatrix(projection_texture, OMGL3D::CORE::OMGL_MATRIX_TEXTURE); // puis la projection utilisée par le FBO
            driver->MultMatrix(matrix_light.GetInverse(), OMGL3D::CORE::OMGL_MATRIX_TEXTURE); // et on positionne le point de vue de la matrice sur le point de vue de la lumière
            feuilles->Draw(CORE::AlphaTest(CORE::OMGL_ALPHATEST_GREATER, 0.0f),
                OMGL3D::CORE::BlendingMode(OMGL3D::CORE::OMGL_BLENDING_ZERO, OMGL3D::CORE::OMGL_BLENDING_SOURCE_ALPHA));
            depth_texture->Disable(0);
            driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_TEXTURE); // on remet la matrice de texture à son état précédent
            driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_MODEL);


            // on désactive notre shader
            shader_shadow->Disable();

            // On remet le Z-buffer dans sa position par défaut
            depthBuffer->SetDepth(OMGL3D::CORE::OMGL_DEPTH_LESS);
        }

        // On restaure l'état des matrices
        driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_VIEW);
        driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_PROJECTION);



        // On paramètre la matrice de projection pour un affichage 2D
        driver->LoadMatrix(identity, OMGL3D::CORE::OMGL_MATRIX_PROJECTION);
        driver->MultMatrix(OMGL3D::MATH::Matrix4f::CreateOrthoMatrix(0, width_screen, 0, height_screen, -1, 1), OMGL3D::CORE::OMGL_MATRIX_PROJECTION);


        depthBuffer->Lock();
        //OMGL3D::UI::CInterfaceManager * interface = OMGL3D::CDevice::GetDevice()->GetUserInterfaceManager();
        //interface->Draw();
        depthBuffer->Unlock();


        // On utilise la matrice de vue pour déplacer le "curseur d'écriture" à l'écran
        driver->PushMatrix(CORE::OMGL_MATRIX_MODEL);
        driver->MultMatrix(MATH::Matrix4f::CreateTranslation(0, height_screen-12, 0), CORE::OMGL_MATRIX_MODEL);

        font->Draw("Omeglond3D v2", CORE::CColor::Green);

        driver->MultMatrix(MATH::Matrix4f::CreateTranslation(0, -12, 0), CORE::OMGL_MATRIX_MODEL);
        std::ostringstream oss;
        oss << framerate;
        std::string sFPS = "FPS : " + oss.str();

        CORE::CColor color = CORE::CColor::Red;

        if( framerate > 25 )
            color = CORE::CColor::Yellow;
        if( framerate > 50 )
            color = CORE::CColor::Green;
        if( framerate > 100 )
            color = CORE::CColor::White;

        font->Draw(sFPS, color);

        // On restaure nos matrices
        driver->PopMatrix(CORE::OMGL_MATRIX_MODEL);
        driver->PopMatrix(OMGL3D::CORE::OMGL_MATRIX_PROJECTION);

        driver->End();

        window.Display();
    }
}
