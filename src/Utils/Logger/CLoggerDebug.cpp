#include "CLoggerDebug.hpp"

#include <iostream>

#include "../../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        void CLoggerDebug::Write(const std::string &str)
        {
            std::cout << str;
        }

        void CLoggerDebug::Write(const LoggerTag & tag)
        {
            switch(tag)
            {
                case OMGL_LOGGER_ENDL:
                case OMGL_LOGGER_FLUSH:
                    std::cout << std::endl;
                    break;
            }
        }
    }
}
