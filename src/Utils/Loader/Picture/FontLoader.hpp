#ifndef _DEF_OMEGLOND3D_FONTLOADER_HPP
#define _DEF_OMEGLOND3D_FONTLOADER_HPP

#include "../ILoader.hpp"

#include "../../../Core/CPicture.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        class FontLoader : public ILoader<CORE::CPicture>
        {

        public:

            FontLoader();

            ~FontLoader();

            CORE::CPicture * Load(const CBuffer & buffer) throw(EXCP::LoadException);

            CBuffer Save(CORE::CPicture * picture) throw(EXCP::SaveException);

        };
    }
}

#endif
