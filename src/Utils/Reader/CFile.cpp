#include "CFile.hpp"

#include <fstream>

namespace OMGL3D
{
    namespace UTILS
    {
        CFile::CFile(const std::string & name) : _name(name)
        {
        }

        CFile::CFile(const char * name) : _name(name)
        {
        }

        CFile::CFile(const CFile & file) : _name(file.GetFullName())
        {
        }

        bool CFile::IsExists() const
        {
            std::ifstream file(_name.c_str());
            if( file.is_open() )
                return true;
            return false;
        }

        const std::string & CFile::GetFullName() const
        {
            return _name;
        }

        const std::string CFile::GetFileName() const
        {
            std::string::size_type pos = _name.find_last_of("/");
            std::string::size_type pos_ext = _name.find_last_of(".");

            if( pos != std::string::npos && pos_ext != std::string::npos)
            {
                return _name.substr(pos, pos_ext);
            }
            return "";
        }

        const std::string CFile::GetExtension() const
        {
            std::string::size_type pos = _name.find_last_of(".");

            if( pos != std::string::npos )
                return _name.substr(pos);
            return "";
        }

        const std::string CFile::GetPath() const
        {
            std::string::size_type pos = _name.find_last_of("/");
            if( pos != std::string::npos )
                return _name.substr(0, pos);
            return "";
        }
    }
}
