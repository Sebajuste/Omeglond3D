#ifndef _DEF_OMEGLOND3D_READER_HPP
#define _DEF_OMEGLOND3D_READER_HPP

#include "CBuffer.hpp"

#include "../../Exception/ReadException.hpp"
#include "../../Exception/WriteException.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        enum StreamType
        {
            OMGL_STREAM_BINARY,
            OMGL_STREAM_ASCII
        };

        template <class C> class IReader
        {

        public:

            virtual ~IReader() { }

            virtual CBuffer Read(const C &source, const StreamType &stream) throw(EXCP::ReadException)
            {
                throw EXCP::ReadException("Reader not yet implemented");
            }

            virtual void Write(const C &source, const CBuffer &buffer, const StreamType &stream) throw(EXCP::WriteException)
            {
                throw EXCP::WriteException("Writer not yet implemented");
            }
        };
    }
}

#endif
