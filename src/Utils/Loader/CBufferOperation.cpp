#include "CBufferOperation.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        std::string CBufferOperation::FindInformation(std::stringstream & buffer, const std::string & str)
        {
            std::string line;
            while( std::getline(buffer, line) )
            {
                int offset = 0;
                if( (offset = line.find(str)) != -1 ) {
                    return line.substr(offset+str.size());
                }
            }
            return line;
        }

        std::string CBufferOperation::FindXMLInformation(const std::string & line, const std::string & str)
        {
            int offset = line.find(str);
            if( offset == -1 ) {
                return "";
            }

            std::string subLine = line.substr(offset);
            offset = subLine.find("\"")+1;
            if( offset == -1 ) {
                return "";
            }

            subLine = subLine.substr(offset);

            offset = subLine.find("\"");
            if( offset == -1 ) {
                return "";
            }

            subLine = subLine.substr(0, offset);

            return subLine;
        }

        float CBufferOperation::StringToFloat(const std::string & str)
        {
            std::istringstream iss(str);
            float f = 0.0f;
            iss >> f;
            return f;
        }

        std::string CBufferOperation::Trim(const std::string & str)
        {
            return str.substr(str.find_first_not_of(' ') );
        }
    }
}
