#ifndef _DEF_OMEGLOND3D_CSHADERLOADER_HPP
#define _DEF_OMEGLOND3D_CSHADERLOADER_HPP

#include "../ILoader.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        class CShaderLoader : public ILoader<char>
        {

        public:

            char * Load(const CBuffer & buffer) throw(EXCP::LoadException);
        };
    }
}

#endif
