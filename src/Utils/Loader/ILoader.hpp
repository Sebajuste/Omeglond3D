#ifndef _DEF_OMEGLOND3D_ILOADER_HPP
#define _DEF_OMEGLOND3D_ILOADER_HPP

#include "../Reader/CBuffer.hpp"

#include "../../Exception/LoadException.hpp"
#include "../../Exception/SaveException.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        template <class C> class ILoader
        {
            public:

            virtual ~ILoader()
            {
            }

            virtual C * Load(const CBuffer & buffer) throw(EXCP::LoadException)
            {
                throw EXCP::LoadException("Loader not yet implemented");
            }

            virtual CBuffer Save(C * object) throw(EXCP::SaveException)
            {
                throw EXCP::SaveException("Saver not yet implemented");
            }
        };
    }
}

#endif
