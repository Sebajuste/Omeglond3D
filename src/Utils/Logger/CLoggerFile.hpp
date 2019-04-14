#ifndef _DEF_OMEGLOND3D_CLOGGERFILE_HPP
#define _DEF_OMEGLOND3D_CLOGGERFILE_HPP

#include "ILogger.hpp"

#include <fstream>

namespace OMGL3D
{
    namespace UTILS
    {
        class CLoggerFile : public ILogger
        {

        public:

            CLoggerFile(const std::string &name="log");

            ~CLoggerFile();

            void Write(const std::string &str);

            void Write(const LoggerTag & tag);


        private:
            //std::string _name;
            std::ofstream _file;
        };
    }
}

#endif
