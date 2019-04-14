#include "CAnimatedModelDemo.hpp"

#include <iostream>

struct TestEvent : public OMGL3D::UI::IMouseAction
{
    void OnClick(const MouseEvent & event)
    {
        std::cout << "click" << std::endl;
    }
};

CAnimatedModelDemo::CAnimatedModelDemo() : _scene("ma_scene")
{
    width_screen = 800;
    height_screen = 600;
}

void CAnimatedModelDemo::init()
{
    window.Create(sf::VideoMode(width_screen, height_screen, 32), "Animated Model Demo");

    CDevice * device = OMGL3D::CDevice::CreateDevice(width_screen, height_screen, OMGL3D::OMGL_OPENGL2);

    driver = device->GetVideoDriver();

    driver->AddFilePath("./files/models/");
    driver->AddFilePath("./files/textures/");
    driver->AddFilePath("./files/shaders/");


    scene_model = driver->GetStaticModel("scene.obj");
    textureRock = driver->GetTexture("rock_color.tga");

    OMGL3D::SCENE::TextureStatement tex_state;
    tex_state.texture = driver->GetTexture("rock_color.tga");





    model_node = _scene.CreateStaticModelNode("ma_scene");
    model_node->AddTextureStatement(tex_state);
    model_node->SetStaticModel(driver->GetStaticModel("scene.obj"));

    _scene.GetRootNode()->AddNode(model_node);


    camera = _scene.CreateCameraNode("ma_camera");
    camera->SetProjectionMatrix(OMGL3D::MATH::Matrix4f::CreatePerspectiveMatrix(70, width_screen/height_screen, 0.1, 1000));

    _scene.GetRootNode()->AddNode(camera);
    _scene.SetActiveCamera(camera);



    OMGL3D::UI::CInterfaceManager * interface = OMGL3D::CDevice::GetDevice()->GetUserInterfaceManager();

    OMGL3D::UI::CFrame * frame = interface->CreateFrame("Ma Frame");

    frame->SetBackground("rock_color.tga");
    frame->SetSize(256, 256);

    frame->SetDrawnable(true);

    frame->SetMouseAction(new TestEvent());

    interface->AddComponent(frame);

}

void CAnimatedModelDemo::yourEvent(float elapsedtime, const sf::Event & event)
{
    if( event.Type == sf::Event::MouseMoved)
    {
        omgl_event.x = event.MouseMove.X;
        omgl_event.y = event.MouseMove.Y;
        return;
    }

    if( event.Type == sf::Event::MouseButtonPressed )
    {
        omgl_event.type = MouseEvent::Pressed;
    }
    if( event.Type == sf::Event::MouseButtonReleased )
    {
        omgl_event.type = MouseEvent::Release;
    }

    if( event.MouseButton.Button == sf::Mouse::Right )
    {
        omgl_event.button = MouseEvent::Right;
    }
}

void CAnimatedModelDemo::run()
{
    OMGL3D::UI::CInterfaceManager * interface = OMGL3D::CDevice::GetDevice()->GetUserInterfaceManager();
    interface->OnEvent(omgl_event);

    //Matrix4f proj_view = OMGL3D::MATH::Matrix4f::createPerspectiveMatrix(70, width_screen/height_screen, 0.1, 1000);


    camera->SetMatrix(position.GetInverse());

    driver->Begin();

/*
    driver->pushMatrix(OMGL_MATRIX_PROJECTION);
    driver->multMatrix(proj_view, OMGL_MATRIX_PROJECTION);

    driver->pushMatrix(OMGL_MATRIX_VIEW);
    driver->multMatrix(position, OMGL_MATRIX_VIEW);
*/


    _scene.Draw();
/*
    textureRock->enable();
    scene_model->draw();
    textureRock->disable();
*/

/*
    driver->popMatrix(OMGL_MATRIX_VIEW);
    driver->popMatrix(OMGL_MATRIX_PROJECTION);
*/

    driver->PushMatrix(OMGL_MATRIX_PROJECTION);
    driver->MultMatrix(OMGL3D::MATH::Matrix4f::CreateOrthoMatrix(0, 800, 600, 0, -1, 1), OMGL_MATRIX_PROJECTION);

    interface->Draw();

    driver->PopMatrix(OMGL_MATRIX_PROJECTION);


    driver->End();

    window.Display();

}
