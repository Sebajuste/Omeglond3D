#include "CComponent.hpp"

namespace OMGL3D
{
    namespace UI
    {
        CComponent::CComponent() : _x(0), _y(0), _width(0), _height(0), _globalX(0), _globalY(0), _visible(true), _father(0)
        {
        }

        CComponent::CComponent(const std::string & name) : _name(name), _x(0), _y(0), _width(0), _height(0), _globalX(0), _globalY(0), _visible(true), _father(0)
        {
        }

        void CComponent::SetName(const std::string & name)
        {
            _name = name;
        }

        std::string CComponent::GetName() const
        {
            return _name;
        }

        void CComponent::SetPosition(int x, int y)
        {
            _x = x;
            _y = y;
            if( _father == 0 )
            {
                _globalX = x;
                _globalY = y;
            }
            else
            {
                _globalX = _father->_globalX + x;
                _globalY = _father->_globalY + y;
            }
        }

        int CComponent::GetPositionX() const
        {
            return _x;
        }

        int CComponent::GetPositionY() const
        {
            return _y;
        }

        void CComponent::SetSize(int width, int height)
        {
            _width = width;
            _height = height;
        }

        int CComponent::GetWidth() const
        {
            return _width;
        }

        int CComponent::GetHeight() const
        {
            return _height;
        }

        void CComponent::SetVisible(bool visible)
        {
            _visible = visible;
        }

        bool CComponent::IsVisible() const
        {
            return _visible;
        }

        void CComponent::SetMouseAction(IMouseAction * action)
        {
            _action = action;
            //_action->_parent = this;
        }

        IMouseAction * CComponent::GetMouseAction()
        {
            return _action;
        }

        void CComponent::SetFather(CComponent * father)
        {
            _father = father;
            _globalX = _x+father->_globalX;
            _globalY = _y+father->_globalY;
        }

        CComponent * CComponent::GetFather()
        {
            return _father;
        }

        void CComponent::OnEvent(const MouseEvent & event)
        {
            if( !_action ) return;

            if( event.x > _globalX && event.x < _globalX+_width &&
                event.y > _globalY && event.y < _globalY+_height )
            {
                switch(event.type)
                {
                    case MouseEvent::Pressed:
                        _action->OnClick(event);
                        break;

                    case MouseEvent::Release:
                        _action->UnClick(event);
                        break;

                    case MouseEvent::Moved:
                        _action->OnMoved(event);
                        break;
                }
            }
        }
    }
}
