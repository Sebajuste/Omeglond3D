#include "CButton.hpp"

#include "../Core/CDevice.hpp"
#include "../Core/IVideoDriver.hpp"

namespace OMGL3D
{
    namespace UI
    {

        CButton::CButton()
        {
            m_Square = CDevice::GetDevice()->GetVideoDriver()->GetPrefabSquare();
        }

        CButton::CButton(const std::string & name) : CComponent(name)
        {
            m_Square = CDevice::GetDevice()->GetVideoDriver()->GetPrefabSquare();
        }

        void CButton::SetButtonImage(const std::string & img_name)
        {
            m_ImgCurrent = m_ImgDefault = CDevice::GetDevice()->GetVideoDriver()->GetTexture(img_name);
        }

        void CButton::SetButtonUp(const std::string & img_name)
        {
            m_ImgUp = CDevice::GetDevice()->GetVideoDriver()->GetTexture(img_name);
        }

        void CButton::SetButtonDown(const std::string & img_name)
        {
            m_ImgDown = CDevice::GetDevice()->GetVideoDriver()->GetTexture(img_name);
        }

        void CButton::Draw()
        {
            CORE::IVideoDriver * driver = CDevice::GetDevice()->GetVideoDriver();
            MATH::Matrix4f pos_matrix = MATH::Matrix4f::CreateTranslation(GetPositionX(), GetPositionY(), 0);
            MATH::Matrix4f size_matrix = MATH::Matrix4f::CreateScale(GetWidth(), GetHeight(), 1);

            driver->PushMatrix(CORE::OMGL_MATRIX_MODEL);
            driver->MultMatrix(pos_matrix, CORE::OMGL_MATRIX_MODEL);
            driver->MultMatrix(size_matrix, CORE::OMGL_MATRIX_MODEL);
            //driver->multMatrix(MATH::Matrix4f::createScale(100, 100, 1), CORE::OMGL_MATRIX_MODEL);

            if( m_ImgCurrent && m_Square)
            {
                m_ImgCurrent->Enable(0);
                m_Square->Draw(CORE::AlphaTest(CORE::OMGL_ALPHATEST_GREATER, 0.5));
                m_ImgCurrent->Disable(0);
            }

            driver->PopMatrix(CORE::OMGL_MATRIX_MODEL);
        }

        void CButton::OnEvent(const MouseEvent & event)
        {
            if( event.x > _globalX && event.x < _globalX+_width &&
                event.y > _globalY && event.y < _globalY+_height )
            {
                switch(event.type)
                {
                    case MouseEvent::Pressed:
                        m_ImgCurrent = m_ImgDown;
                        //_action->OnClick(event);
                        break;

                    case MouseEvent::Release:
                        m_ImgCurrent = m_ImgDefault;
                        //_action->OnUnclick(event);
                        break;

                    case MouseEvent::Moved:
                        m_ImgCurrent = m_ImgUp;
                        //_action->OnMoved(event);
                        break;
                }
            }

            CComponent::OnEvent(event);
        }

    }
}
