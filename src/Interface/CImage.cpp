#include "CImage.hpp"

#include "../Core/CDevice.hpp"
#include "../Core/IVideoDriver.hpp"

#include <iostream>

namespace OMGL3D
{
    namespace UI
    {
        CImage::CImage(const std::string & name) : CComponent(name)
        {
            CORE::IVideoDriver * driver = CDevice::GetDevice()->GetVideoDriver();
            _square = driver->GetPrefabSquare();
        }

        void CImage::SetTexture(const std::string & texture)
        {
            CORE::IVideoDriver * driver = CDevice::GetDevice()->GetVideoDriver();
            _image = driver->GetTexture(texture);
        }

        void CImage::Draw()
        {
            CORE::IVideoDriver * driver = CDevice::GetDevice()->GetVideoDriver();
            MATH::Matrix4f pos_matrix = MATH::Matrix4f::CreateTranslation(GetPositionX(), GetPositionY(), 0);
            MATH::Matrix4f size_matrix = MATH::Matrix4f::CreateScale(GetWidth(), GetHeight(), 1);

            driver->PushMatrix(CORE::OMGL_MATRIX_MODEL);
            driver->MultMatrix(pos_matrix, CORE::OMGL_MATRIX_MODEL);
            driver->MultMatrix(size_matrix, CORE::OMGL_MATRIX_MODEL);
            //driver->multMatrix(MATH::Matrix4f::createScale(100, 100, 1), CORE::OMGL_MATRIX_MODEL);

            if( _image && _square)
            {
                _image->Enable(0);
                _square->Draw(CORE::AlphaTest(CORE::OMGL_ALPHATEST_GREATER, 0.5));
                _image->Disable(0);
            }

            driver->PopMatrix(CORE::OMGL_MATRIX_MODEL);

        }
    }
}
