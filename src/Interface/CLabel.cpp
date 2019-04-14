#include "CLabel.hpp"

#include "../Core/CDevice.hpp"
#include "../Core/IVideoDriver.hpp"

namespace OMGL3D
{
    namespace UI
    {
        CLabel::CLabel(const std::string & name) : CComponent(name)
        {
        }

        void CLabel::SetFont(const std::string & font, int size, bool bold, bool italic, const CORE::CColor & color)
        {
            CORE::IVideoDriver * driver = CDevice::GetDevice()->GetVideoDriver();
            _font = driver->GetFont(font, size, bold, italic);
        }

        void CLabel::SetText(const std::string & text)
        {
            _text = text;
        }

        void CLabel::Draw()
        {
            CORE::IVideoDriver * driver = CDevice::GetDevice()->GetVideoDriver();

            MATH::Matrix4f matrix_pos = MATH::Matrix4f::CreateTranslation(GetPositionX(), GetPositionY(), 0);

            driver->PushMatrix(CORE::OMGL_MATRIX_MODEL);
            driver->MultMatrix(matrix_pos, CORE::OMGL_MATRIX_MODEL);

            _font->Draw(_text, CORE::CColor::Black);

            driver->PopMatrix(CORE::OMGL_MATRIX_MODEL);
        }
    }
}
