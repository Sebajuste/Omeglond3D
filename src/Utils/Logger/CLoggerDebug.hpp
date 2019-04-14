#ifndef _DEF_OMEGLOND3D_CLOGGERDEBUG_HPP
#define _DEF_OMEGLOND3D_CLOGGERDEBUG_HPP

#include "ILogger.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        class CLoggerDebug : public ILogger
        {

        public:

            void Write(const std::string &str);

            void Write(const LoggerTag & tag);
        };
    }
}

#endif
