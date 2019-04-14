#ifndef _DEF_OMEGLOND3D_CFILE_HPP
#define _DEF_OMEGLOND3D_CFILE_HPP

#include <string>

namespace OMGL3D
{
    namespace UTILS
    {
        class CFile
        {

        public:

            CFile(const std::string & name);

            CFile(const char * name);

            CFile(const CFile & file);

            bool IsExists() const;

            const std::string & GetFullName() const;

            const std::string GetFileName() const;

            const std::string GetExtension() const;

            const std::string GetPath() const;


        private:

            std::string _name;
        };
    }
}

#endif
