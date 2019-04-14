#ifndef _DEF_OMEGLOND3D_CBUTTON_HPP
#define _DEF_OMEGLOND3D_CBUTTON_HPP

#include "CComponent.hpp"

#include "../Core/ITexture.hpp"
#include "../Model/IStaticModel.hpp"
#include "../Utils/Export.hpp"

namespace OMGL3D
{
    namespace UI
    {

        class EXPORT CButton : public CComponent
        {

        public:

            CButton();

            CButton(const std::string & name);

            void SetButtonImage(const std::string & img_name);

            void SetButtonUp(const std::string & img_name);

            void SetButtonDown(const std::string & img_name);

            void Draw();

            void OnEvent(const MouseEvent & event);


        private:

            UTILS::ptr<CORE::ITexture>::ResourcePtr m_ImgCurrent;

            UTILS::ptr<CORE::ITexture>::ResourcePtr m_ImgDefault;
            UTILS::ptr<CORE::ITexture>::ResourcePtr m_ImgUp;
            UTILS::ptr<CORE::ITexture>::ResourcePtr m_ImgDown;

            UTILS::ptr<MODEL::IStaticModel>::ResourcePtr m_Square;
        };

    }
}

#endif
