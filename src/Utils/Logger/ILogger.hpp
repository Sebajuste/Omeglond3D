#ifndef _DEF_OMEGLOND3D_ILOGGER_HPP
#define _DEF_OMEGLOND3D_ILOGGER_HPP

#include "../Ptr/SmartPtr.hpp"

#include <string>
#include <sstream>
#include <map>

#include <iostream>

namespace OMGL3D
{
    namespace UTILS
    {
        enum LoggerType {
            OMGL_LOGGER_DEBUG,
            OMGL_LOGGER_STANDART,
            OMGL_LOGGER_ERROR,
            OMGL_LOGGER_RENDERER
        };

        enum LoggerTarget {
            OMGL_LOGGER_FILE,
            OMGL_LOGGER_CONSOLE
        };

        enum LoggerTag {
            OMGL_LOGGER_FLUSH,
            OMGL_LOGGER_ENDL
        };

        class ILogger
        {

        public:

            //-------------------------------------------------
            // Destructor
            //-------------------------------------------------
            virtual ~ILogger();

            //-------------------------------------------------
            // Add logger for type [OMGL_LOGGER_DEBUG|OMGL_LOGGER_ERROR|OMGL_LOGGER_RENDERER]
            //-------------------------------------------------
            static void SetLogger(ILogger * logger, const LoggerType & type);

            //-------------------------------------------------
            // Set the target for a logger type
            //-------------------------------------------------
            static void SetLogger(const LoggerType & type, const LoggerTarget & target);

            //-------------------------------------------------
            // Return the logger for type
            //-------------------------------------------------
            static ILogger & GetLogger(const LoggerType & type);

            //-------------------------------------------------
            // Destroy all loggers
            //-------------------------------------------------
            static void DestroyLoggers();

            //-------------------------------------------------
            // Return the current time
            //-------------------------------------------------
            static std::string GetCurrentTime();

            //-------------------------------------------------
            // Return the current date
            //-------------------------------------------------
            static std::string GetCurrentDate();

            //-------------------------------------------------
            // Operator << for log
            //-------------------------------------------------
            template <class T> ILogger & operator <<(const T & toLog);

            //-------------------------------------------------
            // Operator << for tag log [OMGL_LOGGER_ENDL|OMGL_LOGGER_FLUSH]
            //-------------------------------------------------
            ILogger & operator <<(const LoggerTag & toLog);


        private:

            //-------------------------------------------------
            // Write a string in the log
            //-------------------------------------------------
            virtual void Write(const std::string & str)=0;

            //-------------------------------------------------
            // Write a tag in the log
            //-------------------------------------------------
            virtual void Write(const LoggerTag & tag)=0;

            //-------------------------------------------------
            // Destroy a logger who type is the logger type
            //-------------------------------------------------
            static void Destroy(const LoggerType & type);


            struct LoggerLife {
                ~LoggerLife();
            };


            //typedef std::map<LoggerType, ILogger*> Loggers;
            typedef std::map<LoggerType, ptr<ILogger>::SharedPtr> Loggers;
            static Loggers _loggers;

            static LoggerLife life;
        };

        template <class T> ILogger & ILogger::operator <<(const T & toLog)
        {
            std::ostringstream stream;
            stream << toLog;
            Write(stream.str());
            return *this;
        }

    }
}

#endif
