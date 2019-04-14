#ifndef _DEF_OMEGLOND3D_FILEREADER_HPP
#define _DEF_OMEGLOND3D_FILEREADER_HPP

#include "IReader.hpp"

#include <string>

namespace OMGL3D
{
    namespace UTILS
    {
        class CFileReader : public IReader<std::string>
        {

        public:

            CFileReader();

            ~CFileReader();

            CBuffer Read(const std::string &source, const StreamType &stream) throw(EXCP::ReadException);

            void Write(const std::string &source, const CBuffer &buffer, const StreamType &stream) throw(EXCP::WriteException);
        };
    }
}

#endif
