#ifndef _DEF_OMEGLOND3D_IFONT_HPP
#define _DEF_OMEGLOND3D_IFONT_HPP

#include "../Core/CResource.hpp"
#include "../Core/CColor.hpp"

#include <string>

namespace OMGL3D
{
    namespace FONT
    {
        class IFont : public CORE::CResource
        {

        public:

            virtual ~IFont() {}

            int GetSize() const
            {
                return _size;
            }

            virtual void Draw(const std::string & text, const CORE::CColor & color=CORE::CColor::White)=0;


        protected:

            IFont(const std::string & name) : CORE::CResource(name) {}

            int _size;
        };

    }
}

#endif
