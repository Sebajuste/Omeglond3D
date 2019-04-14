#include "CFrame.hpp"

#include "../Core/CDevice.hpp"
#include "../Core/IVideoDriver.hpp"

namespace OMGL3D
{
    namespace UI
    {
        CFrame::CFrame(const std::string & name) : CComponent(name), _hold(false), _mousex(0), _mousey(0), _drawn(false)
        {
            CORE::IVideoDriver * driver = CDevice::GetDevice()->GetVideoDriver();
            _model = driver->GetPrefabSquare();
        }

        void CFrame::SetBackground(const std::string & name)
        {
            CORE::IVideoDriver * driver = CDevice::GetDevice()->GetVideoDriver();
            _background = driver->GetTexture(name);
        }

        void CFrame::SetTitle(const std::string & title, const std::string & font)
        {
            CORE::IVideoDriver * driver = CDevice::GetDevice()->GetVideoDriver();
            _font = driver->GetFont(font);
            _title = title;
        }

        void CFrame::SetDrawnable(bool drawn)
        {
            _drawn = drawn;
        }

        bool CFrame::IsDrawnable() const
        {
            return _drawn;
        }

        void CFrame::AddComponent(CComponent * component)
        {
            _list_component.push_back(component);
            component->SetFather(this);
        }

        std::vector<UTILS::ptr<CComponent>::SharedPtr> & CFrame::GetListComponent()
        {
            return _list_component;
        }

        void CFrame::OnEvent(const MouseEvent & event)
        {
            if( _action &&
                event.x > _globalX && event.x < _globalX+_width &&
                event.y > _globalY && event.y < _globalY+_height )
            {
                switch(event.type)
                {
                    case MouseEvent::Pressed:
                    {
                        _hold = true;
                        _mousex = event.x;
                        _mousey = event.y;
                        _action->OnClick(event);
                        break;
                    }

                    case MouseEvent::Release:
                        _hold = false;
                        _action->UnClick(event);
                        break;

                    case MouseEvent::Moved:
                        _action->OnMoved(event);
                        break;
                }

                if( _hold && _drawn && event.button == MouseEvent::Right)
                {
                    int x = event.x - _mousex;
                    int y = event.y - _mousey;

                    _x += x;
                    _y += y;
                }
            }


            std::vector<UTILS::ptr<CComponent>::SharedPtr>::iterator it;
            for(it=_list_component.begin(); it!=_list_component.end(); ++it)
            {
                (*it)->OnEvent(event);
            }
        }

        void CFrame::Draw()
        {
            if( IsVisible() == false )
            {
                return;
            }

            CORE::IVideoDriver * driver = CDevice::GetDevice()->GetVideoDriver();

            MATH::Matrix4f matrix_pos = MATH::Matrix4f::CreateTranslation(GetPositionX(), GetPositionY(), 0);
            MATH::Matrix4f matrix_size = MATH::Matrix4f::CreateScale(GetWidth(), GetHeight(), 1);

            driver->PushMatrix(CORE::OMGL_MATRIX_MODEL);
            driver->MultMatrix(matrix_pos, CORE::OMGL_MATRIX_MODEL);


            if( _model.GetPtr() != 0 && _background)
            {
                driver->PushMatrix(CORE::OMGL_MATRIX_MODEL);
                driver->MultMatrix(matrix_size, CORE::OMGL_MATRIX_MODEL);
                _background->Enable(0);
                _model->Draw();
                _background->Disable(0);
                driver->PopMatrix(CORE::OMGL_MATRIX_MODEL);
            }

            if( _font )
            {
                driver->PushMatrix(CORE::OMGL_MATRIX_MODEL);
                driver->MultMatrix(MATH::Matrix4f::CreateTranslation(0, _font->GetSize(), 0), CORE::OMGL_MATRIX_MODEL);
                _font->Draw(_title, CORE::CColor::Black);
                driver->PopMatrix(CORE::OMGL_MATRIX_MODEL);
            }

            std::vector<UTILS::ptr<CComponent>::SharedPtr>::iterator it;
            for(it=_list_component.begin(); it!=_list_component.end(); ++it)
            {
                (*it)->Draw();
            }

            driver->PopMatrix(CORE::OMGL_MATRIX_MODEL);
        }

    }
}
