#ifndef _DEF_IDEMO_HPP
#define _DEF_IDEMO_HPP

#include "src/Omgl3D.hpp"
#include <SFML/Window.hpp>

class IDemo
{
	public:

	IDemo() : width_screen(800), height_screen(600), running(true)
	{
	}

	virtual ~IDemo() {}

	virtual void yourEvent(float elapsedtime, const sf::Event & event) {}

    void events(float elapsedtime)
    {
        sf::Event event;
        while( window.GetEvent(event) )
        {
            if( event.Type == sf::Event::Closed )
            {
                running = false;
            }

            if( event.Type == sf::Event::KeyPressed )
            {
                switch(event.Key.Code)
                {
                    case sf::Key::Escape:
                        running = false;
                        break;

                    default:
                        break;
                }
            }

            yourEvent(elapsedtime, event);
        }

        const sf::Input& Input = window.GetInput();

        bool LeftKeyDown     = Input.IsKeyDown(sf::Key::Left);
        bool RightKeyDown = Input.IsKeyDown(sf::Key::Right);
        bool UpKeyDown     = Input.IsKeyDown(sf::Key::Up);
        bool DownKeyDown = Input.IsKeyDown(sf::Key::Down);
        bool QKeyDown     = Input.IsKeyDown(sf::Key::Q);
        bool DKeyDown = Input.IsKeyDown(sf::Key::D);
        bool ZKeyDown     = Input.IsKeyDown(sf::Key::Z);
        bool SKeyDown = Input.IsKeyDown(sf::Key::S);

        OMGL3D::MATH::Quaternionf rotate, rotate_x, rotate_y, rotate_z;
        OMGL3D::MATH::Vector3f vector;

        if( LeftKeyDown )
        {
            rotate_x = OMGL3D::MATH::Quaternionf::CreateQuaternion(0, 0, 1, -20*elapsedtime);
        }

        if( RightKeyDown )
        {
            rotate_x = OMGL3D::MATH::Quaternionf::CreateQuaternion(0, 0, 1, 20*elapsedtime);
        }

        if( UpKeyDown )
        {
            rotate_z = OMGL3D::MATH::Quaternionf::CreateQuaternion(1, 0, 0, -20*elapsedtime);
        }

        if( DownKeyDown )
        {
            rotate_z = OMGL3D::MATH::Quaternionf::CreateQuaternion(1, 0, 0, 20*elapsedtime);
        }

        if( QKeyDown )
        {
            rotate_y = OMGL3D::MATH::Quaternionf::CreateQuaternion(0, 1, 0, -20*elapsedtime);
        }

        if( DKeyDown )
        {
            rotate_y = OMGL3D::MATH::Quaternionf::CreateQuaternion(0, 1, 0, 20*elapsedtime);
        }

        if( ZKeyDown )
        {
            vector.z = -10*elapsedtime;
        }

        if( SKeyDown )
        {
            vector.z = 10*elapsedtime;
        }

        rotate = rotate_x * rotate_y * rotate_z;

        //position = rotate.getMatrix4();
        position *= rotate.GetMatrix4();
        position *= vector;
    }

	virtual void init()=0;

	virtual void run()=0;

	void start()
	{
	    init();

	    sf::Clock clock;
	    while( running )
	    {
            elapsedtime = clock.GetElapsedTime();
            clock.Reset();

            events(elapsedtime);
            run();
	    }
	}

	protected:

	unsigned int width_screen, height_screen;

	bool running;

	float elapsedtime;

    sf::Window window;

	OMGL3D::MATH::Matrix4f position;
};

#endif
