#ifndef _DEF_OMEGLOND3D_OBJLOADER_HPP
#define _DEF_OMEGLOND3D_OBJLOADER_HPP

#include "../ILoader.hpp"

#include "../../../Model/IStaticModel.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        class CObjLoader : public ILoader<MODEL::IStaticModel>
        {
            public:

            MODEL::IStaticModel * Load(const CBuffer & buffer) throw(EXCP::LoadException);
        };
    }
}

#endif

