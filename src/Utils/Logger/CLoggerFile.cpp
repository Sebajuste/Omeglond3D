#include "CLoggerFile.hpp"

#include <fstream>

#include "../../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        CLoggerFile::CLoggerFile(const std::string &name)
        {
            _file.open(name.c_str());
        }

        CLoggerFile::~CLoggerFile()
        {
            _file.close();
        }

        void CLoggerFile::Write(const std::string &str)
        {
            if( _file.is_open() )
            {
                _file << str;
            }
        }

        void CLoggerFile::Write(const LoggerTag & tag)
        {
            if( !_file.is_open() )
                return;

            switch(tag)
            {
                case OMGL_LOGGER_ENDL:
                    _file << "\n";
                    break;

                case OMGL_LOGGER_FLUSH:
                    _file << std::endl;
                    break;
            }
        }
    }
}
