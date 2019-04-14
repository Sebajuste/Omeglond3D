#ifndef _DEF_OMEGLOND3D_CLABEL_HPP
#define _DEF_OMEGLOND3D_CLABEL_HPP

#include "CComponent.hpp"

#include "../Font/IFont.hpp"
#include "../Utils/Export.hpp"

namespace OMGL3D
{
    namespace UI
    {
        class EXPORT CLabel : public CComponent
        {

        public:

            CLabel(const std::string & name);

            void SetFont(const std::string & font, int size=12, bool bold=false, bool italic=false, const CORE::CColor & color=CORE::CColor::Black);

            void SetText(const std::string & text);

            void Draw();


        private:

            UTILS::ptr<FONT::IFont>::ResourcePtr _font;
            std::string _text;
        };
    }
}

#endif
