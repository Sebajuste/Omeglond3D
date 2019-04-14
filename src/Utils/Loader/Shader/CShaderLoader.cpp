#include "CShaderLoader.hpp"

#include "../../../Debug/DebugAllocation.hpp"

#include <string>
#include <cstring>

namespace OMGL3D
{
    namespace UTILS
    {
        char * CShaderLoader::Load(const CBuffer & buffer) throw(EXCP::LoadException)
        {
            std::string str = buffer.GetBuffer();
            std::size_t size = str.size() + 1;

            char * c_str = new char[size];

            std::strncpy( c_str, str.c_str(), size );

            return c_str;
        }
    }
}
