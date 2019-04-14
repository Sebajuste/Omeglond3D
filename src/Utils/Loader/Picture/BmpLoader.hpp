#ifndef _DEF_OMEGLOND3D_BMPLOADER_HPP
#define _DEF_OMEGLOND3D_BMPLOADER_HPP

#include "../ILoader.hpp"

namespace OMGL3D
{
    namespace CORE {
        class CPicture;
    }

    namespace UTILS
    {
        class BmpLoader : public ILoader<CORE::CPicture>
        {

        public:

            ~BmpLoader()
            {
            }

            CORE::CPicture * Load(const CBuffer &buffer) throw(EXCP::LoadException);

            CBuffer Save(CORE::CPicture * picture) throw(EXCP::SaveException);
        };
    }
}

#endif
