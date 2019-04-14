#ifndef _DEF_OMEGLOND3D_TGALOADER_HPP
#define _DEF_OMEGLOND3D_TGALOADER_HPP

#include "../ILoader.hpp"

#include "../../../Core/CPicture.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        class TgaLoader : public ILoader<CORE::CPicture>
        {

        public:

            TgaLoader();

            ~TgaLoader();

            CORE::CPicture * Load(const CBuffer & buffer) throw(EXCP::LoadException);

            CBuffer Save(CORE::CPicture * picture) throw(EXCP::SaveException);
        };
    }
}

#endif
