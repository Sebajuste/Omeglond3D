#ifndef _DEF_OMEGLOND3D_CCOMPONENT_HPP
#define _DEF_OMEGLOND3D_CCOMPONENT_HPP

#include <string>
#include "IEvent.hpp"
#include "../Utils/Ptr/SmartPtr.hpp"
#include "../Utils/Export.hpp"

namespace OMGL3D
{
    namespace UI
    {
        class EXPORT CComponent
        {

        public:

            virtual ~CComponent() {}

            void SetName(const std::string & name);

            std::string GetName() const;

            void SetPosition(int x, int y);

            int GetPositionX() const;

            int GetPositionY() const;

            void SetSize(int width, int height);

            int GetWidth() const;

            int GetHeight() const;

            void SetVisible(bool visible);

            bool IsVisible() const;

            void SetMouseAction(IMouseAction * action);

            IMouseAction * GetMouseAction();

            void SetFather(CComponent * father);

            CComponent * GetFather();

            virtual void OnEvent(const MouseEvent & event);

            virtual void Draw()=0;


        protected:

            CComponent();

            CComponent(const std::string & name);

            std::string _name;
            int _x, _y, _width, _height;
            int _globalX, _globalY;
            bool _visible;

            CComponent * _father;

            UTILS::ptr<IMouseAction>::SharedPtr _action;
        };


    }
}

#endif
