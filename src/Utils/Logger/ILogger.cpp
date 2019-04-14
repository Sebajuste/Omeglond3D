#include "ILogger.hpp"

#include <ctime>

#include "../../Debug/DebugAllocation.hpp"

#include "CLoggerDebug.hpp"
#include "CLoggerFile.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        ILogger::~ILogger()
        {
        }

        void ILogger::SetLogger(ILogger * logger, const LoggerType & type)
        {
            if( logger != 0)
            {
                Destroy(type);
                _loggers[type] = logger;
            }
        }

        void ILogger::SetLogger(const LoggerType & type, const LoggerTarget & target)
        {
            Destroy(type);
            switch(target)
            {
                case OMGL_LOGGER_CONSOLE:
                {
                    _loggers[type] = new CLoggerDebug();
                    break;
                }

                case OMGL_LOGGER_FILE:
                {
                    std::string fileName;
                    switch(type)
                    {
                        case OMGL_LOGGER_DEBUG: fileName="stddebug.txt"; break;
                        case OMGL_LOGGER_STANDART: fileName="stdout.txt"; break;
                        case OMGL_LOGGER_ERROR: fileName="stderr.txt"; break;
                        case OMGL_LOGGER_RENDERER: fileName="stdrender.txt"; break;
                    }
                    _loggers[type] = new CLoggerFile(fileName);
                    break;
                }

                default:
                    break;
            }
        }

        ILogger& ILogger::GetLogger(const LoggerType & type)
        {
            Loggers::const_iterator it;
            it = _loggers.find(type);
            if( it == _loggers.end() )
            {
                _loggers[type] = new CLoggerFile("error_log.txt");
                return *_loggers[type];
            }
            return *(it->second);
        }

        void ILogger::DestroyLoggers()
        {
            _loggers.clear();
        }

        std::string ILogger::GetCurrentTime()
        {
            char result[24];
            time_t current_time = time(NULL);
            strftime(result, sizeof(result), "%H:%M:%S", localtime(&current_time));
            return result;
        }

        std::string ILogger::GetCurrentDate()
        {
            char result[24];
            time_t current_date = time(NULL);
            strftime(result, sizeof(result), "%d/%m/%Y", localtime(&current_date));

            return result;
        }

        void ILogger::Destroy(const LoggerType &type)
        {
            Loggers::iterator it = _loggers.find(type);
            if( it != _loggers.end() )
            {
                _loggers.erase(it);
            }
        }

        ILogger & ILogger::operator << (const LoggerTag & ToLog)
        {
            Write(ToLog);
            return *this;
        }

        ILogger::LoggerLife::~LoggerLife()
        {
            DestroyLoggers();
        }

        ILogger::Loggers ILogger::_loggers;

        ILogger::LoggerLife ILogger::life =  ILogger::LoggerLife();
    }
}
